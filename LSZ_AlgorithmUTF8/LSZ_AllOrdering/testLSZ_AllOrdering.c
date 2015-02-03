/*********************************************************************
 * File Name: testLSZ_AllOrdering.c
 * Author: linshangze
 * Mail: linshangze163@163.com 
 * Created Time: 2014-01-14-01:36:51 HKT
 ********************************************************************/

#include <stdio.h>
#include "LSZ_AllOrdering.c"

int main(void)
{
	char elements[] = "abcde";

	LSZ_AllOrdering(elements, 0, 4);
	printf("\n%s\n", elements);
	return 0;
}
