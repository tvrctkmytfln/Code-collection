# coding=utf-8

# func:用于测试，学习tldextract包
# time:2016.7.21
# author:@`13

import tldextract

domain = "baidu.com"

tld = tldextract.extract(domain)
print tld.domain
print tld.subdomain
print tld.suffix