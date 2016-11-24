#!/usr/bin/python
# encoding:utf-8

#
# 数据库转移主程序
# `13
# 2016.5.30

import json
import pika
import re
# from gevent import monkey
# monkey.patch_socket()
# import gevent
import datetime
import WhoisFormatTransfer

channel_whois = None
RABBITMQ_HOST = '-'  # rabbitmq_host
count = 0
import threading
count_lock = threading.Lock()

# 初始化通信队列
def init_queue():
    global channel_whois
    connect = pika.BlockingConnection(pika.ConnectionParameters(RABBITMQ_HOST))
    channel_whois = connect.channel()
    channel_whois.queue_declare(queue='whois_queue', durable=True)

def whois_push(**whois_recv_info):
    global channel_whois
    # print 'whois push:', whois_recv_info
    result = ''
    try:
        result = json.dumps(whois_recv_info)
    except UnicodeDecodeError:
        for key in whois_recv_info.keys():
            if type(whois_recv_info[key]) == str:
                whois_recv_info[key] = whois_recv_info[key].decode('latin-1').encode("utf-8")
        result = json.dumps(whois_recv_info)
    if result != '':
        channel_whois.basic_publish(
                exchange='',
                routing_key='whois_queue',
                body=json.dumps(result),
                properties=pika.BasicProperties(
                        delivery_mode=2)
        )

# 开启20个客户端线程
def main():
    init_queue()  # 初始化通信队列
    import threading
    thread_list = []
    for i in range(20):
       client_thread = threading.Thread(target=thread_client)
       client_thread.setDaemon(True)
       client_thread.start()
       thread_list.append(client_thread)
    for client_thread in thread_list:
       client_thread.join()