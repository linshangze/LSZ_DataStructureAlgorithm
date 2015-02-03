/********************************************************************
 *author: Linshangze//林上泽
 *date: 2012-08-14
 *file name: testLSZ_LinearListL.c
 *******************************************************************/

/********************************************************************
 *test file for LSZ_LinearListL
 *LSZ_LinearListL测试源文件
 *******************************************************************/

#include <stdio.h>
#include <malloc.h>
#include "LSZ_LinearListL.h"

int LSZ_LLL_checkFun(LSZ_MT *data);

int main()
{
	LSZ_LLLCtl ctrl; //control of a LSZ_LinearList控制结构
	LSZ_MT data; //临时结点数据元素。
	char data0 = 'a';
	int data1 = 1;
	char data2[] = "hello";
	union {
		char data0;
		int data1;
		char data2[sizeof(data2) + 1];
	} data3;
	int (*checkFun)(LSZ_MT*) = LSZ_LLL_checkFun;
	LSZ_LLLNode *node;

	//when a LSZ_LinearList being used, it should be initialize first
	//当一LSZ_LinearList要被使用时必须先初始化
	LSZ_LLL_init(&ctrl);
	LSZ_MT_init(&data);
	printf("init: size: %d\n", LSZ_LLL_size(&ctrl));

	LSZ_MT_wt(&data, &data0);
	LSZ_LLL_add(&ctrl, &data, 0);
	LSZ_MT_wt(&data, &data2);
	LSZ_LLL_add(&ctrl, &data, 1);
	LSZ_MT_wt(&data, &data1);
	LSZ_LLL_add(&ctrl, &data, 1);
	LSZ_LLL_add(&ctrl, &data, 1); //多插入一个元素
	printf("add: size: %d\n", LSZ_LLL_size(&ctrl));

	LSZ_LLL_del(&ctrl, &data, 1); //删除多余元素
	LSZ_MT_rd(data3.data2, &data);
	printf("del: size = %d, data1 = %d\n",
			LSZ_LLL_size(&ctrl), data3.data1);

	LSZ_LLL_rd(&ctrl, &data, 0);
	LSZ_MT_rd(&(data3.data0), &data);
	printf("rd: data0 = %c", data3.data0);
	LSZ_LLL_rd(&ctrl, &data, 1);
	LSZ_MT_rd(&(data3.data1), &data);
	printf(" data1 = %d", data3.data1);
	LSZ_LLL_rd(&ctrl, &data, 2);
	LSZ_MT_rd(data3.data2, &data);
	printf(" data2 = %s\n", data3.data2);

	data0 = 'b'; //先置不同值。
	LSZ_MT_wt(&data, &data0);
	LSZ_LLL_wt(&ctrl, &data, 0);
	data0 = 'c'; //先置不同值。
	LSZ_LLL_rd(&ctrl, &data, 0);
	LSZ_MT_rd(&data3.data0, &data);
	printf("wt: data0 = %c\n", data3.data0);

	data3.data1 = 0; //先置不同值。
	printf("trav: 1 = %d, num = %d\n",
			(LSZ_MT_rd(&(data3.data1), &data), data3.data1),
			LSZ_LLL_trav(&ctrl, 0, checkFun, &data));

	data3.data1 = 0; //先置不同值。
	node = LSZ_LLL_findNode(&ctrl, 1);
	LSZ_MT_rd(&(data3.data1), &(node->data));
	printf("findNode: data1 = %d\n", data3.data1);
	LSZ_MT_rd(&(data3.data0), &(LSZ_LLL_priorNode(&ctrl, node)->data));
	printf("priorNode: data1 = %c\n", data3.data0);
	LSZ_MT_rd(&(data3.data2), &(LSZ_LLL_nextNode(node)->data));
	printf("nextNode: data1 = %s\n", data3.data2);

	LSZ_LLLCtl ctrl2;
	LSZ_LLL_init(&ctrl2);
	data3.data0 = 'd';
	LSZ_MT_wt(&data, &(data3.data0));
	LSZ_LLL_add(&ctrl2, &data, 0);
	LSZ_LLL_append(&ctrl, &ctrl2);
	LSZ_LLL_rd(&ctrl, &data, 3);
	data3.data0 = 'e'; //先置不同值
	LSZ_MT_rd(&(data3.data0), &data);
	printf("append: 3 = %c, size: %d\n", data3.data0, LSZ_LLL_size(&ctrl));

	data3.data0 = 'f';
	LSZ_MT_wt(&data, &(data3.data0));
	LSZ_LLL_add(&ctrl2, &data, 0);
	LSZ_LLL_swapNode(&ctrl, LSZ_LLL_findNode(&ctrl, 1),
		&ctrl2, LSZ_LLL_findNode(&ctrl2, 0));
	data3.data0 = 'g'; //先置不同值
	LSZ_LLL_rd(&ctrl, &data, 1);
	LSZ_MT_rd(&(data3.data0), &data);
	printf("swap,ctrl: 1 = %c, size: %d\n",
			data3.data0, LSZ_LLL_size(&ctrl));

	LSZ_LLL_swapNode(&ctrl, LSZ_LLL_findNode(&ctrl, 0),
		&ctrl, LSZ_LLL_findNode(&ctrl, 1));
	printf("swap,ctrl: 0 = %c, 1 = %c size: %d\n",
		(LSZ_LLL_rd(&ctrl, &data, 0), LSZ_MT_rd(&(data3.data0), &data),
		 data3.data0),
		(LSZ_LLL_rd(&ctrl, &data, 1), LSZ_MT_rd(&(data3.data0), &data),
		 data3.data0),
		LSZ_LLL_size(&ctrl));

	LSZ_LLL_dest(&ctrl2);
	LSZ_LLL_dest(&ctrl);
	printf("dest,size: %d\n", LSZ_LLL_size(&ctrl));

	return 0;
}

int LSZ_LLL_checkFun(LSZ_MT *data)
{
	LSZ_MT temp;
	int data1 = 1;

	LSZ_MT_init(&temp);
	LSZ_MT_wt(&temp, &data1);
	if(LSZ_MT_eq(data, &temp))
		return 1;
	return 0;
}

