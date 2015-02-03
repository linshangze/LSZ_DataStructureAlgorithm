/*********************************************************************
 * File Name: testMinimunEditDistance.c
 * Author: linshangze
 * Mail: linshangze163@163.com 
 * Created Time: 2013-11-04-01:06:16 PM
 ********************************************************************/

#include <stdio.h>
#include  "LSZ_MinimumEditDistance.c" //方便测试

//输出编辑代价矩阵
void printArray(int **array, int countI, int countJ)
{
	int i, j;
	for(i = 0; i < countI; i++){
		for(j = 0; j < countJ; j++)
			printf("\t%d", array[i][j]);
		printf("\n");
	}
	printf("\n");
}

//测试请修改串长宏和字符串数组

#define LENGTH_SRC 3 //源串长
#define LENGTH_DST 9 //目标串长

int main(int argc, char const *argv[])
{
	char strA[] = "lin"; //源串
	char strB[] = "linszesze"; //目标串
	int costEdit[LENGTH_SRC + 1][LENGTH_DST + 1];
	int *(costEditFix[LENGTH_SRC+1]), i;

	printf("the cost from recursion is %d\n",
			LSZ_String_editMinCostRecursion(strA, LENGTH_SRC, strB, LENGTH_DST));
	for(i = 0; i <= LENGTH_SRC; i++){
		costEditFix[i] = costEdit[i];
	}
	printf("the cost from dynamic is %d\n", 
			LSZ_String_editMinCostDynamic(strA, LENGTH_SRC, strB, LENGTH_DST, costEditFix));
	printf("costEdit array is:\n");
	printArray(costEditFix, LENGTH_SRC + 1, LENGTH_DST + 1);

	return 0;
}
