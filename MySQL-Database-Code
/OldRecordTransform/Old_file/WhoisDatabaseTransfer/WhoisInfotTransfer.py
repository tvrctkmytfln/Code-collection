#!/usr/bin/python
# encoding:utf-8

#
#原始whois数据转换
#`13
#2016.6.2
#

# 新whois数据格式
Whois = {
    'domain_hash': "",  # 域名哈希值
    "domain": "",  # 域名
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

def standWhois(domain,whois_detail):
    pass