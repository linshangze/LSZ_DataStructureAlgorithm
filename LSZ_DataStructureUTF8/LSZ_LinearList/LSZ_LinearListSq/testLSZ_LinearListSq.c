/********************************************************************
 *File Name: testLSZ_LinearListSq.c
 *author: Linshangze//林上泽
 *Mail: linshangze163@163.com
 *date: 2013-05-15
 *******************************************************************/

/********************************************************************
 *test file for LSZ_LinearListSq
 *LSZ_LinearListSq测试源文件
 *******************************************************************/

#include <stdio.h>
#include <malloc.h>
#include "LSZ_LinearListSq.h"

int main()
{

	int array0[10] = {1, 2, 3, 4, 6};
	int array1[5] = {6, 7, 8, 9, 10};
	int x = 5;
	int i;

	printf("begin:\n");
	for(i = 0; i < 5; i++)
		printf("%d\t", array0[i]);
	printf("\n");

	LSZ_LLSq_add(array0, 5, &x, 0);
	printf("after add:\n");
	for(i = 0; i < 6; i++)
		printf("%d\t", array0[i]);
	printf("\n");

	LSZ_LLSq_del(array0, 6, &x, 5);
	printf("after del\n");
	for(i = 0; i < 5; i++)
		printf("%d\t", array0[i]);
	printf("\n%d deleted\n", x);

	LSZ_LLSq_append(array0, 5, array1, 5);
	printf("after append\n");
	for(i = 0; i < 10; i++)
		printf("%d\t", array0[i]);
	printf("\n");

	LSZ_LLSq_reverse(array0, 10);
	printf("after reverse\n");
	for(i = 0; i < 10; i++)
		printf("%d\t", array0[i]);
	printf("\n");

	return 0;
}
