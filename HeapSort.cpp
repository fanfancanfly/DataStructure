/********************************************************************
*This function to do HeapSort
*Author:xiefanfan
*Time:2015-04-04  10:25
*All Rights Reseved
********************************************************************/
#include "stdafx.h"
#include <stdio.h>

/*******************this function to do heap sort based on large root heap*************************/
/*********************��R[s]~R[t]��R[s]�������ѵö��壬��ֻ��R[s]���е�����ʹR[s]Ϊ������ȫ��������Ϊһ����***********************/
void HeapAdjust(int R[],int s,int t)
{
	int i,j;
	int temp = R[s];               //temprory variable
	i=s;
	for (j=2*i;j<=t;j=2*j)         //�عؼ��ֽϴ�ĺ������µ������ȼٶ�Ϊ����   
	{
		if (j<t&&R[j]<R[j+1])     //������ӱ��Һ���С�������Һ������µ���
		{
			j=j+1;
		}
		if (temp>R[j])            //���temp�����Һ��Ӷ����������ѵĶ����ˣ��������µ���
		{
			break;
		}
		R[i]=R[j];                //���ؼ��ֽϴ�ĺ��ӽڵ��˫�׽ڵ㽻��
		i=j;                      //��λ�ں��ӽڵ�  �������µ���
	}
	R[i]=temp;                    //�ҵ����ʵ�λ�ã���temp���ý�ȥ
}

//���ж�����R[]��һ�����飬n������ĸ���
void HeapSort(int R[],int n)
{
	int i;
	for (i=n/2;i>0;i--)              //��ȫ������  ���ն˽ڵ���Ҫ���жѶ����������R[n/2],R[n/2-1],.....R[0]
	{
		HeapAdjust(R,i,n);
	}
	int temp;
	for (i=n;i>0;i--)                //�Գ�ʼ�ѽ���n-1������
	{
		temp = R[1];
		R[1] = R[i];
		R[i] = temp;
		HeapAdjust(R,1,i-1);         //��δ�����ǰi-1���ڵ����µ���Ϊ��
	}	
}

int main()
{
	int shuzu[] = {0,61,33,48,82,72,11,25,48};
	HeapSort(shuzu,8);                 //���ö�������
	int index;
	for(index=1;index<9;++index)
	{
		printf("%d\t",shuzu[index]);
	}
}

