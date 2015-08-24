// cplusplus_test.cpp : �������̨Ӧ�ó������ڵ㡣
/*******************************copyrights****************************************
   This code was programmed by xiefanfan,xi'an university of technology,all rights reserved;
**Function:research on Red-Black Tree
**Time:2015-08-23
********************************************************************************/

/********************************************************
**�����5�����ʣ�
**��1��ÿ�����Ǻ켴��
**��2��������Ǻ�ɫ
**��3��Ҷ�ӽ���Ǻ�ɫ�ģ�NULL������NIL��㣩
**��4�����һ������Ǻ�ɫ����ô���ĺ��ӽ��Ϊ��ɫ
**��5��������ڵ㣬�Ӹý�㵽����NIL���·���ϣ������ĺڽڵ������ͬ
********************************************************/
#include "stdafx.h"
#include <stdio.h>
#include <iostream>

//������ɫ���ͣ�ʹ��ö��
typedef enum color_t
{
      RED = 0,
      BLACK
}color_t;

//���������Ľ��ṹ��
typedef struct RBTreeNode
{
      int    key;                    //��ֵ
      struct RBTreeNode *lchild;
      struct RBTreeNode *rchild;
      struct RBTreeNode *parent;
      color_t  color;                //��ɫ
}RBTreeNode,*RBTree;

RBTreeNode* RBTsearch(RBTree *T,int value);               //���Ҹ���ֵ�Ƿ����
RBTreeNode* RBTSuccessor(RBTreeNode* x);                  //���ص�ǰ���ĺ�̽��
RBTreeNode* RBTPredecessor(RBTreeNode* x);                //���ص�ǰ����ǰ�����
int RBTInsert(RBTree *T,int value);                      //������
int RBTDelete(RBTree *T,int value);                      //ɾ�����
void RBTLeftRotate(RBTree *T,RBTreeNode* x);             //��������
void RBTRightRotate(RBTree *T,RBTreeNode* x);             //��������
void RBTInsertFixUp(RBTree *T,RBTreeNode* x);             //�����޸�
void RBTDeleteFixUp(RBTree *T,RBTreeNode* p,RBTreeNode* x);             //ɾ���޸�


/*********************************************
**���ܣ�������в���һ�����
**T:��������ڵ�
**value�������ֵ
**warning������һ����㣬�ý��Ϊ��ɫ���п����ƻ�����������ʣ���Ҫ�������޸����ָ������������
*********************************************/
int RBTInsert(RBTree *T,int value)
{
      RBTreeNode *node,*p,*curNode;

      node = (RBTreeNode *)malloc(sizeof(RBTreeNode));
      if (!node)
      {
            return 0;
      }
      node->key = value;
      node->color = RED;               //�½��Ϊ��ɫ
      node->lchild = NULL;
      node->rchild = NULL;
      node->parent = NULL;

      curNode = *T;
      //�ҵ��½�����Ľ��λ�ã���p�����������ĸ����
      p = NULL;
      while (curNode != NULL)
      {
            p = curNode;
            if (value < curNode->key)
            {
                  curNode = curNode->lchild;
            }
            else
            {
                  curNode = curNode->rchild;
            }
      }
      if (!p)              //����
      {
            (*T) = node;
      }
      else
      {
            if (value < p->key)          //���뵽���
            {
                  p->lchild = node;
            }
            else
            {
                  p->rchild = node;
            }
      }
      node->parent = p;                   //��ǰ��㸸���
      RBTInsertFixUp(T,node);             //����������޸������ֺ����������
      return 1;
}

/*********************************************
**���ܣ��������ɾ��һ�����
**T:��������ڵ�
**value��ɾ������ֵ
**warning��ɾ��һ����㣬�п����ƻ�����������ʣ���Ҫ��ɾ���޸������ָ������������
*********************************************/
int RBTDelete(RBTree *T,int value)
{
      RBTreeNode *target,*realDel,*child;
      target = RBTsearch(T,value);
      if (!target)                       //�ýڵ㲻����
      {
            return 0;
      }
      if (target->lchild == NULL || target->rchild == NULL)        //�ҵ���ɾ�������������λ��,��������������һ��Ϊ��
      {
            realDel = target;
      }
      else                                                         //������������Ϊ��
      {
            realDel = RBTSuccessor(target);                        //�ҵ���ǰ���ĺ�̽��
      }
      if (realDel->lchild)                             //��ɾ�����ֻ��һ���������ؽӸ�����
      {
            child = realDel->lchild;
      }
      else
      {
            child = realDel->rchild;
      }

      if (child)                                       //���ӽ��ĸ����ָ������ɾ�����ĸ����
      {
            child->parent = realDel->parent;
      }

      if (realDel->parent == NULL)                    //����㣿
      {
            (*T) = child;
      }
      else
      {
            if (realDel->parent->lchild == realDel)
            {
                  realDel->parent->lchild = child;
            }
            else
            {
                  realDel->parent->rchild = child;
            }
      }

      if (target != realDel)
      {
            target->key = realDel->key;
      }

      if (realDel->color == BLACK)                             //����ɾ���Ľ���Ǻ�ɫ���Ž���ɾ���޸�����ɫ���ɾ����Ӱ����������
      {
            RBTDeleteFixUp(T,realDel->parent ,child);
      }
      free(realDel);
      return 1;
}

/*********************************************
**���ܣ�������в���һ��Ԫ�غ󣬿����ƻ��˺���������ʣ���Ҫ�Ժ�������в������޸�����
**T:�����
**x���Ӹý�㿪ʼ�޸�
**warning��������޸���Ҫ�������ֲ�����޸��������,����������ƻ�����4������2.
*********************************************/
void RBTInsertFixUp(RBTree *T,RBTreeNode* x)
{
      RBTreeNode *p,*gparent,*uncle;                //����㡢�游����������ָ��
      //��������2
      while ((p = x->parent) != NULL && p->color == RED)               //�����Ϊ��ɫ�������游���һ������
      {
            gparent = p->parent;
            if (p == gparent->lchild)               //��������游����������
            {
                  uncle = gparent->rchild;
                  //���1�������Ϊ��ɫ��㣬������Ϊ��ɫ��㣻
                  //����������������������Ϳ�ڣ��游���Ϳ�죬Ȼ����游��㴦�����޸�
                  if (uncle != NULL && uncle->color == RED)
                  {
                        gparent->color = RED;
                        p->color = BLACK;
                        uncle->color = BLACK;
                        x = gparent;
                  }
                  else                              //�����㲻���ڻ���Ϊ��ɫ��ͨ����ת�����ֺ��������
                  {
                        //���2����ǰ���Ϊ������������,
                        //����������ָ��ǰ���ĸ����Ϊ֧�㣬��������������תΪ���3
                        if (x == p->rchild)         
                        {
                              x = p;
                              RBTLeftRotate(T,x);
                              p = x->parent;               //��ת������޸���ʹp��Ϊx�ĸ����
                        }
                        //���3����ǰ���Ϊ������������
                        //����������������Ϊ�ڣ��游����Ϊ�죬�游���Ϊ֧���������������
                        else                             
                        {
                              p->color = BLACK;
                              gparent->color = RED;
                              RBTRightRotate(T,gparent);
                        }
                  }
            }
            else                                    //��������游����������,���ϱ��ǶԳ����
            {
                  uncle = gparent->lchild;
                  //���1��������������Ϊ��ɫ
                  if (uncle != NULL && uncle->color == RED)
                  {
                        p->color = BLACK;
                        uncle->color = BLACK;
                        gparent->color = RED;
                        x = gparent;
                  }
                  else                              //�����㲻���ڻ���Ϊ��ɫ��ͨ����ת�����ֺ��������
                  {
                        //���2��xΪ�丸������ӣ�ͨ����תת��Ϊ���3
                        if (x == p->lchild)
                        {
                              x = p;
                              RBTRightRotate(T,x);
                              p = x->parent;
                        }
                        //���3��xΪ�丸������������������ɫִ�ڣ��游�����ɫֵ�죬Ȼ�����游���Ϊ֧���������
                        else
                        {
                              p->color = BLACK;
                              gparent->color = RED;
                              RBTLeftRotate(T,gparent);
                        }
                  }
            }
      }
      //��������2
      (*T)->color = BLACK;
}

/*********************************************
**���ܣ��������������
**T:����������
**x����ǰ��ת��ָ����
*********************************************/
void RBTLeftRotate(RBTree *T,RBTreeNode* x)
{
      //����˳���ȵ���x������������������ĸ���㣬Ȼ�����R��x�ĸ�������ӹ�ϵ��������x����㲻����x������������R������������޸�R��x�����ӡ�
      RBTreeNode *R;                                   //ָ��x����������
      R = x->rchild;
      x->rchild = R->lchild;
      if (R->lchild)
      {
            R->lchild->parent = x;                     //R�������ĸ�����޸�Ϊx
      }
      R->parent = x->parent;
      if (x->parent == NULL)                           //���ڵ�
      {
            *T = R;
      }
      else
      {
            if (x->parent->lchild == x)                //x�������������Ϲ���R
            {
                  x->parent->lchild = R;
            }
            else
            {
                  x->parent->rchild = R;
            }
      }
      R->lchild = x;                                   //�޸�R��x֮��Ĺ�ϵ
      x->parent = R;
}

/*********************************************
**���ܣ��������������
**T:����������
**x����ǰ��ת��ָ����
*********************************************/
void RBTRightRotate(RBTree *T,RBTreeNode* x)
{
      //��������������
      RBTreeNode *L;
      L = x->lchild;
      x->lchild = L->rchild;
      if (L->rchild)
      {
            L->rchild->parent = x;
      }
      L->parent = x->parent;
      if (x->parent == NULL)                //�����
      {
            *T = L;
      }
      else
      {
            if (x->parent->lchild == x)
            {
                  x->parent->lchild = L;
            }
            else
            {
                  x->parent->rchild = L;
            }
      }
      L->rchild = x;
      x->parent = L;
}

/*********************************************
**���ܣ������������һ������Ƿ���ڣ����ھͷ���һ��ָ�����ָ�룬���򷵻�0
**T:�����
**value�����ļ�ֵ
*********************************************/
RBTreeNode* RBTsearch(RBTree *T,int value)
{
      if (!(*T))                   //Ϊ�� ����0
      {
            return 0;
      }
      if ((*T)->key == value)
      {
            return (*T);
      }
      else if(value < (*T)->key)
      {
            return RBTsearch(&(*T)->lchild,value);
      }
      else
      {
            return RBTsearch(&(*T)->rchild,value);
      }
}

/*********************************************
**���ܣ��ҵ���ǰ����ǰ�����
**x:��ǰ�Ľ��
*********************************************/
RBTreeNode* RBTSuccessor(RBTreeNode* x)
{
      RBTreeNode *rp;
      rp = x->rchild;                      //���ң�Ȼ�����󵽾�ͷ
      while(rp->lchild)
      {
            rp = rp->lchild;
      }
      return rp;
}

/*********************************************
**���ܣ��ҵ���ǰ���ĺ�̽��
**x:��ǰ�Ľ��
*********************************************/
RBTreeNode* RBTPredecessor(RBTreeNode* x)
{
      RBTreeNode *lp;
      lp = x->lchild;                        //����Ȼ�����ҵ���ͷ
      while (lp->rchild)
      {
            lp = lp->rchild;
      }
      return lp;
}

/*********************************************
**���ܣ�ɾ��һ���ڽڵ�󣬽���ɾ���޸����ָ����������
**T:��������ڵ�
**p����ǰ���ĸ����
**x����ǰ���
*********************************************/
void RBTDeleteFixUp(RBTree *T,RBTreeNode* p,RBTreeNode* x)
{
      RBTreeNode *brother;                      //�ֵܽ��ָ��
      while ((x == NULL || x->color == BLACK) && x != (*T))        
      {
            if (x == p->lchild)                 //��ǰ���Ϊ���������
            {
                  brother = p->rchild;
                  //���1���ֵܽ��Ϊ��ɫ
                  //����취��������ú죬�ֵܽ���úڣ��Ը����Ϊ֧���������
                  if (brother->color == RED)
                  {
                        brother->color = BLACK;
                        p->color = RED;
                        RBTLeftRotate(T,p);
                        brother = p->rchild;
                  }
                  //���2���ֵܽ��Ϊ�ڣ��ֵܽڵ���������ӽ�㶼Ϊ��(NULLҲΪ�ڽڵ�)����x��brotherĨ��һ�غ�ɫ
                  //����취��brother��ɫ��Ϊ�죬x������Ƶ��丸���
                  if ((brother->lchild == NULL || brother->lchild->color == BLACK) && (brother->rchild == NULL || brother->rchild->color == BLACK))
                  {
                        brother->color = RED;
                        x = p;
                        p = p->parent;
                  }                  
                  else
                  {
                        //���3���ֵܽ��Ϊ�ڣ��ֵܽ������Ϊ�죬����Ϊ��
                        //����������ֵܽ��Ⱦ�죬�ֵܽ������Ⱦ�ڣ����ֵܽ��Ϊ֧���������   
                        if (brother->rchild == NULL && brother->color == BLACK)
                        {
                              brother->lchild->color = BLACK;
                              brother->color = RED;
                              RBTRightRotate(T,brother);
                              brother = p->rchild;
                        }
                        //���4���ֵܽ��Ϊ�ڣ��ֵܽ������Ϊ�죬��������
                        //������������ֵܽڵ�Ⱦ�ɸ������ɫ�������Ⱦ�ڣ��ֵܽ���ҽ��Ⱦ�ڣ��Ը����Ϊָ���������
                        else
                        {
                              brother->color = p->color;
                              p->color = BLACK;
                              brother->rchild->color = BLACK;
                              RBTLeftRotate(T,p);
                        }

                        x = (*T);                        //��xΪ����ʱ������ѭ��
                  }
            }
            else
            {
                  brother = p->lchild;
                  //���1
                  if (brother->color == RED)
                  {
                        brother->color = BLACK;
                        p->color = RED;
                        RBTRightRotate(T,p);
                        brother = p->lchild;
                  }
                  //���2
                  if ((brother->lchild == NULL || brother->lchild->color == BLACK) && (brother->rchild == NULL || brother->rchild->color == BLACK))
                  {
                        brother->color = RED;
                        x = p;
                        p = p->parent;
                  }
                  else
                  {
                        //���3
                        if (brother->lchild == NULL || brother->lchild->color == BLACK)
                        {
                              brother->rchild->color = BLACK;
                              brother->color = RED;
                              RBTLeftRotate(T,brother);
                              //����brother
                              brother = p->lchild;
                        }
                        //���4
                        else
                        {
                              brother->color = p->color;
                              p->color = BLACK;
                              brother->lchild->color = BLACK;
                              RBTRightRotate(T,p);
                        }

                        x = *T;
                  }
            }
      }
      if (x != NULL)
      {
            x->color = BLACK;
      }
}

/*********************************************
**���ܣ��ݹ��ӡ������,�������
**T:����������
*********************************************/
void PrintBTree(RBTree T)
{
   if (!T)                    //�ݹ����
      return;
   PrintBTree(T->lchild);
   printf("%d-%c\n",T->key,T->color==RED?'r':'b');
   PrintBTree(T->rchild);
}

int _tmain(int argc, _TCHAR* argv[])
{
   int a[] = {3,2,1,4,5,6,7,10,9,8};
    RBTree rbt;
    rbt = NULL;
    for (int i=0;i<10;++i)
    {
          RBTInsert(&rbt,a[i]);
    }
    PrintBTree(rbt);
    RBTDelete(&rbt,1);
    PrintBTree(rbt);
    printf("\n");

   return 0;
}

