/********************************************************************
 *File Name: LSZ_LinearListSqS.c
 *Author: Linshangze//林上泽
 *Mail: linshangze163@163.com
 *Created Time: 2013-05-09
 *Updated Time: 2015-01-13
 *******************************************************************/

#ifndef _LSZ_LINEARLISTSQ_C_
#define _LSZ_LINEARLISTSQ_C_

#ifndef _LSZ_CHECK_ERROR_ 
#define _LSZ_CHECK_ERROR_ 
#endif

#include <stdio.h>
#include "LSZ_LinearListSq.h"

/********************************************************************
 *source file of LSZ_LinearListSq data structure
 *LSZ_LinearListL源文件
 *******************************************************************/

/**
 * to insert a new data into a LSZ_LniearListSq
 * according to the sequence number
 * 在一LSZ_LinearListSq根据序列号插入数据
 */
int LSZ_LLSq_add_(LSZ_AT *sq,
					int length,
					LSZ_AT *data,
					int size,
					int number)
{
	int i, j;

#ifdef _LSZ_CHECK_ERROR_
	if(sq == NULL || data == NULL)
		return _LSZ_ERRISNULLPOINTER_;
	if(number < 0 || number > length || size <= 0)
		return _LSZ_LINEARLISTSQFAIL_;
#endif
	number *= size;
	//firstly move the elements to make room for new elements
	//先为新元素腾出空间
	for(i = length * size; i > number; i--){
		LSZ_AT_sign(sq[i], sq[i - size]);
	}
	//save the new element
	//存放新元素
	for(j = 0; j < size; j++){
		LSZ_AT_sign(sq[i + j], data[j]);
	}
	return number;
}

/**
 * to delete a data in a LSZ_LniearListSq
 * according to the sequence number.
 * 在一LSZ_LinearListSq根据序列号删除数据
 */
int LSZ_LLSq_del_(LSZ_AT *sq,
					int length,
					LSZ_AT *data,
					int size,
					int number)
{
	int i;

#ifdef _LSZ_CHECK_ERROR_
	if(sq == NULL || data == NULL)
		return _LSZ_ERRISNULLPOINTER_;
	if(number < 0 || number > length || size <= 0)
		return _LSZ_LINEARLISTSQFAIL_;
#endif
	number *= size;
	length *= size;
	//move the elements after the element deleted
	//移动被删除元素的后继元素
	for(i = number; i < length; i++){
		LSZ_AT_sign(sq[i], sq[i + size]);
	}
	return number;
}

/**
 * to copy LSZ_LniearListSq b to the end of LSZ_LniearListSq a
 * 将LSZ_LinearListSq b拷贝到LSZ_LniearListSq a的尾部
 */
int LSZ_LLSq_append_(LSZ_AT *aSq,
					int aLength,
					int size,
					LSZ_AT *bSq,
					int bLength)
{
	int i;

#ifdef _LSZ_CHECK_ERROR_
	if(aSq == NULL || bSq == NULL)
		return _LSZ_ERRISNULLPOINTER_;
	if(aLength <= 0 || bLength <= 0 || size <= 0)
		return _LSZ_LINEARLISTSQFAIL_;
#endif
	aLength *= size;
	bLength *= size;
	for(i = 0; i < bLength; i++){
		LSZ_AT_sign(aSq[i + aLength], bSq[i]);
	}
	return aLength + bLength;
}

/**
 * 将一LSZ_LinearListSq倒置。
 */
int LSZ_LLSq_reverse_(LSZ_AT *sq,
						int len,
						int size)
{
	int i, j, mid;

#ifdef _LSZ_CHECK_ERROR_
	if(sq == NULL)
		return _LSZ_ERRISNULLPOINTER_;
	if(len <= 0 || size <= 0)
		return _LSZ_LINEARLISTSQFAIL_;
#endif
	len = len * size;
	mid = len / 2;
	len = len - size;
	for(i = 0; i < mid; i += size){
		for(j = 0; j < size; j++){
			LSZ_AT_swap(sq[i + j], sq[len - i + j]);
		}
	}
	return len / size + 1;
}

//the end of file
#endif

