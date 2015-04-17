/********************************************************************
*This function to do HeapSort
*Author:xiefanfan
*Time:2015-04-04  10:25
*All Rights Reseved
********************************************************************/
#include "stdafx.h"
#include <stdio.h>

/*******************this function to do heap sort based on large root heap*************************/
/*********************对R[s]~R[t]除R[s]外均满足堆得定义，即只对R[s]进行调整，使R[s]为根的完全二叉树成为一个堆***********************/
void HeapAdjust(int R[],int s,int t)
{
	int i,j;
	int temp = R[s];               //temprory variable
	i=s;
	for (j=2*i;j<=t;j=2*j)         //沿关键字较大的孩子向下调整，先假定为左孩子   
	{
		if (j<t&&R[j]<R[j+1])     //如果左孩子比右孩子小，则沿右孩子向下调整
		{
			j=j+1;
		}
		if (temp>R[j])            //如果temp比左右孩子都大，满足大根堆的定义了，不在向下调整
		{
			break;
		}
		R[i]=R[j];                //将关键字较大的孩子节点和双亲节点交换
		i=j;                      //定位于孩子节点  继续向下调整
	}
	R[i]=temp;                    //找到合适的位置，将temp放置进去
}

//进行堆排序，R[]是一个数组，n是数组的个数
void HeapSort(int R[],int n)
{
	int i;
	for (i=n/2;i>0;i--)              //完全二叉树  非终端节点需要进行堆定义调整，从R[n/2],R[n/2-1],.....R[0]
	{
		HeapAdjust(R,i,n);
	}
	int temp;
	for (i=n;i>0;i--)                //对初始堆进行n-1趟排序
	{
		temp = R[1];
		R[1] = R[i];
		R[i] = temp;
		HeapAdjust(R,1,i-1);         //将未排序的前i-1个节点重新调整为堆
	}	
}

int main()
{
	int shuzu[] = {0,61,33,48,82,72,11,25,48};
	HeapSort(shuzu,8);                 //调用堆排序函数
	int index;
	for(index=1;index<9;++index)
	{
		printf("%d\t",shuzu[index]);
	}
}

