#include <iostream>
#include <stack>

using namespace std;

#ifndef stauts
    #define stauts int
#endif
#define QB2S_OK 1
#define QB2S_ERROR -1
#define QB2S_NULL -214748364

/**
���ݽṹѧϰ - 3
author     :   @`13
func       :   �� ����ջ��ά��һ������
time       :   2016.10.18
 ˼·��
 1-���е�ʵ�֣��õ���һ��ջ
 2-���ӣ���ӵĽ��˼·��
    ������������ S1 ��Ϊ���������S2����Ϊ����������������
    ��ӡ�������ջ��S1
    ����  �����жϡ�S2���Ƿ�Ϊ�գ�
                        ���գ�
                            �򽫡�S1 ������n-1 ��Ԫ�ء��󡡵������һ��Ԫ�س�ջ
                        ����Ϊ�գ�
                            ��ֱ�ӵ�����S2��Ԫ����Ϊ����Ԫ��

   * ����һЩ�߽��ж��������������ʵ�ֶ��еĹ���
   *��S2 ��ʱʵ�����ǡ��ߵ������Ķ��С�ջ����������ӵ�Ԫ��,ֱ�ӳ�ջ���������Ӳ���
   * �˷�����һ��ʼ��������ġ�һ��ջ��λ��������һ��ջ��Ϊ�������ĸĽ���
   * ����ÿ�β�����������ջ��ֻ����Ҫ��ʱ����е�ջ�����ӿ��˴����ٶ�
   * ���ǻ�ȡ��ͷԪ�ص�ʱ�򣬻�����Ҫ���ε�ջ
*/

// ʹ����ģ�壬ʹ����Զ�Ӧ��������
template <class DataType>
class QueneBy2Stack
// ʹ����ģ����У��ڽ�������ɳ��ԣ���Ӳ���
{
private:
    stack<DataType>  _s1;
    stack<DataType>  _s2;
    int count;  // ���м�������

public:
    QueneBy2Stack()
    /** ���캯�� */
    { count = 0; }

    int getLength()
    /**����ȡ���г��� */
    { return count;}

    stauts push(DataType a)
    /** ��Ӳ���
         ��Ԫ�� a �������*/
    {
        _s1.push(a);
        count++;
    }

    stauts pop()
    /** ���Ӳ�����*/
    {
        if(_s1.empty()&&_s2.empty())
            return QB2S_ERROR;
        else if(!_s2.empty())
        {
            _s2.pop();
            count--;
            return QB2S_OK;
        }
        else
        {
            while (_s1.size() > 1)
            {   // ��ջ����
                _s2.push(_s1.top());
                _s1.pop();
            }
            count--;
            _s1.pop();
            return QB2S_OK;
        }
    }

    DataType front()
    /** ��ȡ��ͷԪ�ز����� */
    {
        DataType e;
        if(_s1.empty()&&_s2.empty())
        {
            cout<<"��������Ԫ��"<<endl;
            return QB2S_NULL;
        }
        else if(!_s2.empty())
            return _s2.top();
        else
        {
            while (_s1.size() > 1)
            {   // ���ε�ջ����
                _s2.push(_s1.top());
                _s1.pop();
            }
            e = _s1.top();
            while (_s2.size() > 0)
            {
                _s1.push(_s2.top());
                _s2.pop();
            }
            return e;
        }
    }

    void raw_show()
    /** ���� */
    {
        int s1l = _s1.size();
        int s2l = _s2.size();
        cout<<"----------STACK 1----------"<<endl;
        for(int i=s1l;i>0;i--)
        {
            cout<<i<<"\t:\t"<<_s1.top()<<endl;
            _s1.pop();
        }
        cout<<"----------STACK 2----------"<<endl;
        for(int j=s2l;j>0;j--)
        {
            cout<<j<<"\t:\t"<<_s2.top()<<endl;
            _s2.pop();
        }
    }
};


int main(void)
{
    QueneBy2Stack<int> q;
    q.push(1);// 1
    cout<<"��ͷԪ�أ�"<<q.front()<<endl;
    q.push(2);// 1 2 3
    q.push(3);// 1 2 3
    cout<<"��ͷԪ�أ�"<<q.front()<<endl;
    q.pop();// 2 3
    q.push(4);// 2 3 4
    cout<<"��ͷԪ�أ�"<<q.front()<<endl;
    q.push(5);// 2 3 4 5
    q.pop();// 3 4 5
    cout<<"��ͷԪ�أ�"<<q.front()<<endl;

    q.raw_show();// �鿴ջ������

}
