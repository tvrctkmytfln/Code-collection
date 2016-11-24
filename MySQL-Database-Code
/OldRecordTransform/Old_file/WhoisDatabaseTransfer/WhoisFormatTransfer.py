#!/usr/bin/python
# encoding:utf-8

#
#原始whois数据分析及转换
#`13
#2016.6.2
#

import re
import datetime
from WhoisdbOpreation import *
from WhoisInfoDeal.info_deal import *
from WhoisInfotTransfer import *

class whoisTransfer():
    '''whois数据转换类'''
    def __init__(self, whoisnum = 1000):
        self.db = DataBase()
        self.whoisnum = whoisnum

    #旧whois数据格式
    Old_whois = {
                    "domain": '',  # 域名
                    "flag": 0,  # 状态标记
                    "top_whois_server": "",  # 顶级域名服务器
                    "sec_whois_server": "",  # 二级域名服务器
                    "reg_name": "",  # 注册姓名
                    "reg_phone": "",  # 注册电话
                    "reg_email": "",  # 注册email
                    "org_name": "",  # 注册公司名称
                    "creation_date": "",  # 创建时间
                    "expiration_date": "",  # 到期时间
                    "updated_date": "",  # 更新时间
                    "insert_time": "",  # 信息插入时间
                    "details": "",  # 细节
                    }
    #新whois数据格式
    New_whois = {
        'domain_hash': "",  # 域名哈希值
        "domain": "",#域名
        "flag": 0,  # 状态标记
        "domain_status": "",  # 域名状态
        "sponsoring_registrar": "",  # 注册商
        "top_whois_server": "",  # 顶级域名服务器
        "sec_whois_server": "",  # 二级域名服务器
        "reg_name": "",  # 注册姓名
        "reg_phone": "",  # 注册电话
        "reg_email": "",  # 注册email
        "org_name": "",  # 注册公司名称
        "creation_date": "",  # 创建时间
        "expiration_date": "",  # 到期时间
        "updated_date": "",  # 更新时间
        "insert_time": "",  # 信息插入时间
        "details": "",  # 细节
        "name_server": "",  # 域名服务器
        "whois_hash": 0,  # whois信息哈希值
    }

    def testPrint(self,**kwargs):
        '''输出测试'''
        print "---------------domain_whois-----------------"
        print "domain_hash:      ", kwargs['domain_hash']
        print "domain:           ", kwargs['domain']
        print "flag:             ", kwargs['flag']
        print "domain_status:    ", kwargs['domain_status']
        print "sponsoring_registrar:", kwargs['sponsoring_registrar']
        print "top_whois_server: ", kwargs['top_whois_server']
        print "sec_whois_server: ", kwargs['sec_whois_server']
        print "reg_name:         ", kwargs['reg_name']
        print "reg_phone:        ", kwargs['reg_phone']
        print "reg_email:        ", kwargs['reg_email']
        print "org_name:         ", kwargs['org_name']
        print "updated_date:     ", kwargs['updated_date']
        print "creation_date:    ", kwargs['creation_date']
        print "expiration_date:  ", kwargs['expiration_date']
        print "insert_time:      ", kwargs['insert_time']
        print "name_server:       ", kwargs['name_server']
        print "whois_hash:      ", kwargs['whois_hash']
        print
        print "-----------------details--------------------"
        print kwargs['details']
        print "--------------------------------------------"


    def transfer(self, table_name):
        '''
        数据转换
        :return:含有whois信息的列表
        '''
        self.db.get_connect()
        for whoises in self.db.get_domainWhois(table_name, ):
            WhoisInfoList = []
            for whois in whoises:
                detail = whois[13]
                WhoisInfoList.append(detail)
            yield WhoisInfoList
        self.db.db_close()


if __name__ == '__main__':
    WT = whoisTransfer()
    for i in WT.Transfer('DomainWhois.domain_whois_A'):
        print i
        time.sleep(5)
    WT.db.db_close()