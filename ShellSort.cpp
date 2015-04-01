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
	int shuzu[] = {48,33,61,96,72,11,25,14,56,87,101,9};       //����������
	int i,j;
	int temp;										//��ʱ����

	ShellSort(shuzu,12);                            //����shell������
	for (int i=0;i<12;++i)                         //��ӡ���
	{
		printf("%d\t",shuzu[i]);	
		printf("\n");
	}

	return 0;
}

//���ܣ�shell����
//������
//shuzu:����Ĵ���������
//num:����ĸ���
void ShellSort(int shuzu[],int num)
{
	int i,j;
	int temp;                                       //��ʱ�ݴ����
	int increment = num;                            //��������
	do 
	{
		increment = increment/3 +1;                 //��������
		for (i=increment;i<num;i++)
		{			
			if (shuzu[i] < shuzu[i-increment])      //��������
			{
				temp = shuzu[i];
				j = i-increment;
				while (shuzu[j] > temp)             //�ȵ�i��λ�ô��Ԫ�������ƶ�
				{
					shuzu[j+increment] = shuzu[j];
					j = j-increment;
				}
				shuzu[j+increment] = temp;          //�ŵ����ʵ�λ��
			}
		}
	} while (increment >1);
}

