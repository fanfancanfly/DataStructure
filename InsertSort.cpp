// creadtxt.cpp : �������̨Ӧ�ó������ڵ㡣
/********************************************************************
*This function to do InsertSort
*Author:xiefanfan
*Time:2015-04-01  21:10
********************************************************************/

#include "stdafx.h"
#include <stdio.h>

int _tmain(int argc, _TCHAR* argv[])
{
	int shuzu[] = {48,33,61,96,72,11,25,14};       //����������
	int i,j;
	int temp;										//��ʱ����
	for (int i = 1; i < 8; ++i)
	{
		temp = shuzu[i];
		if ( shuzu[i] < shuzu[i-1])                //��i�����ź�������һ��С������i�����뵽ǰ������������ȥ
		{
			j = i-1;
			while ( shuzu[j] > temp)              //ֻҪ�ȵ�i���������ƶ�
			{
				shuzu[j+1] = shuzu[j];
				j--;
			}
			shuzu[j+1] = temp;                    //���뵽���ʵ�λ��
		}
	}
	for (int i=0;i<8;++i)                         //��ӡ���
	{
		printf("%d\t",shuzu[i]);	
		printf("\n");
	}

	return 0;
}

