/********************************************************************
 *File Name: LSZ_String.h
 *Author: Linshangze//林上泽
 *Mail: linshangze163@163.com
 *Created Time: 2013-05-22
 *Updated Time: 2015-05-20
 *******************************************************************/

/********************************************************************
 *header file of LSZ_String data structure
 *LSZ_String头文件
 *******************************************************************/

#ifndef _LSZ_STRING_H_
#define _LSZ_STRING_H_

#include "../LSZ_DataType/LSZ_DataType.h"
#include "../LSZ_DataType/LSZ_ErrorType.h"

/////////////////////////////////////////////////////////////////////
//macro
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
//definition of type
//数据类型定义
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
//declaration of functions
//函数声明
/////////////////////////////////////////////////////////////////////

/**
 * to copy string b to string a
 * according the length parameter
 * 根据参数length将a串复制到b串
 */
extern LSZ_AT *LSZ_Str_copy(LSZ_AT *dstStr,
						LSZ_AT *srcStr);
#ifndef _LSZ_STRING_C_
#define LSZ_Str_copy(dstStr, srcStr) \
	(char*)LSZ_Str_copy((LSZ_AT*)(dstStr), (LSZ_AT*)(srcStr))
#endif

/**
 * to connect string b to the tail of string a
 * according the length parameter
 * 根据参数length将b串连接到a串的尾部
 */
extern LSZ_AT *LSZ_Str_cat(LSZ_AT *dstStr,
					LSZ_AT *srcStr);
#ifndef _LSZ_STRING_C_
#define LSZ_Str_cat(dstStr, srcStr) \
	(char*)LSZ_Str_cat((LSZ_AT*)(dstStr), (LSZ_AT*)(srcStr))
#endif

/**
 * to find the substring b int the string a
 * 在串a中找子串b，返回在a串的起始位置。
 */
extern LSZ_AT *LSZ_Str_sub(LSZ_AT *dstStr,
					LSZ_AT *subStr);
#ifndef _LSZ_STRING_C_
#define LSZ_Str_sub(dstStr, subStr) \
	(char*)LSZ_Str_sub((LSZ_AT*)(dstStr), (LSZ_AT*)(subStr))
#endif

/**
 * to find the substring b int the string a with KMP algorithm
 * 用KMP算法在串a中找子串b
 */
extern LSZ_AT *LSZ_Str_subKMP(LSZ_AT *dstStr,
						LSZ_AT *subStr);
#ifndef _LSZ_STRING_C_
#define LSZ_Str_subKMP(dstStr, subStr) \
	(char*)LSZ_Str_subKMP((LSZ_AT*)(dstStr), (LSZ_AT*)(subStr))
#endif

/**
 * to set the next of string using int KMP algorithm
 * 为KMP算法设置串的next位
 */
extern int* LSZ_Str_nextKMP(LSZ_AT *str);
#ifndef _LSZ_STRING_C_
#define LSZ_Str_nextKMP(str) \
	LSZ_Str_nextKMP((LSZ_AT*)(str))
#endif

//the end of file
#endif
