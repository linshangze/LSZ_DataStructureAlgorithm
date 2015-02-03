/*********************************************************************
 * File Name: testLSZ_Matrix.c
 * Author: linshangze
 * Mail: linshangze163@163.com
 * Created Time: 2015-01-20-09:59:49 PM
 * Updated  Time: 2015-01-20-09:59:49 PM
 ********************************************************************/

#include <stdio.h>
#include "LSZ_Matrix.c"

#define ARRAYSIZE 5 //矩阵阶
#define DIAGLINE  5 //对角阵非零对角线数

int main(void)
{
	int i, j, index;
	int symmArray[LSZ_Matrix_symmSize(ARRAYSIZE)]; 
	int diagArray[LSZ_Matrix_diagSize(ARRAYSIZE, DIAGLINE)];

	for(i = 0; i < LSZ_Matrix_symmSize(ARRAYSIZE); i++)
		symmArray[i] = 'a' + i;
	printf("symmetria matrix, size: %d\n", LSZ_Matrix_symmSize(ARRAYSIZE));
	for(i = 0; i < ARRAYSIZE; i++){
		for(j = 0; j < ARRAYSIZE; j++)
			printf("%c ", symmArray[LSZ_Matrix_symmIndex(i, j)]);
		printf("\n");
	}
	printf("\n");

	for(i = 0; i < ARRAYSIZE; i++){
		for(j = 0; j < ARRAYSIZE; j++){
			index = LSZ_Matrix_diagIndex(ARRAYSIZE, DIAGLINE, i, j);
			if(index>= 0)
				diagArray[index] = 'A' + i * ARRAYSIZE + j;
		}
		printf("\n");
	}
	printf("diagoal	matrix, size: %d\n",
		LSZ_Matrix_diagSize(ARRAYSIZE, DIAGLINE));
	for(i = 0; i < ARRAYSIZE; i++){
		for(j = 0; j < ARRAYSIZE; j++){
			index = LSZ_Matrix_diagIndex(ARRAYSIZE, DIAGLINE, i, j);
			if(index>= 0)
				printf("%c ", diagArray[index]);
			else
				printf("0 ");
		}
		printf("\n");
	}
	printf("\n");

	return 0;
}

