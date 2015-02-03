/********************************************************************
 *File Name: LSZ_String.c
 *Author: Linshangze//林上泽
 *Mail: linshangze163@163.com
 *Created Time: 2013-05-22
 *Updated Time: 2015-05-20
 *******************************************************************/

/********************************************************************
 *source file of LSZ_String data structure
 *LSZ_String源文件
 *******************************************************************/

#ifndef _LSZ_STRING_C_
#define _LSZ_STRING_C_

#ifndef _LSZ_CHECK_ERROR_
#define _LSZ_CHECK_ERROR_
#endif

#include <malloc.h>
#include "LSZ_String.h"

//字符串结尾标记设定
#define _LSZ_FUN_STR_END(str) ((str) == '\0')

/**
 * to copy string b to string a
 * according the length parameter
 * 根据参数length将a串复制到b串
 */
LSZ_AT *LSZ_Str_copy(LSZ_AT *dstStr,
						LSZ_AT *srcStr)
{
	int i;

#ifdef _LSZ_CHECK_ERROR_
	if(dstStr == NULL || srcStr == NULL)
		return dstStr; //_LSZ_ERRISNULLPOINTER_;
#endif
	for(i = 0; !_LSZ_FUN_STR_END(srcStr[i]); i++)
		LSZ_AT_sign(dstStr[i], srcStr[i]);
	LSZ_AT_sign(dstStr[i], srcStr[i]);
	return dstStr;
}

/**
 * to connect string b to the tail of string a
 * according the length parameter
 * 根据参数length将b串连接到a串的尾部
 */
LSZ_AT *LSZ_Str_cat(LSZ_AT *dstStr,
					LSZ_AT *srcStr)
{
	int i, j;

#ifdef _LSZ_CHECK_ERROR_
	if(dstStr == NULL || srcStr == NULL)
		return dstStr; //_LSZ_ERRISNULLPOINTER_;
#endif
	for(i = 0; !_LSZ_FUN_STR_END(dstStr[i]); i++)
		;
	for(j = 0; !_LSZ_FUN_STR_END(srcStr[j]); i++, j++)
		LSZ_AT_sign(dstStr[i], srcStr[j]);
	LSZ_AT_sign(dstStr[i], srcStr[j]);
	return dstStr;
}

/**
 * to find the substring b int the string a
 * 在串a中找子串b，返回在a串的起始位置。
 */
LSZ_AT *LSZ_Str_sub(LSZ_AT *dstStr,
					LSZ_AT *subStr)
{
	int i, j;

#ifdef _LSZ_CHECK_ERROR_
	if(dstStr == NULL || subStr == NULL)
		return dstStr; //_LSZ_ERRISNULLPOINTER_;
#endif
	for(i = 0; !_LSZ_FUN_STR_END(dstStr[i]); i++){
		for(j = 0;!_LSZ_FUN_STR_END(dstStr[i + j]) &&
			!_LSZ_FUN_STR_END(subStr[j]) &&
		   	LSZ_AT_eq(dstStr[i + j], subStr[j]); j++)
			;
		if(_LSZ_FUN_STR_END(subStr[j]))
			return dstStr + i;
	}
	return NULL;
}

/**
 * to find the substring b int the string a with KMP algorithm
 * 用KMP算法在串a中找子串b
 */
LSZ_AT *LSZ_Str_subKMP(LSZ_AT *dstStr,
						LSZ_AT *subStr)
{
	int *next, i, j;
	LSZ_AT *dstP = dstStr, *subP = subStr;

#ifdef _LSZ_CHECK_ERROR_
	if(dstP == NULL || subP == NULL)
		return NULL;
#endif
	if((next = LSZ_Str_nextKMP(subStr)) == NULL)
		return NULL;
	i = j = 0;
	while(!_LSZ_FUN_STR_END(dstStr[i]) &&
			(j == -1 || !_LSZ_FUN_STR_END(subStr[j]))){
		//none of the mode match with the main string
		//or one is match with the main string 
		//零匹配于主串
		//或者获得一匹配增量
		if(j == -1 || LSZ_AT_eq(dstP[i], subP[j])){
			i++;
			j++;
		}else//dismatch//非零匹配的失配
			j = next[j];
	}
	free(next);
	if(j >=0 && _LSZ_FUN_STR_END(subStr[j]))//find the substring
		return dstP + i - j;
	return NULL;
}

/**
 * to set the next of string using int KMP algorithm
 * 为KMP算法设置串的next位
 */
int* LSZ_Str_nextKMP(LSZ_AT *str)
{
	LSZ_AT *cP = str;
	int *next, i, j;

#ifdef _LSZ_CHECK_ERROR_
	if(str == NULL)
		return NULL;//_LSZ_ERRISNULLPOINTER_
#endif
	for(i = 0; !_LSZ_FUN_STR_END(cP[i]); i++)
		;
	if(i == 0)
		return NULL; //空串
	if((next = (int*)malloc(sizeof(int) * i)) == NULL)
		return NULL;//_LSZ_ERRISFAILALLOCATE_
	//if the first of the mode is not match with the main string
	//the mode should be compared by the next of the main string
	//如果模式串的第一个和主串不匹配
	//那么模式串和主串的下一个比较
	i = 0, j = -1;
	next[i] = j;//none matching with the main string//零匹配
	//every back tack index is according to the previous one
	//每一个回溯下标的设置是由前一个决定的
	while(!_LSZ_FUN_STR_END(str[i + 1])){
		//none of the mode match with the main string
		//or one is match with the main string 
		//零匹配于主串
		//或者获得一匹配增量
		if(j == -1 || LSZ_AT_eq(cP[i], cP[j])){
			i++, j++;
			//this is promote the mode as 'aaa...bcd...'
			//这里的分支主要是改进形如'aaa...bcd...'的模式串
			if(LSZ_AT_eq(cP[i], cP[j]))
				next[i] = next[j];
			else
				next[i] = j;//when not matching, set where to go back
		}else //当前不匹配，设置回溯点
			j = next[j];
	}
	return next;
}

//the end of file
#endif
