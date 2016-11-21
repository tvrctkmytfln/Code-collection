#include <iostream>
#include <vector>
#include <algorithm>
// algorithm意为"算法"
// 是C++的标准模版库（STL）中最重要的头文件之一
// 提供了大量基于迭代器的非成员模版函数

/** STL源码剖析
 *  P36L1
 *  仿函数-functor
 *
 *  @`13
 *  2016年11月21日
 * */

using namespace std;

template<typename T>
class print {
public:
    void operator()(const T &elem) { cout << elem << " "; }
};
// 简单总结(参数)
/*  int类型作为形参--值传递：形参a ,b 也要分配内存空间，实参的值复制给形参  */
void mySwap1(int a, int b) {
    int temp;
    temp = a;
    a = b;
    b = temp;
}

/*  int * 类型作为形参--值传递：形参p1,p2 也要分配内存空间，实参的值复制给形参（地址）  */
void mySwap2(int *p1, int *p2) {
    //改变形参指针的指向，不会影响到实参
    int *temp;
    temp = p1;
    p1 = p2;
    p2 = temp;
}

/*  int * 类型作为形参--值传递：形参p1,p2 也要分配内存空间，实参的值复制给形参（地址）  */
void mySwap3(int *p1, int *p2) {
    //改变形参指针指向的内存空间值，也就改变了实参指针指向的内存空间值
    int temp2;
    temp2 = *p1;
    *p1 = *p2;
    *p2 = temp2;
}

/*  引用类型作为形参--址传递：形参a,b是不分配内存空间的，形参是实参的“别名”  */
void mySwap4(int &a, int &b) {
    int temp;
    temp = a;
    a = b;
    b = temp;
}
// 传递参数时有关&与*的区别
// http://blog.csdn.net/cxc19890214/article/details/44617685

// plus：
// 函数作为参数传递
// 函数指针！ http://www.cnblogs.com/uniqueliu/archive/2011/07/27/2118619.html
// Demo
int add(int a, int b)
{ return a + b; }

int sub(int a, int b)
{ return a - b; }

// 函数指针的定义 注意 (*fun)不能省略
int (*fun)(int a, int b);

int calc(int a, int b, int (*fun)(int a, int b))
{ return fun(a, b); }

int func_main() {
    int num1, num2;
    char op;
    scanf("%d %d %c", &num1, &num2, &op);
    switch (op) {
        case '+':
            fun = add;  //定义在上面
            break;
        case '-':
            fun = sub;
            break;
        default:
            fun = add; }
    printf("%d\n", calc(num1, num2, fun));
    return 0;
}

int main() {
    int ia[6] = {0, 1, 2, 3, 4, 5};
    vector<int> iv(ia, ia + 6);
    // STL vetcor支持多种构造函数重载
    // http://blog.csdn.net/huang_xw/article/details/8213617
    for_each(iv.begin(), iv.end(), print<int>()); // STL内函数
    return 0;
}