/********************************************************************
 *author: Linshangze//林上泽
 *Mail: linshangze163@163.com
 *date: 2013-05-21
 *file name: LSZ_Queue.h
 *******************************************************************/

/********************************************************************
 *header file of LSZ_Queue data structure
 *LSZ_Queue头文件
 *******************************************************************/

#ifndef _LSZ_QUEUE_H_
#define _LSZ_QUEUE_H_

#include "../LSZ_DataType/LSZ_DataType.h"
#include "../LSZ_DataType/LSZ_ErrorType.h"

/////////////////////////////////////////////////////////////////////
//macro
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
//definition of type
//数据类型定义
/////////////////////////////////////////////////////////////////////

/**
 * the node of linear linked list queue
 * 邻接链表队列的结点结构
 */
typedef struct LSZ_QueueNode
{
	LSZ_MT data;//the data in a node
	struct LSZ_QueueNode *next;//the next node
}LSZ_QueueNode;

/**
 * the structure controlling the LSZ_LinearListLQueue
 * 控制LSZ_LinearListLQueue的结构
 */
typedef struct LSZ_QueueCtl
{
	LSZ_QueueNode *head;//the head of queue(队列的头)
	struct LSZ_QueueNode *tail;//the tail of queue(队列的尾)
	int count; //队列中元素的个数
}LSZ_QueueCtl;

/////////////////////////////////////////////////////////////////////
//declaration of functions
//函数声明
/////////////////////////////////////////////////////////////////////

/**
 * to initialize a link queue list
 * 初始化一队列结构
 */
extern int LSZ_Queue_init(LSZ_QueueCtl *control);

/**
 * to clear a queue
 * and the data in it will be released
 * 清空一队列而其中的数据会被销毁
 */
extern int LSZ_Queue_dest(LSZ_QueueCtl *control);

/**
 * to count a stack
 * 计算一队列的大小
 */
extern int LSZ_Queue_size(LSZ_QueueCtl *control);

/**
 * enqueue, a new data enters the tail of a queue
 * 一新元素进入队尾
 */
extern int LSZ_Queue_enqueue(LSZ_QueueCtl *control,
						LSZ_MT *data);

/**
 * dequeue, an data departs from the head of queue
 * and the data will be return by data parameter
 * 一元素离开队头并用参数data返回其值
 */
extern int LSZ_Queue_dequeue(LSZ_QueueCtl *control,
						LSZ_MT *data);

/**
 * to get the tail data of a queue by data parameter
 * 用参数data获取队列尾元素的值
 */
extern int LSZ_Queue_tail(LSZ_QueueCtl *control,
					LSZ_MT *data);

/**
 * to get the head data of a queue by data parameter
 * 用参数data获取队列头元素的值
 */
extern int LSZ_Queue_head(LSZ_QueueCtl *control,
					LSZ_MT *data);

//the end of file
#endif
