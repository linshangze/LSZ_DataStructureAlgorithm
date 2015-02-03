/*********************************************************************
 * File Name: testMatrixChainMultiplication.c
 * Author: linshangze
 * Mail: linshangze163@163.com 
 * Created Time: 2013-10-14-06:03:08 PM
 ********************************************************************/

#include <stdio.h>

#include "LSZ_MatrixChainMultiplication.c" //为了方便测试

#define MATRICES_COUNT 3 //相乘矩阵的个数

void printAarry(int *array[], int countI, int countJ) //输出数组
{
	int i, j;

	for(i = 0; i < countI; i++){
		for(j = 0; j < countJ; j++){
			printf("%-16d", array[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int main(void)
{
	//int rowColumn[] = {8, 4, 8, 2}, //记录矩阵的维数
	int rowColumn[] = {10, 100, 5, 50}, //记录矩阵的维数
		*rowColumnFix = rowColumn + 1; //对rowColumn数组的使用会出现-1下标
	int pointTemp[MATRICES_COUNT][MATRICES_COUNT], //记录矩阵划分点
		countTemp[MATRICES_COUNT][MATRICES_COUNT], //记录相乘运算次数
		*(breakPoint[MATRICES_COUNT]),
		*(countMul[MATRICES_COUNT]);
	int i, j;

	for(i = 0; i < MATRICES_COUNT; i++){ //给指针数组赋值
		breakPoint[i] = pointTemp[i];
		countMul[i] = countTemp[i];
	}
	for(i = 0; i < MATRICES_COUNT; i++){ //初始化数组，为了好看
		for(j = 0; j < MATRICES_COUNT; j++){
			breakPoint[i][j] = -1;
			countMul[i][j] = -1;
		}
	}

	printf("***************************\n");
	printf("the count of multiplication is %d in recursion function\n",
			LSZ_Matrix_countChainMulRecursion(rowColumnFix,
				breakPoint, 0, MATRICES_COUNT - 1));
	printf("breakPoint array:\n");
	printAarry(breakPoint, MATRICES_COUNT, MATRICES_COUNT);

	printf("***************************\n");
	printf("the count of multiplication is %d in dynamic function\n",
			LSZ_Matrix_countChainMulDynamic(rowColumnFix,
				breakPoint, countMul, MATRICES_COUNT));
	printf("breakPoint array:\n");
	printAarry(breakPoint, MATRICES_COUNT, MATRICES_COUNT);
	printf("count of multiplication array:\n");
	printAarry(countMul, MATRICES_COUNT, MATRICES_COUNT);

	printf("***************************\n");
	printf("the count of multiplication is %d in dynamic function\n",
			LSZ_Matrix_countChainMulDynamicImprove(rowColumnFix,
				breakPoint, MATRICES_COUNT));
	printf("breakPoint array and count of multiplication array:\n");
	printAarry(breakPoint, MATRICES_COUNT, MATRICES_COUNT);

	printf("***************************\n");
	printf("the simulation of matrices multiplication is:\n");
	for(i = 0; i < MATRICES_COUNT; i++){
		printf("m[%d](%d,%d) * ", i, rowColumn[i], rowColumn[i + 1]);
	}
	printf("\b\b \n");
	LSZ_Matrix_multiplyChainSimulation(breakPoint, 0, MATRICES_COUNT - 1);
	printf("\n");

	return 0;
}
