#!/usr/bin/python
# encoding:utf-8

"""
# 旧数据库内容移植
#
# func      :   flag变换工作过程
# author    :   @`13
# version   :   0.1.0
"""

from gen_SQL import SQL_refactor
from db_opreation import DataBase
log = open("Opreation_log.txt",'w')

# 旧数据库数据表
Table_Name_list = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
                   'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                   'Y', 'Z', 'num', 'other']


def GetOldDatabaseDomain(OldDatabase, fetchLimit=1000):
    """
    获取旧数据库中，whois内容完整的域名
    :param Database:数据库操作对象
    :param fetchLimit:每次取回的数目 （默认1000）
    :return : 已经获取了的whois的domain的生成器
    """
    count = 0
    OldDatabase.get_connect()
    for tableName in Table_Name_list:
        SQL = """SELECT `domain` FROM DomainWhois.domain_whois_{order} WHERE `flag`>'100' LIMIT 1000""".format(
            order=tableName)    # SQL语句
        for domain_list in OldDatabase.execute_Iterator(SQL, pretchNum=fetchLimit):
            for domain in domain_list:  # 每次返回固定数量个域名
                yield domain
                count += 1
        massage = '[Table]处理了'+tableName+'库中的约'+str(count)+'个域名'
        print massage
        log.write(massage)
        log.write('\n')
        count = 0
    OldDatabase.db_close()

def OldWhois2NewFlga():
    """
    工作函数
    将就数据库的有内容的数据在新库中进行标记
    """
    commit_count = 0
    no_exist_count = 0
    ODB = DataBase(section='Old_DataBase')
    NDB = DataBase(section='New_DataBase')
    NDB.get_connect()
    for domain in GetOldDatabaseDomain(ODB):
        # print domain
        SQL_serch = SQL_refactor.isFlag_100(domain)
        result = NDB.execute(SQL_serch)
        if result:
            flag = str(NDB.execute(SQL_serch)[0][0])
            if int(flag) <= -98:
                # 将暂时未处理的domain的flag改为-97
                SQL_update = SQL_refactor.Update_by_domain(domain, UpdateCon=['flag'], UpdateVal=['-97'])
                # print SQL_update
                NDB.execute(SQL_update)     # 操作
                # print domain,
                # print 'flag'+str(flag)+'->97'
                commit_count += 1
                if commit_count == 1000:    # 一定数量操作开始提交事物
                    NDB.db_commit()     # 提交事物
                    print '[Commit]数据库提交'
                    commit_count = 0
        else:
            print '[Domain]新库中不存在的域名:',
            print domain
            no_exist_count += 1
            log.write('[Domain]新库中不存在的域名:')
            log.write(domain)
            log.write('\n')
    # 关闭
    NDB.db_commit()
    NDB.db_close()
    log.write('[Domain]新库中不存在的域名个数 : ')
    log.write(str(no_exist_count))
    log.write('\n')
    log.close()


if __name__ == '__main__':
    OldWhois2NewFlga()
