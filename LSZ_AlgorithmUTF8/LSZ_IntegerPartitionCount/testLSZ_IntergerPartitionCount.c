/*********************************************************************
 * File Name: testLSZ_IntegerPartitionCount.c
 * Author: linshangze
 * Mail: linshangze163@163.com 
 * Created Time: 2014-01-15-10:20:07 HKT
 ********************************************************************/

#include <stdio.h>
#include "LSZ_IntegerPartitionCount.c"

#define INTEGER1 10
#define INTEGER2 5

int main(void)
{
	int result1[INTEGER1];
	int result2[INTEGER2];

	printf("%d\n", LSZ_integerPartitionCount(INTEGER1, INTEGER1));
	LSZ_integerPartition(INTEGER1, INTEGER1, result1, 0);

	printf("%d\n", LSZ_integerPartitionCount(INTEGER2, INTEGER2));
	LSZ_integerPartition(INTEGER2, INTEGER2, result2, 0);

	return 0;
}
