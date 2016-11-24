# coding=utf-8

#
# 餐馆有m张桌子，
# 每张桌子有一个参数 a ： 可容纳的最大人数
# 有m批客人
# 每批客人有两个参数 b ： 人数 c ： 预计消费金额
# 在不得拼桌的情况下，请实现一个算法选择其中一部分客人，是得其总预计消费金额最大
#

# eg：
# input：

# 3 5
# 2 4 2
# 1 3
# 3 5
# 3 7
# 5 9
# 1 10

# out_put:
# 20


# 最终数据通过率 20%

# --获取输入内容部分--
# 1,2行
line1 = raw_input()
n = int(line1.split(' ', 1)[0])
m = int(line1.split(' ', 1)[1])
table_list = []
line2 = raw_input()
for table_max_people in line2.split(' '):
    table_list.append(int(table_max_people))
# 桌人数排序
table_list.sort()

# 获取输入内容
# 剩余m行
people_list = []
price_list = []
for i in range(m):
    line = raw_input()
    people_list.append(int(line.split(' ', 1)[0]))
    price_list.append(int(line.split(' ', 1)[1]))

# --处理结果部分--
result = 0
# 贪心算法，
#   优先处理最大的消费金额的人，
#   直到其中有一个列表内容为空，退出循环
while len(table_list) > 0 and len(price_list) > 0:
    # 获取当前最大的消费金额
    index = price_list.index(max(price_list))
    if index+1 > len(price_list):
        print -1
        break
    people = people_list[index]
    # 如果这个消费金额对应的人数在桌子人数的最大之内，则加上这个金额
    if max(table_list) > people_list[index]:
        result += price_list[index]
        del people_list[index]
        del price_list[index]
        # 找到第一个大于消费人数的桌子的下标志，并删除
        for i in table_list:
            if i > people:
                table_list.remove(i)
                break
    # 如果不满足，则直接去掉列表中对应的消费人数和金额
    else:
        del price_list[index]
        del people_list[index]
    # print table_list
    # print people_list
    # print price_list
# 输出结果
print result
