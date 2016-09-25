#!/usr/bin/python
# encoding:utf-8

#
# proxy_ip
# func  :
# time  : 2016.9.15
# author: @`13
#

import json
import urllib

#  快代理订单号：
orderNum = '977384347862623'  # 订单号，从网页中获取


class proxy_ip:
    """简单封装'快代理'的API接口"""
    def __init__(self):
        """基础信息"""
        self.order = '977384347862623'  # 订单号，从网页中获取
        self.vip_url = 'http://dev.kuaidaili.com/api/getproxy'  # VIP账户API链接

    @staticmethod
    def getPageText(url):
        """获取页面内容
        :return url的HTML源码"""
        try:
            text = urllib.urlopen(url).read()
        except:
            print "[Error]解析" + str(url) + "内容失败！"
            return None
        return text

    def genAPI(self, num='100', quality='1', area='', sp1='1', sp2='0', sort='1', format='text', sep='1'):
        """
        生成API连接
        详细链接：http://www.kuaidaili.com/genapiurl
        :param @num     提取数量        - number～提取数量
        :param @quality 代理ip的稳定性   - 0～不稳定 1～稳定（vip）
        :param @area    ip所在地区      - 支持按 国家/省/市 筛选(多个地区用英文逗号分隔，如 北京,上海)
        :param @sp1     极速代理        - 0～不开启 1～开启
        :param @sp2     快速代理        - 0～不开启 1～开启
        :param @sort    排序方式        - 1～V响应速度(从快到慢) （vip）
        :param @format  返回格式        - text，xml，json
        :param @sep     分隔符          - 1～/r/n  other～
        :return API链接
        """
        # 部分默认参数
        b_pcie = 1  # IE浏览器支持
        b_pcff = 1  # 火狐浏览器支持
        protocol = 1    # 协议支持
        method = 1  # GET/POST方法支持
        url = self.vip_url + '/?'
        url += 'orderid='+str(self.order)
        url += '&'
        url += 'num=' + str(num)
        url += '&'
        url += 'b_pcie=' + str(b_pcie) + '&'
        url += 'b_pcff=' + str(b_pcff) + '&'
        url += 'protocol=' + str(protocol) + '&'
        url += 'method=' + str(method) + '&'
        url += 'quality=' + str(quality)
        url += '&'
        if area != '':
            url += 'area=' + str(area)
            url += '&'
        if sp1 == '1':
            url += 'sp1=' + str(sp1)
            url += '&'
        if sp2 == '1':
            url += 'sp2=' + str(sp2)
            url += '&'
        if sort:
            url += 'sort=' + str(sort)
            url += '&'
        url += 'format=' + str(format)
        url += '&'
        url += 'sep=' + str(sep)
        return url

    def getProxy(self, APIlink):
        """获取代理ip
        :return 代理ip构成的列表"""
        data = self.getPageText(APIlink)
        proxy_ip_list = []
        if data is not None:
            for proxyIp in data.split('\r\n'):
                proxy_ip_list.append(proxyIp)
            return proxy_ip_list    # 返回代理IP列表
        return None  # 获取失败返回None

if __name__ == '__main__':
    # A Demo for 快代理 proxy ip
    p = proxy_ip()
    url = p.genAPI(area='中国')
    result = p.getProxy(url)
    if result is not None:
        for ip in result:
            # foo - bar
            pass
