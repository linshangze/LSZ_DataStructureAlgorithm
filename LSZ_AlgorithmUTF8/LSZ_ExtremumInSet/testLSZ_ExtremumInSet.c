/*********************************************************************
 * File Name: testLSZ_ExtremumInSet.c
 * Author: linshangze
 * Mail: linshangze163@163.com 
 * Created Time: 2014-01-13-10:07:17 HKT
 ********************************************************************/

#include <stdio.h>
#include "LSZ_ExtremumInSet.c"

int methodIntegerGreater(int set[], int index1, int index2)
{
	return set[index1] > set[index2] ? index1 : index2;
}

int methodIntegerLess(int set[], int index1, int index2)
{
	return set[index1] < set[index2] ? index1 : index2;
}

int main(void)
{
	int set[] = {1, 3, 5, 7, 9, 0, 2, 4, 6, 8};
	int result1, result2;

	//测试正确下标0～9，0～0，9～9
	//测试错误的下标10～9
	result1 = LSZ_getExtremumInSet(methodIntegerGreater, set, 0, 9);
	result2 = LSZ_getExtremumInSet(methodIntegerLess, set, 0, 9);
	printf("%d, %d\n", result1, result2);
	return 0;
}

