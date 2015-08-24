// cplusplus_test.cpp : 定义控制台应用程序的入口点。
/*******************************copyrights****************************************
   This code was programmed by xiefanfan,xi'an university of technology,all rights reserved;
**Function:research on Red-Black Tree
**Time:2015-08-23
********************************************************************************/

/********************************************************
**红黑树5大性质：
**（1）每个结点非红即黑
**（2）根结点是黑色
**（3）叶子结点是黑色的（NULL结点或者NIL结点）
**（4）如果一个结点是红色，那么它的孩子结点为黑色
**（5）对任意节点，从该结点到任意NIL结点路径上，经过的黑节点个数相同
********************************************************/
#include "stdafx.h"
#include <stdio.h>
#include <iostream>

//定义颜色类型，使用枚举
typedef enum color_t
{
      RED = 0,
      BLACK
}color_t;

//定义红黑树的结点结构体
typedef struct RBTreeNode
{
      int    key;                    //键值
      struct RBTreeNode *lchild;
      struct RBTreeNode *rchild;
      struct RBTreeNode *parent;
      color_t  color;                //颜色
}RBTreeNode,*RBTree;

RBTreeNode* RBTsearch(RBTree *T,int value);               //查找给定值是否存在
RBTreeNode* RBTSuccessor(RBTreeNode* x);                  //返回当前结点的后继结点
RBTreeNode* RBTPredecessor(RBTreeNode* x);                //返回当前结点的前驱结点
int RBTInsert(RBTree *T,int value);                      //插入结点
int RBTDelete(RBTree *T,int value);                      //删除结点
void RBTLeftRotate(RBTree *T,RBTreeNode* x);             //左旋操作
void RBTRightRotate(RBTree *T,RBTreeNode* x);             //右旋操作
void RBTInsertFixUp(RBTree *T,RBTreeNode* x);             //插入修复
void RBTDeleteFixUp(RBTree *T,RBTreeNode* p,RBTreeNode* x);             //删除修复


/*********************************************
**功能：红黑树中插入一个结点
**T:红黑树根节点
**value：插入的值
**warning：插入一个结点，该结点为红色。有可能破坏红黑树的性质，需要做插入修复，恢复红黑树的性质
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
      node->color = RED;               //新结点为红色
      node->lchild = NULL;
      node->rchild = NULL;
      node->parent = NULL;

      curNode = *T;
      //找到新结点插入的结点位置，用p保存带插入结点的父结点
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
      if (!p)              //空树
      {
            (*T) = node;
      }
      else
      {
            if (value < p->key)          //插入到左边
            {
                  p->lchild = node;
            }
            else
            {
                  p->rchild = node;
            }
      }
      node->parent = p;                   //当前结点父结点
      RBTInsertFixUp(T,node);             //红黑树插入修复，保持红黑树的性质
      return 1;
}

/*********************************************
**功能：红黑树中删除一个结点
**T:红黑树根节点
**value：删除结点键值
**warning：删除一个结点，有可能破坏红黑树的性质，需要做删除修复处理，恢复红黑树的性质
*********************************************/
int RBTDelete(RBTree *T,int value)
{
      RBTreeNode *target,*realDel,*child;
      target = RBTsearch(T,value);
      if (!target)                       //该节点不存在
      {
            return 0;
      }
      if (target->lchild == NULL || target->rchild == NULL)        //找到待删除结点的真正结点位置,至少左右子树有一个为空
      {
            realDel = target;
      }
      else                                                         //左右子树都不为空
      {
            realDel = RBTSuccessor(target);                        //找到当前结点的后继结点
      }
      if (realDel->lchild)                             //待删除结点只有一颗子树，重接该子树
      {
            child = realDel->lchild;
      }
      else
      {
            child = realDel->rchild;
      }

      if (child)                                       //孩子结点的父结点指向真正删除结点的父结点
      {
            child->parent = realDel->parent;
      }

      if (realDel->parent == NULL)                    //根结点？
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

      if (realDel->color == BLACK)                             //真正删除的结点是黑色，才进行删除修复，红色结点删除不影响红黑树性质
      {
            RBTDeleteFixUp(T,realDel->parent ,child);
      }
      free(realDel);
      return 1;
}

/*********************************************
**功能：红黑树中插入一个元素后，可能破坏了红黑树的性质，需要对红黑树进行插入后的修复工作
**T:红黑树
**x：从该结点开始修复
**warning：红黑树修复主要考虑三种插入的修复情况即可,插入结点可能破坏性质4和性质2.
*********************************************/
void RBTInsertFixUp(RBTree *T,RBTreeNode* x)
{
      RBTreeNode *p,*gparent,*uncle;                //父结点、祖父结点和叔叔结点指针
      //纠正性质2
      while ((p = x->parent) != NULL && p->color == RED)               //父结点为红色，所以祖父结点一定存在
      {
            gparent = p->parent;
            if (p == gparent->lchild)               //父结点是祖父结点的左子树
            {
                  uncle = gparent->rchild;
                  //情况1，父结点为红色结点，叔叔结点为红色结点；
                  //修正方法：父结点和叔叔结点涂黑，祖父结点涂红，然后从祖父结点处继续修复
                  if (uncle != NULL && uncle->color == RED)
                  {
                        gparent->color = RED;
                        p->color = BLACK;
                        uncle->color = BLACK;
                        x = gparent;
                  }
                  else                              //叔叔结点不存在或者为黑色，通过旋转来保持红黑树性质
                  {
                        //情况2，当前结点为父结点的右子树,
                        //修正方法：指向当前结点的父结点为支点，进行左旋操作，转为情况3
                        if (x == p->rchild)         
                        {
                              x = p;
                              RBTLeftRotate(T,x);
                              p = x->parent;               //旋转后进行修复，使p仍为x的父结点
                        }
                        //情况3，当前结点为父结点的左子树
                        //修正方法：父结点变为黑，祖父结点变为红，祖父结点为支点进行右旋操作，
                        else                             
                        {
                              p->color = BLACK;
                              gparent->color = RED;
                              RBTRightRotate(T,gparent);
                        }
                  }
            }
            else                                    //父结点是祖父结点的右子树,跟上边是对称情况
            {
                  uncle = gparent->lchild;
                  //情况1：父结点和叔叔结点为红色
                  if (uncle != NULL && uncle->color == RED)
                  {
                        p->color = BLACK;
                        uncle->color = BLACK;
                        gparent->color = RED;
                        x = gparent;
                  }
                  else                              //叔叔结点不存在或者为黑色，通过旋转来保持红黑树性质
                  {
                        //情况2：x为其父结点左子，通过旋转转换为情况3
                        if (x == p->lchild)
                        {
                              x = p;
                              RBTRightRotate(T,x);
                              p = x->parent;
                        }
                        //情况3：x为其父结点右子树，父结点颜色执黑，祖父结点颜色值红，然后以祖父结点为支点进行左旋
                        else
                        {
                              p->color = BLACK;
                              gparent->color = RED;
                              RBTLeftRotate(T,gparent);
                        }
                  }
            }
      }
      //保持性质2
      (*T)->color = BLACK;
}

/*********************************************
**功能：红黑树左旋处理
**T:红黑树根结点
**x：当前旋转的指点结点
*********************************************/
void RBTLeftRotate(RBTree *T,RBTreeNode* x)
{
      //调整顺序：先调整x结点右子树的左子树的父结点，然后调整R和x的父结点链接关系（左旋后，x父结点不再与x相连，而是与R相连），最后修改R和x的连接。
      RBTreeNode *R;                                   //指向x结点的右子树
      R = x->rchild;
      x->rchild = R->lchild;
      if (R->lchild)
      {
            R->lchild->parent = x;                     //R左子树的父结点修改为x
      }
      R->parent = x->parent;
      if (x->parent == NULL)                           //根节点
      {
            *T = R;
      }
      else
      {
            if (x->parent->lchild == x)                //x父结点的左子树上挂载R
            {
                  x->parent->lchild = R;
            }
            else
            {
                  x->parent->rchild = R;
            }
      }
      R->lchild = x;                                   //修改R和x之间的关系
      x->parent = R;
}

/*********************************************
**功能：红黑树右旋处理
**T:红黑树根结点
**x：当前旋转的指点结点
*********************************************/
void RBTRightRotate(RBTree *T,RBTreeNode* x)
{
      //方法与左旋类似
      RBTreeNode *L;
      L = x->lchild;
      x->lchild = L->rchild;
      if (L->rchild)
      {
            L->rchild->parent = x;
      }
      L->parent = x->parent;
      if (x->parent == NULL)                //根结点
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
**功能：红黑树中搜索一个结点是否存在，存在就返回一个指向结点的指针，否则返回0
**T:红黑树
**value：结点的键值
*********************************************/
RBTreeNode* RBTsearch(RBTree *T,int value)
{
      if (!(*T))                   //为空 返回0
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
**功能：找到当前结点的前驱结点
**x:当前的结点
*********************************************/
RBTreeNode* RBTSuccessor(RBTreeNode* x)
{
      RBTreeNode *rp;
      rp = x->rchild;                      //向右，然后向左到尽头
      while(rp->lchild)
      {
            rp = rp->lchild;
      }
      return rp;
}

/*********************************************
**功能：找到当前结点的后继结点
**x:当前的结点
*********************************************/
RBTreeNode* RBTPredecessor(RBTreeNode* x)
{
      RBTreeNode *lp;
      lp = x->lchild;                        //向左，然后向右到尽头
      while (lp->rchild)
      {
            lp = lp->rchild;
      }
      return lp;
}

/*********************************************
**功能：删除一个黑节点后，进行删除修复，恢复红黑树性质
**T:红黑树根节点
**p：当前结点的父结点
**x：当前结点
*********************************************/
void RBTDeleteFixUp(RBTree *T,RBTreeNode* p,RBTreeNode* x)
{
      RBTreeNode *brother;                      //兄弟结点指针
      while ((x == NULL || x->color == BLACK) && x != (*T))        
      {
            if (x == p->lchild)                 //当前结点为父结点左子
            {
                  brother = p->rchild;
                  //情况1：兄弟结点为红色
                  //解决办法：父结点置红，兄弟结点置黑，以父结点为支点进行左旋
                  if (brother->color == RED)
                  {
                        brother->color = BLACK;
                        p->color = RED;
                        RBTLeftRotate(T,p);
                        brother = p->rchild;
                  }
                  //情况2：兄弟结点为黑，兄弟节点的两个孩子结点都为黑(NULL也为黑节点)：将x和brother抹除一重黑色
                  //解决办法：brother颜色变为红，x结点上移到其父结点
                  if ((brother->lchild == NULL || brother->lchild->color == BLACK) && (brother->rchild == NULL || brother->rchild->color == BLACK))
                  {
                        brother->color = RED;
                        x = p;
                        p = p->parent;
                  }                  
                  else
                  {
                        //情况3：兄弟结点为黑，兄弟结点左子为红，右子为黑
                        //解决方法：兄弟结点染红，兄弟结点左子染黑，以兄弟结点为支点进行右旋   
                        if (brother->rchild == NULL && brother->color == BLACK)
                        {
                              brother->lchild->color = BLACK;
                              brother->color = RED;
                              RBTRightRotate(T,brother);
                              brother = p->rchild;
                        }
                        //情况4：兄弟结点为黑，兄弟结点右子为红，左子任意
                        //解决方法：将兄弟节点染成父结点颜色，父结点染黑，兄弟结点右结点染黑，以父结点为指点进行左旋
                        else
                        {
                              brother->color = p->color;
                              p->color = BLACK;
                              brother->rchild->color = BLACK;
                              RBTLeftRotate(T,p);
                        }

                        x = (*T);                        //当x为树根时，结束循环
                  }
            }
            else
            {
                  brother = p->lchild;
                  //情况1
                  if (brother->color == RED)
                  {
                        brother->color = BLACK;
                        p->color = RED;
                        RBTRightRotate(T,p);
                        brother = p->lchild;
                  }
                  //情况2
                  if ((brother->lchild == NULL || brother->lchild->color == BLACK) && (brother->rchild == NULL || brother->rchild->color == BLACK))
                  {
                        brother->color = RED;
                        x = p;
                        p = p->parent;
                  }
                  else
                  {
                        //情况3
                        if (brother->lchild == NULL || brother->lchild->color == BLACK)
                        {
                              brother->rchild->color = BLACK;
                              brother->color = RED;
                              RBTLeftRotate(T,brother);
                              //重置brother
                              brother = p->lchild;
                        }
                        //情况4
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
**功能：递归打印二叉树,中序遍历
**T:二叉排序树
*********************************************/
void PrintBTree(RBTree T)
{
   if (!T)                    //递归出口
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

