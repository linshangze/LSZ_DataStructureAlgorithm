/********************************************************************
 *author: Linshangze//林上泽
 *Mail: linshangze163@163.com
 *date: 2012-08-14
 *file name: testLSZ_LinearListLQueue.c
 *******************************************************************/

/********************************************************************
 *test file for LSZ_LinearListLQueue data structure
 *LSZ_LinearListLQueue测试源文件
 *******************************************************************/

#include <stdio.h>
#include "LSZ_Queue.h"

int main()
{
	LSZ_QueueCtl queue;
	LSZ_MT data;
	char temp;
	int i;

	LSZ_MT_init(&data);
	LSZ_Queue_init(&queue);
	printf("init, size: %d\n", LSZ_Queue_size(&queue));

	for(i = 0; i < 5; i++){
		temp = 'a' + i;
		LSZ_MT_wt(&data, &temp);
		if(LSZ_Queue_enqueue(&queue, &data) != 0){
			printf("enqueue: %d, what happened??\n", i);
			return 0;
		}else
			printf("enqueue: %c\n", temp);
	}
	printf("enqueue ok\n\n");

	for(i = 0; i < 6; i++){
		if(LSZ_Queue_head(&queue, &data) == 0){
			LSZ_MT_rd(&temp, &data);
			printf("getHead: %c\n", temp);
		}else{
			if(i < 5){
				printf("getHead %d: what happened??\n", i);
				return 0;
			}else
				printf("getHead: ok\n");
		}
		if(LSZ_Queue_tail(&queue, &data) == 0){
			LSZ_MT_rd(&temp, &data);
			printf("getTail: %c\n", temp);
		}else{
			if(i < 5){
				printf("getTail %d: what happened??\n", i);
				return 0;
			}else
				printf("getTail: ok\n");
		}
		if(LSZ_Queue_dequeue(&queue, &data) == 0){
			LSZ_MT_rd(&temp, &data);
			printf("dequeue: %c\n", temp);
		}else{
			if(i < 5){
				printf("dequeue %d: what happened??\n", i);
				return 0;
			}else
				printf("dequeue: ok\n");
		}
	}

	LSZ_Queue_dest(&queue);
	printf("dest, size: %d\n", LSZ_Queue_size(&queue));

	return 0;
}

