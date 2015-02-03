/********************************************************************
 *File Name: LSZ_Stack.c
 *Author: Linshangze//林上泽
 *Mail: linshangze163@163.com
 *Created Time: 2013-05-21
 *Updated Time: 2015-01-20
 *******************************************************************/

/********************************************************************
 *source file of LSZ_Stack data structure
 *LSZ_Stack源文件
 *******************************************************************/

#ifndef _LSZ_STACK_C_
#define _LSZ_STACK_C_

#ifndef _LSZ_CHECK_ERROR_
#define _LSZ_CHECK_ERROR_
#endif

#include <malloc.h>
#include "LSZ_Stack.h"

#define	_LSZ_FUN_Stack_NODE(newNode) \
   	((newNode = (LSZ_StackNode*)malloc(sizeof(LSZ_StackNode))) != NULL)

/**
 * to clear a stack
 * and destroy its data
 * 清空一栈的元素并销毁其数据
 */
int LSZ_Stack_dest(LSZ_StackCtl *control)
{
	LSZ_StackNode *oldNode;

#ifdef _LSZ_CHECK_ERROR_
	if(control == NULL)
		return _LSZ_ERRISNULLPOINTER_;
#endif
	while((oldNode = control->top) != NULL){
		control->top = oldNode->next;
		LSZ_MT_dest(&(oldNode->data));
		free(oldNode);
	}
	control->count = 0;
	return 0;
}

/**
 * to count a stack
 * 计算一栈的大小
 */
int LSZ_Stack_size(LSZ_StackCtl *control)
{
#ifdef _LSZ_CHECK_ERROR_
	if(control == NULL)
		return _LSZ_ERRISNULLPOINTER_;
#endif
	return control->count;
}

/////////////////////////////////////////////////////////////////////
//LSZ_Stack的习惯操作。
/////////////////////////////////////////////////////////////////////

/**
 * to get the top data of the stack by data parameter
 * 用参数data获取栈顶元素的值
 */
int LSZ_Stack_top(LSZ_StackCtl *control,
					LSZ_MT *data)
{
#ifdef _LSZ_CHECK_ERROR_
	if(control == NULL)
		return _LSZ_ERRISNULLPOINTER_;
	if(control->top == NULL)//stack empty(空栈)
		return _LSZ_ERRISOUTOFBORDER_;
#endif
	LSZ_MT_sign(data, &(control->top->data));
	return 0;
}

/**
 * to push a new data into a stack
 * 一新元素的进栈
 */
int LSZ_Stack_push(LSZ_StackCtl *control,
					LSZ_MT *data)
{		//(实质头插法)
	LSZ_StackNode *newNode;
#ifdef _LSZ_CHECK_ERROR_
	if(control == NULL)
		return _LSZ_ERRISNULLPOINTER_;
#endif
	if(!_LSZ_FUN_Stack_NODE(newNode))
		return _LSZ_ERRISFAILALLOCATE_;
	LSZ_MT_init(&(newNode->data));
	LSZ_MT_sign(&(newNode->data), data);
	newNode->next = control->top;
	control->top = newNode;
	control->count += 1;
	return 0;
}

/**
 * to pop the top data of stack
 * and return it by data parameter
 * 栈顶元素出栈并用参数data将其返回
 */
int LSZ_Stack_pop(LSZ_StackCtl *control,
					LSZ_MT *data)
{
	LSZ_StackNode *oldNode;

#ifdef _LSZ_CHECK_ERROR_
	if(control == NULL)
		return _LSZ_ERRISNULLPOINTER_;
	if((oldNode = control->top) == NULL) //empty stack
		return _LSZ_ERRISOUTOFBORDER_;
#endif
	control->top = oldNode->next;
	if(data != NULL)
		LSZ_MT_sign(data, &(oldNode->data));
	LSZ_MT_dest(&(oldNode->data));
	free(oldNode);
	control->count -= 1;
	return 0;
}

//the end of file
#endif
