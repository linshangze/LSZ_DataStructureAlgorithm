/********************************************************************
 *File Name: LSZ_Stack.h
 *Author: Linshangze//林上泽
 *Mail: linshangze163@163.com
 *Created Time: 2013-05-21
 *Updated Time: 2015-01-20
 *******************************************************************/

/********************************************************************
 *header file of LSZ_Stack data structure
 *LSZ_Stack头文件
 *******************************************************************/

#ifndef _LSZ_STACK_H_
#define _LSZ_STACK_H_

#include "../LSZ_DataType/LSZ_DataType.h"
#include "../LSZ_DataType/LSZ_ErrorType.h"

/********************************************************************
	the stack linked list dosen't has head node,it is because
	consider that the stack maybe be nested in some user-defined
	struct which will cause memory leak if stack has head node.
	实现栈的链表没有采用头结点,
	是为了避免当该栈结构被内嵌成其它结构体成员是可能会造成内存泄漏。
 *******************************************************************/

/////////////////////////////////////////////////////////////////////
//macro
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
//definition of type
//数据类型定义
/////////////////////////////////////////////////////////////////////

/**
 * the node of linear linked list stack
 * 邻接链表栈的结点结构
 */
typedef struct LSZ_StackNode
{
	LSZ_MT data; //the the data saved in node
	struct LSZ_StackNode *next;//the next node
}LSZ_StackNode;

/**
 * the structure controlling the LSZ_Stack
 * 控制LSZ_Stack的结构
 */
typedef struct LSZ_StackCtl
{
	LSZ_StackNode *top; //the top of stack(栈顶)
	int count; //栈中元素的个数
}LSZ_StackCtl;

/////////////////////////////////////////////////////////////////////
//declaration of functions
//函数声明
/////////////////////////////////////////////////////////////////////

/**
 * to initailize a link stack list
 * 初始化一个栈结构
 */
#define LSZ_Stack_init(newStack) \
	((newStack)->top = NULL, (newStack)->count = 0)

/**
 * to clear a stack
 * and destroy its data
 * 清空一栈的元素并销毁其数据
 */
extern int LSZ_Stack_dest(LSZ_StackCtl *control);

/**
 * to count a stack
 * 计算一栈的大小
 */
extern int LSZ_Stack_size(LSZ_StackCtl *control);

/////////////////////////////////////////////////////////////////////
//LSZ_Stack的习惯操作。
/////////////////////////////////////////////////////////////////////

/**
 * to get the top data of the stack by data parameter
 * 用参数data获取栈顶元素的值
 */
extern int LSZ_Stack_top(LSZ_StackCtl *control,
					LSZ_MT *data);
/**
 * to push a new data into a stack
 * 一新元素的进栈
 */
extern int LSZ_Stack_push(LSZ_StackCtl *control,
					LSZ_MT *data);
/**
 * to pop the top data of stack
 * and return it by data parameter
 * 栈顶元素出栈并用参数data将其返回
 */
extern int LSZ_Stack_pop(LSZ_StackCtl *control,
					LSZ_MT *data);

//the end of file
#endif
