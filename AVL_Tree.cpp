// cplusplus_test.cpp : �������̨Ӧ�ó������ڵ㡣
//ƽ��������о�

#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#define LH 1            //���
#define EH 0            //�ȸ�
#define RH -1           //�Ҹ�

using namespace std;

typedef struct BiTNode          //���ṹ��
{
   int data;
   int bf;                      //���ƽ������
   struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

/*********************************************
**���ܣ�����pΪ���Ķ�������������������
**p������������
*********************************************/
void R_Rotate(BiTree *p)
{
   BiTree L;
   L = (*p)->lchild;               //Lָ����ڵ��������
   (*p)->lchild = L->rchild;       //L�����������ڸ��ڵ����������
   L->rchild = (*p);               
   (*p) = L;                        //pָ���µĸ��ڵ�
}

/*********************************************
**���ܣ�����pΪ���Ķ�������������������
**p������������
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
**���ܣ���ָ��T��ָ���Ϊ���Ľ�������ƽ����ת����
**T:����������
*********************************************/
void LeftBalance(BiTree *T)
{
   BiTree L,Lr;
   L = (*T)->lchild;               //Lָ�����������ڵ�
   switch(L->bf)
   {
   case LH:                        //�½ڵ���������ӵ��������ϣ�Ҫ������������
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
      L_Rotate(&(*T)->lchild);           //��T������������������
      R_Rotate(T);                       //��T����������
   }
}

/*********************************************
**���ܣ���ָ��T��ָ���Ϊ���Ľ�������ƽ����ת����
**T:����������
*********************************************/
void RightBalance(BiTree *T)
{
   BiTree R,Rl;
   R = (*T)->rchild;
   switch(R->bf)
   {
   case RH:                 //��ʱ�����ڵ�����������ƽ��������ͬ��ֱ�ӶԸ��ڵ�����
      (*T)->bf = R->bf = EH;
      L_Rotate(T);
      break;
   case LH:
      Rl = R->lchild;       //ָ���������ĸ��ڵ��������,��ţ���Ҫ����˫������
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
      R_Rotate(&(*T)->rchild);           //��T�����������ڵ�����������
      L_Rotate(T);                       //�Ը��ڵ�T����������
   }
}

/*********************************************
**���ܣ�ƽ��������в���һ�����e����e�����ڣ����벢����true�����򷵻�false
**T:ƽ�������
**e:��������
**taller�����Ƿ�����
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
      *taller = 1;                      //��ʾ��������
   }
   else
   {
      if (e == (*T)->data)             //�ýڵ��Ѿ�����  ���ò�����
      {
         *taller = 0;
         return 0;
      }
      if (e < (*T)->data)
      {
         if (!InsertAVL(&(*T)->lchild,e,taller))         //�������м�������  ����û�в���
         {
            return 0;
         }
         if (*taller)                                    //�����µĽ��  ������������
         {
            switch((*T)->bf)
            {
            case LH:                                     //ԭ�����������������ߣ�����ƽ�⴦��
               LeftBalance(T);
               *taller = 0;
               break;
            case EH:                                     //ԭ�����������ȸߣ���������������ʹ������
               (*T)->bf = LH;
               *taller = 1;
               break;
            case RH:                                    //ԭ���������ϸߣ�������������һ����
               (*T)->bf = EH;
               *taller = 0;
               break;
            }
         }
      }
      else                                            //�������н�������
      {
         if (!InsertAVL(&(*T)->rchild,e,taller))       //��������δ����
         {
            return 0;
         }
         if (*taller)
         {
            switch((*T)->bf)                         //���T��ƽ���
            {
            case LH:
               (*T)->bf = EH;
               *taller = 0;
               break;
            case EH:
               (*T)->bf = RH;
               *taller = 1;
               break;
            case RH:                               //�������������������ߣ����������������㣬��Ҫ����ƽ�⴦��
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
**���ܣ�ƽ��������н���ɾ��,�ָýڵ㣬ɾ��������true����û�иýڵ㣬����false
**T:ƽ�������
**e:ɾ���Ľ���ֵ
**shorter:���ĸ߶��Ƿ񽵵�
*********************************************/
int DeleteAVL(BiTree *T,int e,int* shorter)
{
   //��ʾ��������ʹ�õĵݹ���룬�������뵽ɾ��Ҳ���õĵݹ�ɾ��
   if (!*T)                 //�����ڸýڵ�
   {
      return 0;
   }
   else if ((*T)->data == e)      //�ҵ��ýڵ�
   {
      BiTree q;
      if (!(*T)->lchild)          //���������Ϊ�գ�ֻ��Ҫ�ؽ�������
      {
         q = (*T);
         (*T) = (q->rchild);
         free(q);
         *shorter = 1;
      }
      else if (!(*T)->rchild)    //������Ϊ�գ�ֻ��Ҫ�ؽ�������
      {
         q = (*T);
         (*T) = q->lchild;
         free(q);
         *shorter = 1;
      }
      else                       //������������Ϊ��
      {
         q = (*T)->lchild;       //������Ȼ�����ҵ���ͷ
         while(q->rchild)
         {
            q = q->rchild;
         }
         (*T)->data = q->data;
         DeleteAVL(&(*T)->lchild,q->data,shorter);             //�������еݹ�ɾ��ǰ�����
      }
   }
   else if (e < (*T)->data)       //�������еݹ����
   {
      if (!DeleteAVL(&(*T)->lchild,e,shorter))       //û�ҵ�
      {
         return 0;
      }
      if (*shorter)                                //ɾ����㣬���Ҹ߶Ƚ���
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
         case RH:                              //�ұ߱����͸�  ���ɾ������Ҫ������ƽ�⴦��
            RightBalance(T);
            if ((*T)->rchild->bf == EH)        //��ͼ��һ�£���easy
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
   else                          //�������еݹ����
   {
      if (!DeleteAVL(&(*T)->rchild,e,shorter))       //û�ҵ�
      {
         return 0;
      }
      if (*shorter)                                //ɾ����㣬���Ҹ߶Ƚ���
      {
         switch((*T)->bf)
         {
         case LH:
            LeftBalance(T);
            if((*T)->lchild->bf == EH)             //��ͼ������˵
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
**���ܣ��ݹ��ӡ������,�������
**T:����������
*********************************************/
void PrintBTree(BiTree T)
{
   if (!T)                    //�ݹ����
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

