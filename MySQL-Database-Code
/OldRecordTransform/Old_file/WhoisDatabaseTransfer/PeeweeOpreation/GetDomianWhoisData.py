# /usr/bin/python
# encoding:utf-8

#
#数据库操作
#`13
#2016.5.31
#

import peewee

import Model


class WhoisDataBase():
    def __init__(self):
        table_list = [
            'Model.domain_whois_A',
            'Model.domain_whois_B',
            'Model.domain_whois_C',
            'Model.domain_whois_D',
            'Model.domain_whois_E',
            'Model.domain_whois_F',
            'Model.domain_whois_G',
            'Model.domain_whois_H',
            'Model.domain_whois_I',
            'Model.domain_whois_J',
            'Model.domain_whois_K',
            'Model.domain_whois_L',
            'Model.domain_whois_M',
            'Model.domain_whois_N',
            'Model.domain_whois_O',
            'Model.domain_whois_P',
            'Model.domain_whois_Q',
            'Model.domain_whois_R',
            'Model.domain_whois_S',
            'Model.domain_whois_T',
            'Model.domain_whois_U',
            'Model.domain_whois_V',
            'Model.domain_whois_W',
            'Model.domain_whois_X',
            'Model.domain_whois_Y',
            'Model.domain_whois_Z',
            'Model.domain_whois_num',
            'Model.domain_whois_other',]  # 表
        model_list = []     # 模型表
        for table in table_list:
            model_list.append(eval(table))
        self.model_list = model_list
        self.sign_commit = False #数据库锁

    #连接
    def connect(self):
        Model.OldWhoisDatabase.connect()

    #关闭
    def close(self):
        Model.OldWhoisDatabase.close()

    #提交
    def commit(self):
        self.sign_commit = True
        Model.OldWhoisDatabase.commit()
        self.sign_commit = False



    # 获取旧数据库中没有处理的域名
    # @param orderNum 表序号[0~27]
    def GetDomainWhois(self, orderNum):
        try:
            query_results = self.model_list[orderNum].select(
            ).where(
                self.model_list[orderNum].flag > 1
            ).limit(1)

            return query_results
        except peewee.OperationalError as error:
            print error

