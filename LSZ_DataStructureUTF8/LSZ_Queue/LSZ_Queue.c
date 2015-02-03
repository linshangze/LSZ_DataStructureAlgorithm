/********************************************************************
 *author: Linshangze//林上泽
 *date: 2013-05-21
 *Mail: linshangze163@163.com
 *file name: LSZ_Queue.c
 *******************************************************************/

/********************************************************************
 *source file of LSZ_LinearListLQueue data structure
 *LSZ_LinearListLQueue源文件
 *******************************************************************/

#ifndef _LSZ_QUEUE_C_
#define _LSZ_QUEUE_C_

#ifndef _LSZ_CHECK_ERROR_
#define _LSZ_CHECK_ERROR_
#endif

#include <malloc.h>
#include "LSZ_Queue.h"

#define _LSZ_FUN_QUEUE_NODE(node) \
	((node = (LSZ_QueueNode*)malloc(sizeof(LSZ_QueueNode))) != NULL)

/**
 * to initialize a link queue list
 * 初始化一队列结构
 */
int LSZ_Queue_init(LSZ_QueueCtl *control)
{
#ifdef _LSZ_CHECK_ERROR_
	if(control == NULL)
		return _LSZ_ERRISNULLPOINTER_;
#endif
	control->head = control->tail = NULL;
	control->count = 0;
	return 0;
}

/**
 * to clear a queue
 * and the data in it will be released
 * 清空一队列而其中的数据会被销毁
 */
int LSZ_Queue_dest(LSZ_QueueCtl *control)
{
	LSZ_QueueNode *oldNode;

#ifdef _LSZ_CHECK_ERROR_
	if(control == NULL)
		return _LSZ_ERRISNULLPOINTER_;
#endif
	while((oldNode = control->head) != NULL){
		control->head = oldNode->next;
		LSZ_MT_dest(&(oldNode->data));
		free(oldNode);
	}
	control->tail = NULL;	//empty queue(空队)
	control->count = 0;
	return 0;
}

/**
 * to count a stack
 * 计算一队列的大小
 */
int LSZ_Queue_size(LSZ_QueueCtl *control)
{
#ifdef _LSZ_CHECK_ERROR_
	if(control == NULL)
		return _LSZ_ERRISNULLPOINTER_;
#endif
	return control->count;
}

/**
 * enqueue, a new data enters the tail of a queue
 * 一新元素进入队尾
 */
int LSZ_Queue_enqueue(LSZ_QueueCtl *control,
						LSZ_MT *data)
{
	LSZ_QueueNode *newNode;

#ifdef _LSZ_CHECK_ERROR_
	if(control == NULL)
		return _LSZ_ERRISNULLPOINTER_;
#endif
	if(!_LSZ_FUN_QUEUE_NODE(newNode))
		return _LSZ_ERRISFAILALLOCATE_;
	LSZ_MT_init(&(newNode->data));
	LSZ_MT_sign(&(newNode->data), data);
	newNode->next = NULL;
	if(control->head == NULL)//queue empty(空队列)
		control->head = control->tail = newNode;
	else{
		control->tail->next = newNode;
		control->tail = newNode;
	}
	control->count += 1;
	return 0;
}

/**
 * dequeue, an data departs from the head of queue
 * and the data will be return by data parameter
 * 一元素离开队头并用参数data返回其值
 */
int LSZ_Queue_dequeue(LSZ_QueueCtl *control,
						LSZ_MT *data)
{
	LSZ_QueueNode *oldNode;

#ifdef _LSZ_CHECK_ERROR_
	if(control == NULL)
		return _LSZ_ERRISNULLPOINTER_;
	if((oldNode = control->head) == NULL)
		return _LSZ_ERRISOUTOFBORDER_;//empty queue(空队)
#endif
	if((control->head = oldNode->next) == NULL)
		control->tail = NULL;//will be empty queue(空队)
	if(data != NULL)
		LSZ_MT_sign(data, &(oldNode->data));
	free(oldNode);
	control->count -= 1;
	return 0;
}

/**
 * to get the tail data of a queue by data parameter
 * 用参数data获取队列尾元素的值
 */
int LSZ_Queue_tail(LSZ_QueueCtl *control,
					LSZ_MT *data)
{
#ifdef _LSZ_CHECK_ERROR_
	if(control == NULL || data == NULL)
		return _LSZ_ERRISNULLPOINTER_;
	if(control->tail == NULL)
		return _LSZ_ERRISOUTOFBORDER_;//empty queue(空队列)
#endif
	LSZ_MT_sign(data, &(control->tail->data));
	return 0;
}

/**
 * to get the head data of a queue by data parameter
 * 用参数data获取队列头元素的值
 */
int LSZ_Queue_head(LSZ_QueueCtl *control,
					LSZ_MT *data)
{
#ifdef _LSZ_CHECK_ERROR_
	if(control == NULL || data == NULL)
		return _LSZ_ERRISNULLPOINTER_;
	if(control->head == NULL)
		return _LSZ_ERRISOUTOFBORDER_;//empty queue(空队列)
#endif
	LSZ_MT_sign(data, &(control->head->data));
	return 0;
}

//the end of file
#endif

