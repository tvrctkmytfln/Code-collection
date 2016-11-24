#!/usr/bin/python
# encoding:utf-8

"""
# 旧数据库内容移植
#
# func      :   数据库操作
# author    :   @`13
# version   :   0.1.0
"""

import MySQLdb
import threading
import datetime
import ConfigParser
cf = ConfigParser.ConfigParser()
cf.read("DataBase.conf")

class DataBase:
    """
    数据库操作类
    """
    def __init__(self, section='New_DataBase'):
        """
        :param section: 用于区分配置文件中的数据库类型
        """
        self.host = cf.get(section, 'host')
        self.user = cf.get(section, 'user')
        self.passwd = cf.get(section, 'passwd')
        self.charset = 'utf8'
        self.db_lock = threading.Lock()

    # 链接数据库
    def get_connect(self):
        if self.db_lock.acquire():
            try:
                self.conn = MySQLdb.Connection(
                    host=self.host, user=self.user, passwd=self.passwd, charset=self.charset)
            except MySQLdb.Error, e:
                print str(datetime.datetime.now()).split(".")[0], "ERROR %d: %s" % (e.args[0], e.args[1])

            self.cursor = self.conn.cursor()
            if not self.cursor:
                raise(NameError, "Connect failure")
            self.db_lock.release()

    # 关闭数据库
    def db_close(self):
        try:
            self.conn.close()
        except MySQLdb.Error as e:
            print 'db_close error_info: %d: %s' % (e.args[0], e.args[1])

    # 提交事务
    def db_commit(self):
        try:
            self.conn.commit()
        except MySQLdb.Error as e:
            print 'db_commit error_info: %d: %s' % (e.args[0], e.args[1])

    # 执行SQL语句
    def execute(self, sql):
        result = None
        if self.db_lock.acquire():
            try:
                self.cursor.execute(sql)
                result = self.cursor.fetchall()
            except MySQLdb.Error, e:
                if e.args[0] == 2013 or e.args[0] == 2006:  # 数据库连接出错，重连
                    self.db_lock.release()
                    self.get_connect()
                    print str(datetime.datetime.now()).split(".")[0], '数据库重新连接'
                    result = self.execute(sql)  # 重新执行
                    self.db_lock.acquire()
                else:
                    print str(datetime.datetime.now()).split(".")[0], "ERROR %d: %s" % (e.args[0], e.args[1])
            self.db_lock.release()
        return result if result else None

    # 执行SQL语句(转化为迭代器)
    def execute_Iterator(self, sql, pretchNum = 1000):
        Iterator_count = 0
        result = None
        result_list = []
        if self.db_lock.acquire():
            try:
                Resultnum = self.cursor.execute(sql)
                for j in range(Resultnum):
                    result = self.cursor.fetchone()
                    result_list.append(result[0])
                    Iterator_count += 1
                    if Iterator_count == pretchNum:
                        yield result_list
                        result_list = []
                        Iterator_count = 0
            except MySQLdb.Error, e:
                if e.args[0] == 2013 or e.args[0] == 2006:  # 数据库连接出错，重连
                    self.db_lock.release()
                    self.get_connect()
                    print str(datetime.datetime.now()).split(".")[0], '数据库重新连接'
                    result = self.execute(sql)  # 重新执行
                    self.db_lock.acquire()
                else:
                    print str(datetime.datetime.now()).split(".")[0], "ERROR %d: %s" % (e.args[0], e.args[1])
            self.db_lock.release()


