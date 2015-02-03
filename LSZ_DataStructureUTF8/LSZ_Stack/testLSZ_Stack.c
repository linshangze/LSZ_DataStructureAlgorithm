/********************************************************************
 *File Name: testLSZ_Stack.c
 *Author: Linshangze//林上泽
 *Mail: linshangze163@163.com
 *Created Time: 2013-05-21
 *Updated Time: 2015-01-20
 *******************************************************************/

/********************************************************************
 *test file for LSZ_Stack
 *LSZ_Stack测试源文件
 *******************************************************************/

#include <stdio.h>
#include "LSZ_Stack.h"

int main(void)
{
	LSZ_StackCtl stack;
	LSZ_MT data;
	char temp;
	int i;

	LSZ_Stack_init(&stack);
	LSZ_MT_init(&data);

	printf("init, size: %d\n", LSZ_Stack_size(&stack));
	printf("init, top: %d\n", LSZ_Stack_top(&stack, &data));
	for(i = 0; i < 5; i++){
		temp = 'A' + i;
		LSZ_MT_wt(&data, &temp);
		if(LSZ_Stack_push(&stack, &data) != 0)
			printf("push: what happened??\n");
		else
			printf("push: %c\n", temp);
	}
	printf("push: ok\n\n");

	for(i = 0; i < 5; i++){
		if(LSZ_Stack_top(&stack, &data) == 0){
			LSZ_MT_rd(&temp, &data);
			printf("top: %c\n", temp);
		}else
			printf("top: what happened??\n");

	}
	printf("top, ok\n\n");

	for(i = 0; LSZ_Stack_size(&stack) > 0; i++){
		if(LSZ_Stack_pop(&stack, &data) == 0){
			LSZ_MT_rd(&temp, &data);
			printf("pop: %c\n", temp);
		}else{
			if(i >= 5)
				printf("pop: ok\n");
			else
				printf("pop: what happened??\n");
		}
	}
	printf("top, ok\n");

	LSZ_Stack_dest(&stack);
	printf("dest, size: %d\n", LSZ_Stack_size(&stack));

	return 0;
}
