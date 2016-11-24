#!/usr/bin/python
# encoding:utf-8

#
#数据库操作
#`13
#2016.5.31
#

import MySQLdb
import threading
import time

class DataBase:
    '''数据库操作类'''
    def __init__(self):
        '''数据库初始化'''
        self.host = '-'
        self.user = '-'
        self.passwd = '-'
        self.charset = '-'
        self.db_lock = threading.Lock()  # 数据库操作锁

    def get_connect(self):
        '''执行连接数据库操作'''
        if self.db_lock.acquire():
            try:
                self.conn = MySQLdb.Connection(
                    host=self.host, user=self.user, passwd=self.passwd, charset=self.charset)
                self.cursor = self.conn.cursor()
            except MySQLdb.Error, e:
                print 'get_connect error_info: %d: %s' % (e.args[0], e.args[1])
            self.db_lock.release()

    def db_close(self):
        '''关闭数据库链接'''
        if self.db_lock.acquire():
            try:
                self.conn.close()
            except MySQLdb.Error, e:
                print 'db_close error_info: %d: %s' % (e.args[0], e.args[1])
            self.db_lock.release()

    def db_commit(self):
        '''提交事物'''
        if self.db_lock.acquire():
            try:
                self.conn.commit()
            except MySQLdb.Error, e:
                print 'db_commit error_info: %d: %s' % (e.args[0], e.args[1])
            self.db_lock.release()

    def __execute__(self, sql):
        '''执行sql语句
        :param sql: sql语句
        :return: 执行结果
        '''
        result = None
        if self.db_lock.acquire():
            try:
                self.cursor.execute(sql)
                result = self.cursor.fetchall()
            except MySQLdb.Error, e:
                if e.args[0] == 2013 or e.args[0] == 2006:  # 数据库连接出错，重连
                    self.db_lock.release()
                    self.get_connect()
                    print '数据库重新连接'
                    result = self.__execute__(sql)  # 重新执行
                    self.db_lock.acquire()
                else:
                    print 'db_execute error_info: %d: %s' % (e.args[0], e.args[1])
            self.db_lock.release()
        return result if result else None

    # 数据库whois获取
    def get_domainWhois(self, table_name,whoisnum = 1000):
        '''
        获取whois数据
        :param table_name: 库名.表名
        :param whoisnum: 单次从取得的whois信息个数
        :return:每次调用生成有内容的whois信息里表
        '''
        id_count = 0
        domainwhois_list = []
        sql = """SELECT count(*) FROM {table} WHERE flag > 0""".format(table = table_name,)
        domainwhois_num = self.__execute__(sql)[0][0]
        #print domainwhois_num
        for times in range(domainwhois_num//whoisnum + 1):
            SQL = """SELECT * FROM {table} WHERE flag>0 AND id>{num1} AND id<={num2}"""\
                .format(table = table_name, num1 = id_count, num2 = id_count+whoisnum)

            temp = self.__execute__(SQL)
            if temp:
                for whoisinfo in self.__execute__(SQL):
                    domainwhois_list.append(whoisinfo)

            yield domainwhois_list
            domainwhois_list = []
            id_count += whoisnum
            if id_count > domainwhois_num + whoisnum:
                break

if __name__ == '__main__':

    db = DataBase()
    db.get_connect()
    for i in db.get_domainWhois('DomainWhois.domain_whois_A',):
        print i
        time.sleep(3)
    db.db_close()