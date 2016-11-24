# /usr/bin/python
# encoding:utf-8

#
#peewee模型表
#`13
#2016.5.31
#

import peewee

OldWhoisDatabase = peewee.MySQLDatabase(
            host='-',
            user='-',
            passwd='-',
            database='-',
            charset='-',
            port=3306)

#peewee模型
class WhoisBaseModel(peewee.Model):
    id = peewee.IntegerField()
    domain = peewee.CharField()
    flag = peewee.IntegerField()
    ip = peewee.CharField()
    sponsoring_registrar = peewee.CharField()
    top_whois_server = peewee.CharField()
    sec_whois_server = peewee.CharField()
    reg_name = peewee.CharField()
    reg_phone = peewee.CharField()
    reg_email = peewee.CharField()
    org_name = peewee.CharField()
    name_server = peewee.CharField()
    creation_date = peewee.CharField()
    expiration_date = peewee.CharField()
    updated_date = peewee.CharField()
    insert_time = peewee.DateTimeField()
    details = peewee.TextField()
    tld = peewee.CharField()

    class Meta():
        database = OldWhoisDatabase

#旧库中的28张表
class domain_whois_A(WhoisBaseModel):pass
class domain_whois_B(WhoisBaseModel):pass
class domain_whois_C(WhoisBaseModel):pass
class domain_whois_D(WhoisBaseModel):pass
class domain_whois_E(WhoisBaseModel):pass
class domain_whois_F(WhoisBaseModel):pass
class domain_whois_G(WhoisBaseModel):pass
class domain_whois_H(WhoisBaseModel):pass
class domain_whois_I(WhoisBaseModel):pass
class domain_whois_J(WhoisBaseModel):pass
class domain_whois_K(WhoisBaseModel):pass
class domain_whois_L(WhoisBaseModel):pass
class domain_whois_M(WhoisBaseModel):pass
class domain_whois_N(WhoisBaseModel):pass
class domain_whois_O(WhoisBaseModel):pass
class domain_whois_P(WhoisBaseModel):pass
class domain_whois_Q(WhoisBaseModel):pass
class domain_whois_R(WhoisBaseModel):pass
class domain_whois_S(WhoisBaseModel):pass
class domain_whois_T(WhoisBaseModel):pass
class domain_whois_U(WhoisBaseModel):pass
class domain_whois_V(WhoisBaseModel):pass
class domain_whois_W(WhoisBaseModel):pass
class domain_whois_X(WhoisBaseModel):pass
class domain_whois_Y(WhoisBaseModel):pass
class domain_whois_Z(WhoisBaseModel):pass
class domain_whois_num(WhoisBaseModel):pass
class domain_whois_other(WhoisBaseModel):pass


db_whois_addr = peewee.MySQLDatabase(
    host='172.26.253.3',
    user='root',
    passwd='platform',
    database='domain_whois',
    charset='utf8',
    port=3306)

class whois_addr(peewee.Model):
    tld = peewee.CharField()  # 顶级域名
    addr = peewee.CharField()  # 顶级域名对应的whois服务器
    class Meta():
        database = db_whois_addr

