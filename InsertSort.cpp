// creadtxt.cpp : 定义控制台应用程序的入口点。
/********************************************************************
*This function to do InsertSort
*Author:xiefanfan
*Time:2015-04-01  21:10
********************************************************************/

#include "stdafx.h"
#include <stdio.h>

int _tmain(int argc, _TCHAR* argv[])
{
	int shuzu[] = {48,33,61,96,72,11,25,14};       //带排序数组
	int i,j;
	int temp;										//临时变量
	for (int i = 1; i < 8; ++i)
	{
		temp = shuzu[i];
		if ( shuzu[i] < shuzu[i-1])                //地i个比排好序的最后一个小，将第i个插入到前边有序数组中去
		{
			j = i-1;
			while ( shuzu[j] > temp)              //只要比第i个大，往后移动
			{
				shuzu[j+1] = shuzu[j];
				j--;
			}
			shuzu[j+1] = temp;                    //插入到合适的位置
		}
	}
	for (int i=0;i<8;++i)                         //打印结果
	{
		printf("%d\t",shuzu[i]);	
		printf("\n");
	}

	return 0;
}

