/********************************************************************
 *File Name: testLSZ_LinearListSq.c
 *Author: Linshangze//林上泽
 *Mail: linshangze163@163.com
 *Created Time: 2013-05-15
 *Updated Time: 2015-01-14
 *******************************************************************/

/********************************************************************
 *test file for LSZ_LinearListSq
 *LSZ_LinearListSq测试源文件
 *******************************************************************/

#include <stdio.h>
#include <malloc.h>

typedef char LSZ_LLStLData;
#include "LSZ_LinearListStL.h"
LSZ_LLStLNode space[20];

int main()
{
	int i, j;

	if(LSZ_LLStL_init(space, 20) != 0){
		printf("initailizing fail\n");
		return 0;
	}

	for(j = 0; j < 20 - 1; j++){
		if((i = LSZ_LLStL_malloc()) <= 0){
			printf("fail to malloc\n");
			return 0;
		}
		else{
			printf("malloc %d\n", i);
		}
	}

	for(i = 1, j = 0; j < 20 - 1; j++, i++)
	if((i = LSZ_LLStL_free(i)) <= 0){
		printf("fail to free %d\n", i);
		return 0;
	}
	else{
		printf("free %d\n", i);
	}

	for(j = 0; j < 20; j++){
		if((i = LSZ_LLStL_malloc()) <= 0){
			printf("fail to malloc\n");
			return 0;
		}
		else{
			printf("malloc %d\n", i);
		}
		if((j = LSZ_LLStL_malloc()) <= 0){
			printf("fail to malloc\n");
			return 0;
		}
		else{
			printf("malloc %d\n", j);
		}
		if((j = LSZ_LLStL_free(j)) <= 0){
			printf("fail to free %d\n", j);
			return 0;
		}
		else{
			printf("free %d\n", j);
		}
	}

	return 0;
}
