#include <iostream>
#include <stdio.h>
#include <malloc.h>
#include <stack>
#include <queue>

using namespace std;

/** ���ݽṹʵ�� ��3
 * authro : @`13
 * time   : 2016��11��7�� */
//  �������ṹ
typedef struct node {
    char data;          //�ڵ�����Ԫ��
    struct node *lchild;//ָ������
    struct node *rchild;//ָ���Һ���
}BiTNode,*BTree;

// ����
// �����ܷ���һ��Ψһ�Ķ�������
// https://zhidao.baidu.com/question/491870984.html��
BTree ImpCreatBitTree (void)
{/** ������һ�Ŷ����� */
    BTree bt;
    char ch;
    cin>>ch;
    if (ch=='#')
        return NULL;
    else
    {
        if (!(bt=(BTree)malloc(sizeof(BiTNode)))) return NULL;
        bt->lchild=ImpCreatBitTree();   // ��
        bt->data=ch;                    // ��
        bt->rchild=ImpCreatBitTree();   // ��
    }
    return bt;
}

/** ˼�룺���ø���ջ��ֻҪջ��Ϊ�գ��Ϳ���������������
 * ÿ�ε���һ����㣬���������ҽ�㶼��ջ��[����->���ȳ�*/
void PreOrder_Nonrecursive(BTree T)
{/** ��������ķǵݹ� */
    if(!T)
        return ;
    stack<BTree> s;
    s.push(T);  // ����վ

    while(!s.empty())
    {
        BTree tmp = s.top();
        cout<<tmp->data<<" ";  // ����ڵ�
        s.pop();
        if(tmp->rchild)    // �ҽڵ��Ƚ�ջ,��֤�ȳ����������ڵ�
            s.push(tmp->rchild);
        if(tmp->lchild)
            s.push(tmp->lchild);
    }
/** ˼�룺����1-����һ������ȫ����ڵ� �������ջ����������
 *       ����2-������ڵ㿪ʼ���γ�ս,��ʹ�ò���1 [���շ��ʵ�˳���˼·*/
    void PreOrder_Nonrecursive1(BTree T)
    {
        if(!T)
            return ;

        stack<BTree> s;
        BTree cur = T; // �����α�
        while(cur != NULL || !s.empty())
        {
            while(cur != NULL)
            {   // ����ѹ��һ������ȫ����ڵ㲢���
                cout<<cur->data<<"  ";
                s.push(cur);
                cur = cur->lchild;
            }
            if(!s.empty())
            {   // ����ջ�е�ÿ�����ڵ�(��Ҫ�����Һ��ӵ�)��Ѱ�����нڵ�Ȼ��ѹ�룬�����ظ�����ѭ������ ֱ��ȫ��ջ��
                cur = s.top();
                s.pop();
                cur = cur->rchild;
            }
        }
    }
    /** CSDN�����ϵ�˼· ������˼·2 ����ʹ����ʱ���α� */
    void PreOrder_Nonrecursive2(BTree T)
    {
        if(!T)
            return ;

        stack<BTree> s;
        while(T)          // �������ϵĽڵ�ȫ��ѹ�뵽ջ��
        {
            s.push(T);
            cout<<T->data<<"  ";
            T = T->lchild;
        }

        while(!s.empty())
        {
            BTree tmp = s.top()->rchild;  // ջ��Ԫ�ص�������
            s.pop();                        // ����ջ��Ԫ��
            while(tmp)          // ջ��Ԫ�ش��������������������ͬ�����������·�
            {
                cout<<tmp->data<<"  ";
                s.push(tmp);
                tmp = tmp->lchild;
            }
        }
    }

    /** ������������� 1
     * ˼·���ȱ��������������Դ���ջ Ȼ�����γ�ջ���������ҽڵ�
     *      �ظ�������̱���Եõ�����������ַ����������Ͼ��ǻ���˳��
     */
    void InOrderTraverse(BTree T)
    {
        if(!T)
            return ;
        BTree cur = T;    // ָ��ǰҪ�����Ľڵ�
        stack<BTree> s;
        while(cur != NULL || !s.empty())
        {
            while(cur != NULL)
            {   // �����α����ڽڵ����������
                s.push(cur);    // ������ջ
                cur = cur->lchild;
            }
            if(!s.empty())
            {
                cur = s.top();
                s.pop();
                cout<<cur->data<<"  ";  // �������
                cur = cur->rchild;      // ������
            }
        }
    }

    /** ������������� 2
    * ˼·���ȱ��������������Դ���ջ
    *      ���ε����ڵ� ������ڵ�����������ظ��ϸ�����
    */
    void InOrderTraverse1(BTree T)
    {
        if(!T)
            return ;

        stack<BTree> s;
        BTree cur = T->lchild;    // ָ��ǰҪ���Ľڵ�
        s.push(T);
        while(cur != NULL || !s.empty())
        {
            while(cur != NULL)
            { // �����α����ڽڵ������������������ջ
                s.push(cur);
                cur = cur->lchild;
            }
            cur = s.top();
            s.pop();
            cout<<cur->data<<"  ";  // ���ÿ��ջ�нڵ��������
            cur = cur->rchild;
        }
    }

    /** ��������������
    * ˼·���ȱ��������������Դ���ջ
    *      ���ε����ڵ� ����ڵ���Һ������Ϊ�ջ����Ѿ������ʣ�����ʵ�ǰ�ڵ�
    *      �ظ�������̱���Եõ�����������ַ���
    *      �������½ڵ㰴�� ��-��-�� ��˳�����������
    */
    void PostOrder_Nonrecursive1(BTree T)
    {
        stack<BTree> S;
        BTree cur = T ;             // �α�
        BTree preCur = NULL;        // �α���ʷ�ڵ�
        while(cur != NULL || !S.empty())  // ջ��ʱ����
        {
            while(cur != NULL)            // һֱ������ֱ��Ϊ��
            {
                S.push(cur);
                cur = cur->lchild;
            }
            cur = S.top();
            // ��ǰ�ڵ���Һ������Ϊ�ջ����Ѿ������ʣ�����ʵ�ǰ�ڵ�
            if(cur->rchild == NULL || cur->rchild == preCur)
            {
                cout<<cur->data<<"  ";
                preCur = cur;
                S.pop();
                cur = NULL;
            }
            else
                cur = cur->rchild;      // ��������Һ���
        }
    }

    /** ����CSDN���� ˫ջ�� */
    void PostOrder_Nonrecursive2(BTree T)  // ��������ķǵݹ� 2     ˫ջ��
    {
        stack<BTree> s1 , s2;
        BTree curr ;           // ָ��ǰҪ���Ľڵ�
        s1.push(T);
        while(!s1.empty())  // ջ��ʱ����
        {
            curr = s1.top();
            s1.pop();
            s2.push(curr);
            if(curr->lchild)
                s1.push(curr->lchild);
            if(curr->rchild)
                s1.push(curr->rchild);
        }
        while(!s2.empty())
        {
            printf("%c ", s2.top()->data);
            s2.pop();
        }
    }


    int visit(BTree T)
    {
        if(T)
        {
            printf("%c ",T->data);
            return 1;
        }
        else
            return 0;
    }
    /** CSDN:������������ķ��� */
    void LeverTraverse(BTree T)   //����һ���ǵݹ��α���������
    {
        queue <BTree> Q;
        BTree p;
        p = T;
        if(visit(p)==1)
            Q.push(p);
        while(!Q.empty())
        {
            p = Q.front();
            Q.pop();
            if(visit(p->lchild) == 1)
                Q.push(p->lchild);
            if(visit(p->rchild) == 1)
                Q.push(p->rchild);
        }
    }
    void LevelOrder(BTree BT)     //���������ǵݹ��α���������
    {
        BiTNode *queue[10];//���������ʮ���ռ�
        if (BT==NULL)
            return;
        int front,rear;
        front=rear=0;
        queue[rear++]=BT;
        while(front!=rear)//�����βָ�벻���ڶ�ͷָ��ʱ
        {
            cout<<queue[front]->data<<"  ";  //����������
            if(queue[front]->lchild!=NULL)  //�����׽�������ָ�������
            {
                queue[rear]=queue[front]->lchild;
                rear++;    //��βָ�����һλ
            }
            if(queue[front]->rchild!=NULL)
            {
                queue[rear]=queue[front]->rchild;    //�����׽����Һ���ָ�������
                rear++;   //��βָ�����һλ
            }
            front++;    //��ͷָ�����һλ
        }
    }

int main(void)
{cout << "Hello, World!" << endl;}

