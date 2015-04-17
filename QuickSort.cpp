/********************************************************************
*This function to do QuickSort
*Author:xiefanfan
*Time:2015-04-01  21:10
*All Rights Reseved
********************************************************************/
#include "stdafx.h"
#include <stdio.h>

/*****************This step is to do the partion step in quicksort********************/
/********************the main step of quicksort**************************************/
int Partion(int R[],int i,int j)
{
	int temp;
	temp = R[i];                                   //make i-th variable as the token variable
	while(i < j)
	{
		while(i<j&&R[j] >= temp)
		{
			j--;
		}
		if (i<j)
		{
			R[i] = R[j];
			i++;
		}
		while(i<j&&R[i] <= temp)
		{
			i++;
		}
		if(i<j)
		{
			R[j] = R[i];
			j--;
		}
	}
	R[i] = temp;
	return i;
}
/******************************do the quicksort step***********************************/
void QuickSort(int R[],int s,int t)
{
	int j;        //tempory variable,to save the return value of function Partion();
	if(s<t)       //next steps,it is recursion
	{
		j = Partion(R,s,t);
		QuickSort(R,s,j-1);
		QuickSort(R,j+1,t);
	}
}

int main()
{
	int shuzu[] = {61,33,48,82,72,11,25,48};
	QuickSort(shuzu,0,7);
	int index;
	for(index=0;index<8;++index)
	{
		printf("%d\t",shuzu[index]);
	}
}

