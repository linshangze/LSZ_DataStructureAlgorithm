/********************************************************************
 *File Name: testLSZ_LinearListCL.c
 *Author: Linshangze//林上泽
 *Mail: linshangze163@163.com
 *Created Time: 2013-05-16
 *Updated Time: 2015-01-20
 *******************************************************************/

/********************************************************************
 *test file for LSZ_LinearListCL
 *LSZ_LinearListCL测试源文件
 *******************************************************************/

#include "LSZ_LinearListCL.h"

int checkFunShow(LSZ_MT *data);

int main()
{
	LSZ_LLCLCtl control1, control2;
	LSZ_MT data;
	char temp;
	int i;
	int (*func)(LSZ_MT*) = checkFunShow;
	LSZ_LLCLNode *node;

	LSZ_LLCL_init(&control1);
	LSZ_MT_init(&data);
	printf("init, size: %d\n", LSZ_LLCL_size(&control1));

	temp = 'a', i = 1; //第一个结点序号为0
	LSZ_MT_wt(&data, &temp);
	printf("add index = %d, size: %d, index = %d,  %c\n",
			i, LSZ_LLCL_size(&control1),
			LSZ_LLCL_add(&control1, &data, i), temp);
	temp = 'b', i = 0;
	LSZ_MT_wt(&data, &temp);
	printf("add index = %d, size: %d, index = %d,  %c\n",
			i, LSZ_LLCL_size(&control1),
			LSZ_LLCL_add(&control1, &data, i), temp);
	temp = 'c', i = 3;
	LSZ_MT_wt(&data, &temp);
	printf("add index = %d, size: %d, index = %d,  %c\n",
			i, LSZ_LLCL_size(&control1),
			LSZ_LLCL_add(&control1, &data, i), temp);
	temp = 'd', i = 5;
	LSZ_MT_wt(&data, &temp);
	printf("add index = %d, size: %d, index = %d,  %c\n",
			i, LSZ_LLCL_size(&control1),
			LSZ_LLCL_add(&control1, &data, i), temp);

	for(i = 0; i < 10; i++){
		LSZ_LLCL_rd(&control1, &data, i);
		LSZ_MT_rd(&temp, &data);
		printf("rd, %d, %c\n", i, temp);
	}

	temp = 'z';
	i = 0;
	LSZ_MT_wt(&data, &temp);
	LSZ_LLCL_wt(&control1, &data, i);
	printf("wt index = %d: %c\n", i, temp);

	i = LSZ_LLCL_trav(&control1, 0, func, &data);
	LSZ_MT_rd(&temp, &data);
	printf("trav : %c index = %d\n", temp, i);

	i = -5;
	node = LSZ_LLCL_findNode(&control1, i);
	LSZ_MT_rd(&temp, &(node->data));
	printf("findNode : %c index = %d\n", temp, i);
	LSZ_MT_rd(&temp, &(LSZ_LLCL_nextNode(node)->data));
	printf("nextNode : %c index = %d\n", temp, i - 1);
	LSZ_MT_rd(&temp, &(LSZ_LLCL_priorNode(node)->data));
	printf("priorNode : %c index = %d\n", temp, i + 1);

	LSZ_LLCL_init(&control2);
	for(i = 0; i < 3; i++){
		temp = 'i' + i;
		LSZ_MT_wt(&data, &temp);
		LSZ_LLCL_add(&control2, &data, 0);
		LSZ_LLCL_swapNode(&control2, LSZ_LLCL_findNode(&control2, 0),
			&control1, LSZ_LLCL_findNode(&control1, i));
		LSZ_LLCL_swapNode(&control2, LSZ_LLCL_findNode(&control2, i),
			&control2, LSZ_LLCL_findNode(&control2, i - 1));
	}
	for(i = 0; i < 3; i++){
		LSZ_LLCL_rd(&control2, &data, i);
		LSZ_MT_rd(&temp, &data);
		printf("swap : index = %d, %c\n", i, temp);
	}

	LSZ_LLCL_append(&control1, &control2);
	printf("append, size1: %d\n", LSZ_LLCL_size(&control1));
	printf("append, size2: %d\n", LSZ_LLCL_size(&control2));
	for(i = 0; i < 20; i++){
		LSZ_LLCL_rd(&control1, &data, i);
		LSZ_MT_rd(&temp, &data);
		printf("append, index = %d, %c\n", i, temp);
	}

	LSZ_LLCL_dest(&control1);
	LSZ_LLCL_dest(&control2);
	return 0;
}


int checkFunShow(LSZ_MT *data)
{
	char temp;

	LSZ_MT_rd(&temp, data);
	printf("check : %c\n", temp);
	if(temp == 'a')
		return 1;
	return 0;
}
