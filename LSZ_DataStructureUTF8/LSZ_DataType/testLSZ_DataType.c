/********************************************************************
 *File Name: testLSZ_DataType.c
 *Author: Linshangze//林上泽
 *Mail: linshangze163@163.com
 *Created Time: 2013-08-28
 *Updated Time: 2015-01-10
 *******************************************************************/

/********************************************************************
 *test file for LSZ_DataType
 *LSZ_DataType测试源文件
 *******************************************************************/

#include <stdio.h>
#include "LSZ_DataType.h"

typedef struct Test{
	char check1;
	int check2;
	LSZ_AT check3;
}Test;

int main()
{
//////////////////////////////////////////////////////////////////////
//for LSZ_AT
	Test t1 = {'0', 99}, t2 = { '1', 59}, t3 = {'2', 0};
	LSZ_AT t4;

	LSZ_AT_init(t1.check3);
	LSZ_AT_dest(t2.check3);
	LSZ_AT_dest(t3.check3); 
	printf("check1: t1 = %c, t2 = %c, t3 = %c\n",
			t1.check1, t2.check1, t3.check1);
	printf("check2: t1 = %d, t2 = %d, t3 = %d\n",
			t1.check2, t2.check2, t3.check2);
	printf("check3: t1 = %u, t2 = %u, t3 = %u\n",
			t1.check3, t2.check3, t3.check3);
	printf("size, check3: t1=%ld, t2=%ld, t2=%ld\n", LSZ_AT_size(t1.check3),
			LSZ_AT_size(t1.check3), LSZ_AT_size(t1.check3));
	LSZ_AT_wt(t1.check3, 1);
	LSZ_AT_wt(t2.check3, 0);
	LSZ_AT_wt(t3.check3, -1); 
	printf("wt, check3: t1 = %u, t2 = %u, t3 = %u\n",
			t1.check3, t2.check3, t3.check3);
	LSZ_AT_rd(t4, t1.check3);
	printf("rd, t1.check3: t4=%u\n", t4);
	LSZ_AT_rd(t4, t2.check3);
	printf("rd, t2.check3: t4=%u\n", t4);
	LSZ_AT_rd(t4, t3.check3); 
	printf("rd, t3.check3: t4=%u\n", t4);
	LSZ_AT_swap(t1.check3, t3.check3);
	LSZ_AT_swap(t2.check3, t2.check3);
	printf("swap, check3: t1 = %u, t2 = %u, t3 = %u\n",
			t1.check3, t2.check3, t3.check3);
	printf("gt, t1, t2, check3: %d\n", LSZ_AT_gt(t1.check3, t2.check3));
	printf("gt, t2, t2, check3: %d\n", LSZ_AT_gt(t2.check3, t2.check3));
	printf("gt, t2, t3, check3: %d\n", LSZ_AT_gt(t2.check3, t3.check3));
	printf("eq, t1, t2, check3: %d\n", LSZ_AT_eq(t1.check3, t2.check3));
	printf("eq, t2, t2, check3: %d\n", LSZ_AT_eq(t2.check3, t2.check3));
	printf("eq, t2, t3, check3: %d\n", LSZ_AT_eq(t2.check3, t3.check3));
	printf("lt, t1, t2, check3: %d\n", LSZ_AT_lt(t1.check3, t2.check3));
	printf("lt, t2, t2, check3: %d\n", LSZ_AT_lt(t2.check3, t2.check3));
	printf("lt, t2, t3, check3: %d\n", LSZ_AT_lt(t2.check3, t3.check3));

//////////////////////////////////////////////////////////////////////
//for LSZ_MT
	LSZ_MT x, y, z;

	LSZ_MT_init(&x);
	LSZ_MT_init(&y);
	LSZ_MT_init(&z);
	printf("init: x = %s, y = %s, z = %s\n",
			(char*)(x.data), (char*)(y.data), (char*)(z.data));
	LSZ_MT_wt(&x, &t1);
	LSZ_MT_wt(&y, &t2);
	LSZ_MT_wt(&z, &t3);
	printf("wt, eq, x, y: %d\n", LSZ_MT_eq(&x, &y));
	printf("wt, eq, y, y: %d\n", LSZ_MT_eq(&y, &y));
	printf("wt, eq, y, z: %d\n", LSZ_MT_eq(&y, &z));
	printf("size, x = %ld, y = %ld, z = %ld\n",
			LSZ_MT_size(&x), LSZ_MT_size(&y), LSZ_MT_size(&z));
	LSZ_MT_swap(&x, &z);
	LSZ_MT_swap(&y, &y);
	LSZ_MT_rd(&t1, &x);
	LSZ_MT_rd(&t2, &y);
	LSZ_MT_rd(&t3, &z);
	printf("rd, swap: t1 = %c, t2 = %c, t3 = %c\n",
			t1.check1, t2.check1, t3.check1);
	printf("rd, swap: t1 = %d, t2 = %d, t3 = %d\n",
			t1.check2, t2.check2, t3.check2);
	printf("rd, swap: t1 = %u, t2 = %u, t3 = %u\n",
			t1.check3, t2.check3, t3.check3);
	LSZ_MT_wt0(&x);
	LSZ_MT_rd(&t1, &x);
	printf("wt0, t1: check1 = %c, check2 = %d, check3 = %u\n",
			t1.check1, t1.check2, t1.check3);
	LSZ_MT_dest(&x);
	LSZ_MT_dest(&y);
	LSZ_MT_dest(&z);
	printf("dest: x = %s, y = %s, z = %s\n",
			(char*)(x.data), (char*)(y.data), (char*)(z.data));
	return 0;
}
