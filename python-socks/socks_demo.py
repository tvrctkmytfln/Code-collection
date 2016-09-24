# coding=utf-8
import socks
import urllib2

# 218.241.238.141:1080@SOCKS4#北京市 电信通
# 221.4.140.85:1080@SOCKS4#广东省东莞市 联通
# 211.154.6.19:8888 523 523 @SOCKS5

s = socks.socksocket()  # 创建对象
s.set_proxy(socks.SOCKS5, "211.154.6.19", 8888, username="523", password="523") # 设置代理
s.connect(('218.241.97.14', 43))    # 连接
s.send('baidu.cn\r\n')  # 发送请求

data_result = ''

# 从字节流读取内容，直到结束
while True:
    try:
        data_rcv = s.recv(1024)
    except Exception as e:
        print e
    if not len(data_rcv):
        print data_result  # 返回查询结果
        break
    data_result = data_result + data_rcv  # 每次返回结果组合

s.close()

