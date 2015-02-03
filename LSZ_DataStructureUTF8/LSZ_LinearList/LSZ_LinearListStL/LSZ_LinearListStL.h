/********************************************************************
 *File Name: LSZ_LinearListStL.h
 *Author: Linshangze//林上泽
 *Mail: linshangze163@163.com
 *Created Time: 2013-05-15
 *Updated Time: 2015-01-14
 *******************************************************************/

/********************************************************************
 *header file of LSZ_LinearListStL
 *LSZ_LinearListStL头文件
 *该文件虽然是.h文件，实质是.c文件，在include此文件前，
 *应先定义好LSZ_LLStLData类型，再用LSZ_LLStLNode数组定义好分配空间。
 *简单实现了静态分配数组堆。因为LSZ_LLStLData不能被重新定义，
 *所以只能建立多个数据类型相同的静态分配数组堆。只提供操作，已分配
 *出去的静态空间需要用户自己管理好。
 *******************************************************************/

#ifndef _LSZ_LINEARLISTSTL_H_
#define _LSZ_LINEARLISTSTL_H_

#ifndef _LSZ_CHECK_ERROR_
#define _LSZ_CHECK_ERROR_
#endif

#include "../../LSZ_DataType/LSZ_ErrorType.h"

/////////////////////////////////////////////////////////////////////
//macro
/////////////////////////////////////////////////////////////////////

/**
 * LSZ_LLStLData Type that is the data field
 * should have been defined before this file is included
 * 在include此文件前先定义数据类型。
 */
//typedef selfType LSZ_LLStLData;

/////////////////////////////////////////////////////////////////////
//definition of type
//数据类型定义
/////////////////////////////////////////////////////////////////////

/**
 * 静态空间结点类型。
 */
typedef struct LSZ_LLStLNode{
	LSZ_LLStLData data; //data fiel//数据域
	int cursor; //the cursor point to the next Node//指向下个结点
	int flag; //是否空闲结点的标志。
}LSZ_LLStLNode;

//the space need to be initialized first
//指向当前操作的自定义堆空间
static LSZ_LLStLNode *LSZ_LLStLSpace = NULL;
//当前操作的堆空间的长度。
static int LSZ_LLStLLength = 0;

/////////////////////////////////////////////////////////////////////
//declaration of functions
//函数声明
/////////////////////////////////////////////////////////////////////

/**
 * to initialize a LSZ_LinearListStL's space
 * 初始化一LSZ_LinearListStL的空间
 */
int LSZ_LLStL_init(LSZ_LLStLNode *space,
					int length)
{
	int i;

#ifdef _LSZ_CHECK_ERROR_
	if(space == NULL)
		return _LSZ_ERRISNULLPOINTER_;
#endif
	for(i = 0; i < length; i++){ //unused space//未用空间
		space[i].cursor = i + 1;
		space[i].flag = 0; //空闲标志。
	}
	space[i - 1].cursor = 0;//the end//游标0代表链结束
	space[i - 1].flag = 0;
	LSZ_LLStLSpace = space;
	LSZ_LLStLLength = length;
	return 0;
}

/**
 * to allocate a unused component and return its index
 * 分配没被使用的结点并返回其下标
 */
int LSZ_LLStL_malloc()//LSZ_LLStLNode *space
{
	int i;

#ifdef _LSZ_CHECK_ERROR_
	if(LSZ_LLStLSpace == NULL)
		return _LSZ_ERRISNULLPOINTER_;
	//none available component//没有可用结点
	if(LSZ_LLStLSpace[0].cursor == 0)
		return _LSZ_ERRISOUTOFBORDER_;
#endif
	i = LSZ_LLStLSpace[0].cursor;//get unused component取出未用结点
	LSZ_LLStLSpace[i].flag = 1;
	//the component is out
	LSZ_LLStLSpace[0].cursor = LSZ_LLStLSpace[i].cursor;
	return i;
}

/**
 * to free a used component by its cursor
 * 根据其下标释放一结点
 */
int LSZ_LLStL_free(int i)
{
#ifdef _LSZ_CHECK_ERROR_
	if(LSZ_LLStLSpace == NULL)
		return _LSZ_ERRISNULLPOINTER_;
	if(i <= 0 || i >= LSZ_LLStLLength)
		return _LSZ_ERRISOUTOFBORDER_;
	if(LSZ_LLStLSpace[i].flag != 1)
		return _LSZ_ERRISNULLPOINTER_;
#endif
	//insert into unused space(插入到未用空间)
	LSZ_LLStLSpace[i].flag = 0;
	LSZ_LLStLSpace[i].cursor = LSZ_LLStLSpace[0].cursor;
	LSZ_LLStLSpace[0].cursor = i;
	return i;
}

/**
 * to reset a LSZ_LinearListStL's space using a new space
 * that has been initialized.
 * 用一已初始化的空间设置一LSZ_LinearListStL的空间
 */
int LSZ_LLStL_reset(LSZ_LLStLNode *space, int len)
{
	LSZ_LLStLSpace = space;
	LSZ_LLStLLength = len;
	return 0;
}

//the end of file
#endif
