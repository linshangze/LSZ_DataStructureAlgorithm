/*********************************************************************
 * File Name: testLSZ_SortQuick.c
 * Author: linshangze
 * Mail: linshangze163@163.com 
 * Created Time: 2014-01-28-10:53:51 HKT
 ********************************************************************/

#include <stdio.h>
#include "LSZ_SortQuick.c"

int main()
{
//	int array[] = {6, 7, 5, 2, 5, 8};
//	int array[] = {6, 1, 1, 1, 1, 1};
//	int array[] = {1, 6, 6, 6, 6, 6};
	int array[] = {6, 6, 6, 6, 6, 6};
//	int array[] = {1};
	int i;
	int ARRAY_COUNT = sizeof(array)/sizeof(int);

	printf("array:\n");
	for(i = 0; i < ARRAY_COUNT; i++){
		printf("%d,", array[i]);
	}
	printf("\n");
	LSZ_sort_quick(array, 0, ARRAY_COUNT - 1);
	printf("array:\n");
	for(i = 0; i < ARRAY_COUNT; i++){
		printf("%d,", array[i]);
	}
	printf("\n");
	return 0;
}
