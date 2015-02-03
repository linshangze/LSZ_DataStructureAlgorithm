/********************************************************************
 *File Name: LSZ_LinearListSq.h
 *Author: Linshangze//林上泽
 *Mail: linshangze163@163.com
 *Created Time: 2013-05-09
 *Updated Time: 2015-01-13
 *******************************************************************/

/********************************************************************
 *header file of LSZ_LinearListSq data structure
 *because the c programming language provides with
 *some operations of sequence linear list
 *I just to do some thing to extend the operations 
 *LSZ_LinearListSq头文件
 *因为c语言提供一些数组操作，所以这里只是扩展数据操作
 *******************************************************************/

#ifndef _LSZ_LINEARLISTSQ_H_
#define _LSZ_LINEARLISTSQ_H_

#include "../../LSZ_DataType/LSZ_ErrorType.h"
#include "../../LSZ_DataType/LSZ_DataType.h"

/////////////////////////////////////////////////////////////////////
//macro
/////////////////////////////////////////////////////////////////////
#define _LSZ_LINEARLISTSQFAIL_ -1

/////////////////////////////////////////////////////////////////////
//definition of type
//数据类型定义
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
//declaration of functions
//函数声明
/////////////////////////////////////////////////////////////////////

/**
 * to insert a new data into a LSZ_LniearListSq
 * according to the sequence number
 * 在一LSZ_LniearListSq根据序列号插入数据
 */
extern int LSZ_LLSq_add_(LSZ_AT *sq,
					int length,
					LSZ_AT *data,
					int size,
					int number);
#ifndef _LSZ_LINEARLISTSQ_C_
#define LSZ_LLSq_add(sq, len, data, num) \
	LSZ_LLSq_add_((LSZ_AT*)(sq), len, (LSZ_AT*)(data), \
	sizeof((sq)[0]), num)
#endif

/**
 * to delete a data in a LSZ_LniearListSq
 * according to the sequence number.
 * 在一LSZ_LinearListSq根据序列号删除数据
 */
extern int LSZ_LLSq_del_(LSZ_AT *sq,
					int length,
					LSZ_AT *data,
					int size,
					int number);
#ifndef _LSZ_LINEARLISTSQ_C_
#define LSZ_LLSq_del(sq, len, data, num) \
	LSZ_LLSq_del_((LSZ_AT*)(sq), len, (LSZ_AT*)(data), \
	sizeof((sq)[0]), num)
#endif

/**
 * to copy LSZ_LniearListSq b to the end of LSZ_LniearListSq a
 * 将LSZ_LinearListSq b拷贝到LSZ_LniearListSq a的尾部
 */
extern int LSZ_LLSq_append_(LSZ_AT *aSq,
					int aLength,
					int size,
					LSZ_AT *bSq,
					int bLength);
#ifndef _LSZ_LINEARLISTSQ_C_
#define LSZ_LLSq_append(aSq, aLen, bSq, bLen) \
	LSZ_LLSq_append_((LSZ_AT*)(aSq), aLen, sizeof((aSq)[0]), \
	(LSZ_AT*)(bSq), bLen)
#endif

/**
 * 将一LSZ_LinearListSq倒置。
 */
extern int LSZ_LLSq_reverse_(LSZ_AT *sq,
						int len,
						int size);
#ifndef _LSZ_LINEARLISTSQ_C_
#define LSZ_LLSq_reverse(sq, len) \
	LSZ_LLSq_reverse_((LSZ_AT*)(sq), len, sizeof((sq)[0]))
#endif

//the end of file
#endif
