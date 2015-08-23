// cplusplus_test.cpp : 定义控制台应用程序的入口点。
//平衡二叉树研究

#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#define LH 1            //左高
#define EH 0            //等高
#define RH -1           //右高

using namespace std;

typedef struct BiTNode          //结点结构体
{
   int data;
   int bf;                      //结点平衡因子
   struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

/*********************************************
**功能：对以p为根的二叉排序树做右旋处理
**p：二叉排序树
*********************************************/
void R_Rotate(BiTree *p)
{
   BiTree L;
   L = (*p)->lchild;               //L指向根节点的左子树
   (*p)->lchild = L->rchild;       //L的右子树挂在根节点的左子树上
   L->rchild = (*p);               
   (*p) = L;                        //p指向新的根节点
}

/*********************************************
**功能：对以p为根的二叉排序树做左旋处理
**p：二叉排序树
*********************************************/
void L_Rotate(BiTree *p)
{
   BiTree R;
   R = (*p)->rchild;
   (*p)->rchild = R->lchild;
   R->lchild = (*p);
   (*p) = R;
}

/*********************************************
**功能：对指针T所指结点为根的结点进行左平衡旋转处理
**T:二叉排序树
*********************************************/
void LeftBalance(BiTree *T)
{
   BiTree L,Lr;
   L = (*T)->lchild;               //L指向左子树根节点
   switch(L->bf)
   {
   case LH:                        //新节点插入在左孩子的左子树上，要作单右旋处理
      (*T)->bf = L->bf = EH;
      R_Rotate(T);
      break;
   case  RH:
      Lr = L->rchild;
      switch(Lr->bf)
      {
      case LH:
         (*T)->bf = RH;
         L->bf = EH;
         break;
      case EH:
         (*T)->bf=L->bf=EH;
         break;
      case RH:
         (*T)->bf = EH;
         L->bf = LH;
         break;
      }
      Lr->bf = EH;
      L_Rotate(&(*T)->lchild);           //对T的左子树做左旋处理
      R_Rotate(T);                       //对T做右旋处理
   }
}

/*********************************************
**功能：对指针T所指结点为根的结点进行右平衡旋转处理
**T:二叉排序树
*********************************************/
void RightBalance(BiTree *T)
{
   BiTree R,Rl;
   R = (*T)->rchild;
   switch(R->bf)
   {
   case RH:                 //此时，根节点和右子树结点平衡因子相同，直接对根节点左旋
      (*T)->bf = R->bf = EH;
      L_Rotate(T);
      break;
   case LH:
      Rl = R->lchild;       //指向右子树的根节点的左子树,异号，需要进行双旋处理
      switch(Rl->bf)
      {
      case RH:
         (*T)->bf = LH;
         R->bf = EH;
         break;
      case EH:
         (*T)->bf = R->bf=EH;
         break;
      case LH:(*T)->bf = EH;
         R->bf = RH;
         break;
      }
      Rl->bf = EH;
      R_Rotate(&(*T)->rchild);           //对T的右子树根节点做右旋操作
      L_Rotate(T);                       //对根节点T做左旋操作
   }
}

/*********************************************
**功能：平衡二叉树中插入一个结点e，若e不存在，插入并返回true，否则返回false
**T:平衡二叉树
**e:带插入结点
**taller：树是否增高
*********************************************/
int InsertAVL(BiTree *T,int e,int *taller)
{
   if(!*T)
   {
      *T =(BiTree)malloc(sizeof(BiTNode));
      (*T)->data = e;
      (*T)->lchild = NULL;
      (*T)->rchild = NULL;
      (*T)->bf = EH;
      *taller = 1;                      //表示树长高了
   }
   else
   {
      if (e == (*T)->data)             //该节点已经存在  不用插入了
      {
         *taller = 0;
         return 0;
      }
      if (e < (*T)->data)
      {
         if (!InsertAVL(&(*T)->lchild,e,taller))         //左子树中继续搜索  但是没有插入
         {
            return 0;
         }
         if (*taller)                                    //插入新的结点  并且树长高了
         {
            switch((*T)->bf)
            {
            case LH:                                     //原来左子树比右子树高，做左平衡处理
               LeftBalance(T);
               *taller = 0;
               break;
            case EH:                                     //原来左、右子树等高，现在左子树增高使树增高
               (*T)->bf = LH;
               *taller = 1;
               break;
            case RH:                                    //原来右子树较高，现在左右子树一样高
               (*T)->bf = EH;
               *taller = 0;
               break;
            }
         }
      }
      else                                            //右子树中进行搜索
      {
         if (!InsertAVL(&(*T)->rchild,e,taller))       //右子树中未插入
         {
            return 0;
         }
         if (*taller)
         {
            switch((*T)->bf)                         //检查T的平衡度
            {
            case LH:
               (*T)->bf = EH;
               *taller = 0;
               break;
            case EH:
               (*T)->bf = RH;
               *taller = 1;
               break;
            case RH:                               //本来右子树比左子树高，还在右子树插入结点，需要做右平衡处理
               RightBalance(T);
               *taller = 0;
               break;
            }
         }
      }
   }
   return 1;
}

/*********************************************
**功能：平衡二叉树中进行删除,又该节点，删除并返回true，若没有该节点，返回false
**T:平衡二叉树
**e:删除的结点键值
**shorter:树的高度是否降低
*********************************************/
int DeleteAVL(BiTree *T,int e,int* shorter)
{
   //提示：插入结点使用的递归插入，可以联想到删除也是用的递归删除
   if (!*T)                 //不存在该节点
   {
      return 0;
   }
   else if ((*T)->data == e)      //找到该节点
   {
      BiTree q;
      if (!(*T)->lchild)          //如果左子树为空，只需要重接右子树
      {
         q = (*T);
         (*T) = (q->rchild);
         free(q);
         *shorter = 1;
      }
      else if (!(*T)->rchild)    //右子树为空，只需要重接左子树
      {
         q = (*T);
         (*T) = q->lchild;
         free(q);
         *shorter = 1;
      }
      else                       //左右子树都不为空
      {
         q = (*T)->lchild;       //先向左，然后向右到尽头
         while(q->rchild)
         {
            q = q->rchild;
         }
         (*T)->data = q->data;
         DeleteAVL(&(*T)->lchild,q->data,shorter);             //左子树中递归删除前驱结点
      }
   }
   else if (e < (*T)->data)       //左子树中递归查找
   {
      if (!DeleteAVL(&(*T)->lchild,e,shorter))       //没找到
      {
         return 0;
      }
      if (*shorter)                                //删除结点，而且高度降低
      {
         switch((*T)->bf)
         {
         case LH:
            (*T)->bf = EH;
            *shorter = 1;
            break;
         case EH:
            (*T)->bf = RH;
            *shorter = 0;
            break;
         case RH:                              //右边本来就高  左边删除后，需要进行右平衡处理
            RightBalance(T);
            if ((*T)->rchild->bf == EH)        //画图看一下，很easy
            {
               *shorter = 0;
            }
            else
            {
               *shorter = 1;
            }
            break;
         }
      }
   }
   else                          //右子树中递归查找
   {
      if (!DeleteAVL(&(*T)->rchild,e,shorter))       //没找到
      {
         return 0;
      }
      if (*shorter)                                //删除结点，而且高度降低
      {
         switch((*T)->bf)
         {
         case LH:
            LeftBalance(T);
            if((*T)->lchild->bf == EH)             //画图，不多说
            {
               *shorter = 0;
            }
            else
            {
               *shorter = 1;
            }
            break;
         case EH:
            (*T)->bf = LH;
            *shorter = 0;
            break;
         case RH:
            (*T)->bf = EH;
            *shorter = 1;
            break;
         }
      }
   }
   return 0;
}

/*********************************************
**功能：递归打印二叉树,中序遍历
**T:二叉排序树
*********************************************/
void PrintBTree(BiTree T)
{
   if (!T)                    //递归出口
      return;
   PrintBTree(T->lchild);
   printf("%d\t",T->data);
   PrintBTree(T->rchild);
}

int _tmain(int argc, _TCHAR* argv[])
{
   int a[] = {3,2,1,4,5,6,7,10,9,8};
   BiTree T = NULL;
   int taller;
   for (int i=0;i<10;++i)
   {
      InsertAVL(&T,a[i],&taller);
   }
   PrintBTree(T);
   int shorter;
   DeleteAVL(&T,10,&shorter);
   PrintBTree(T);
   printf("\n");

   return 0;
}

