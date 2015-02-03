/********************************************************************
 *File Name: LSZ_DataType.c
 *Author: Linshangze//林上泽
 *Mail: linshangze163@163.com
 *Created Time: 2013-08-28 
 *Updated Time: 2015-01-10
 *******************************************************************/

/********************************************************************
 *source file of LSZ_DataType
 *LSZ_ElementType源文件
 *******************************************************************/

#ifndef _LSZ_DATATYPE_C_
#define _LSZ_DATATYPE_C_

#ifndef _LSZ_CHECK_ERROR_
#define _LSZ_CHECK_ERROR_
#endif

#include <malloc.h>
#include "LSZ_ErrorType.h"
#include "LSZ_DataType.h"

/**
 * to initialize a LSZ_MT.
 * 初始化一LSZ_MT类型。
 */
int LSZ_MT_init(LSZ_MT* e)
{
#ifdef _LSZ_CHECK_ERROR_
	if(e == NULL)
		return _LSZ_ERRISNULLPOINTER_;
#endif
	e->data = NULL;
	return e->len = 0;
}

/**
 * to destroy a LSZ_MT.
 * 销毁一LSZ_MT类型。
 */
int LSZ_MT_dest(LSZ_MT* e)
{
#ifdef _LSZ_CHECK_ERROR_
	if(e == NULL)
		return _LSZ_ERRISNULLPOINTER_;
#endif
	if(e->data != NULL){
		free(e->data);
		e->data = NULL;
	}
	return e->len = 0;
}

/**
 * read the value of LSZ_MT.
 * 读取一LSZ_MT类型的值。
 */
int LSZ_MT_rd(LSZ_AT* dst,
				LSZ_MT* src)
{
	LSZ_LT count;
#ifdef _LSZ_CHECK_ERROR_
	if(dst == NULL || src == NULL)
		return _LSZ_ERRISNULLPOINTER_;
	if(src->data != NULL && src->len == 0)
		return _LSZ_ERRISNULLPOINTER_;
	if(src->data == NULL && src->len != 0)
		return _LSZ_ERRISNULLPOINTER_;
#endif
	if(src->len == 0){
		LSZ_AT_init(*dst);
	}else{
		count = src->len;
		while(count > 0){
			count--;
			LSZ_AT_wt(dst[count], src->data[count]);
		}	
	}
	return src->len;
}

/**
 * modify the value of LSZ_MT.
 * 修改一LSZ_MT类型的值。
 */
int LSZ_MT_wt_(LSZ_MT* dst,
				LSZ_AT* src,
				LSZ_LT len)
{
	LSZ_AT* temp;
	LSZ_LT count;
#ifdef _LSZ_CHECK_ERROR_
	if(dst == NULL || src == NULL)
		return _LSZ_ERRISNULLPOINTER_;
	if((dst->data != NULL && dst->len == 0) ||
		(dst->data == NULL && dst->len != 0))
		return _LSZ_ERRISNULLPOINTER_;
#endif
	if(len == 0 && dst->data != NULL){
		free(dst->data);
	}else{
		if(len != dst->len){
			if((temp = (LSZ_AT*)realloc(
				dst->data, len * sizeof(LSZ_AT))) == NULL)
				return _LSZ_ERRISFAILALLOCATE_;
			dst->data = temp;
		}
		count = len;
		while(count > 0){
			count--;
			LSZ_AT_wt(dst->data[count], src[count]);
		}	
	}
	return dst->len = len;
}

/**
 * 赋值一LSZ_MT类型。
 */
int LSZ_MT_sign(LSZ_MT* dst,
				LSZ_MT* src)
{
	LSZ_AT *temp;
	LSZ_LT count;
#ifdef _LSZ_CHECK_ERROR_
	if(dst == NULL || src == NULL)
		return _LSZ_ERRISNULLPOINTER_;
	if((dst->data != NULL && dst->len == 0) ||
		(dst->data == NULL && dst->len != 0))
		return _LSZ_ERRISNULLPOINTER_;
	if((src->data != NULL && src->len == 0) ||
		(src->data == NULL && src->len != 0))
		return _LSZ_ERRISNULLPOINTER_;
#endif
	if(src->len == 0 && dst->data != NULL){
		free(dst->data);
	}else{
		if(src->len != dst->len){
			if((temp = (LSZ_AT*)realloc(
				dst->data, src->len * sizeof(LSZ_AT))) == NULL)
				return _LSZ_ERRISFAILALLOCATE_;
			dst->data = temp;
		}
		count = src->len;
		while(count > 0){
			count--;
			LSZ_AT_wt(dst->data[count], src->data[count]);
		}	
	}
	return dst->len = src->len;
}

/**
 * to compare two LSZ_MT according CmpFun,
 * CmpFun will decide the value returned.
 * 0 will be return if they are equal.
 * 比较两个LSZ_MT类型，通过CmpFun函数判断得到返回值。
 * 相同返回0，否则返回非零。
 */
int LSZ_MT_eq(LSZ_MT* e1,
				LSZ_MT* e2)
{
	int count = 0;
#ifdef _LSZ_CHECK_ERROR_
	if(e1 == NULL || e2 == NULL)
		return _LSZ_ERRISNULLPOINTER_;
	if((e1->data == NULL && e1->len != 0) ||
		(e1->data != NULL && e1->len == 0))
		return _LSZ_ERRISNULLPOINTER_;
	if((e2->data == NULL && e2->len != 0) ||
		(e2->data != NULL && e2->len == 0))
		return _LSZ_ERRISNULLPOINTER_;
#endif
	while(e1->len > count && e2->len > count){
		if(!LSZ_AT_eq(e1->data[count], e2->data[count]))
			return 0;
		count++;
	}
	if(count < e1->len || count < e2->len)
		return 0;
	return 1;
}


/**
 * to fill the data saved in 'e' with zero each bit.
 * return the length of data in byte if successfully.
 * 将e存储的数据按位置零。
 * 成功返回数据的以字节算的长度。
 */
int LSZ_MT_wt0(LSZ_MT* e)
{
	int count;

#ifdef _LSZ_CHECK_ERROR_
	if(e == NULL)
		return _LSZ_ERRISNULLPOINTER_;
#endif
	if(e->data == NULL && e->len != 0)
		return e->len = 0;
	if(e->data != NULL && e->len == 0){
		e->data = NULL;
		return e->len;
	}
	count = e->len;
	while(count > 0){
		count--;
		LSZ_AT_wt(e->data[count], 0);
	}	
	return e->len;
}

/**
 * to swap two data saved in 'e1' and 'e2'.
 * return the length of data swapped in byte if successfully.
 * 交换e1和e2中存储的数据。。
 * 成功返回交换的数据的以字节算的长度。
 */
int LSZ_MT_swap(LSZ_MT* e1,
				LSZ_MT* e2)
{
	LSZ_AT *temp;
	int length;

#ifdef _LSZ_CHECK_ERROR_
	if(e1 == NULL || e2 == NULL)
		return _LSZ_ERRISNULLPOINTER_;
	if((e1->data == NULL && e1->len != 0) ||
		(e1->data != NULL && e1->len == 0))
		return _LSZ_ERRISNULLPOINTER_;
	if((e2->data == NULL && e2->len != 0) ||
		(e2->data != NULL && e2->len == 0))
		return _LSZ_ERRISNULLPOINTER_;
#endif
	temp = e2->data;
	e2->data = e1->data;
	e1->data = temp;
	length = e2->len;
	e2->len = e1->len;
	e1->len = length;
	return e1->len > e2->len ? e1->len : e2->len;
}

//the end of file
#endif
