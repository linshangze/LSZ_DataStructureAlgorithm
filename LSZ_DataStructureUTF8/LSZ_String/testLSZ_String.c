/********************************************************************
 *File Name: testLSZ_LinearListL.c
 *Author: Linshangze//林上泽
 *Mail: linshangze163@163.com
 *Created Time: 2012-08-14
 *Updated Time: 2015-01-20
 *******************************************************************/

/********************************************************************
 *test file for LSZ_String
 *LSZ_String测试源文件
 *******************************************************************/

#include <stdio.h>
#include <malloc.h>
#include "LSZ_String.h"

int main(void)
{
	char aStr[80], bStr[80] = "12345";

	printf("copy: %s\n", LSZ_Str_copy(aStr, bStr));
	printf("cat: %s\n", LSZ_Str_cat(aStr, "67890"));
	printf("sub: %s\n", LSZ_Str_sub(aStr, "67"));
	printf("sub KMP: %s\n", LSZ_Str_subKMP(aStr, "67"));
	return 0;
}

