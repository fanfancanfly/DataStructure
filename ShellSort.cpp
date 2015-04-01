/********************************************************************
*This function to do InsertSort
*Author:xiefanfan
*Time:2015-04-01  21:10
*All Rights Reseved
********************************************************************/
#include "stdafx.h"
#include <stdio.h>

void ShellSort(int shuzu[],int num);
int _tmain(int argc, _TCHAR* argv[])
{
	int shuzu[] = {48,33,61,96,72,11,25,14,56,87,101,9};       //待排序数组
	int i,j;
	int temp;										//临时变量

	ShellSort(shuzu,12);                            //调用shell排序函数
	for (int i=0;i<12;++i)                         //打印结果
	{
		printf("%d\t",shuzu[i]);	
		printf("\n");
	}

	return 0;
}

//功能：shell排序
//参数：
//shuzu:输入的待排序数组
//num:数组的个数
void ShellSort(int shuzu[],int num)
{
	int i,j;
	int temp;                                       //临时暂存变量
	int increment = num;                            //增量变量
	do 
	{
		increment = increment/3 +1;                 //增量减少
		for (i=increment;i<num;i++)
		{			
			if (shuzu[i] < shuzu[i-increment])      //插入排序
			{
				temp = shuzu[i];
				j = i-increment;
				while (shuzu[j] > temp)             //比第i个位置大的元素往后移动
				{
					shuzu[j+increment] = shuzu[j];
					j = j-increment;
				}
				shuzu[j+increment] = temp;          //放到合适的位置
			}
		}
	} while (increment >1);
}

