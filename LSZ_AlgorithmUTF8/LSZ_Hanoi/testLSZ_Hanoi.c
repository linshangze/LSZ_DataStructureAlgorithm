/*********************************************************************
 * File Name: testLSZ_Hanoi.c
 * Author: linshangze
 * Mail: linshangze163@163.com 
 * Created Time: 2014-01-16-11:04:46 HKT
 ********************************************************************/

#include <stdio.h>
#include "LSZ_Hanoi.c"

#define HANOI_COUNT 2 
int main(void)
{
	LSZ_hanoi(1, 2, 3, HANOI_COUNT);
	printf("源塔1，目标塔2，辅助塔3，圆盘个数%d\n", HANOI_COUNT);
	return 0;
}
