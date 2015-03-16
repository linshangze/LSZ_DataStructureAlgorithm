/*********************************************************************
 * File Name: testLSZ_Search.c
 * Author: linshangze
 * Mail: linshangze163@163.com
 * Created Time: 2013-10-24-07:56:03 PM
 ********************************************************************/

#include <stdio.h>
#include "./LSZ_Search.h"
#include "./LSZ_SearchUtility.h"

#define MAXCOUNT 64

//为了方便赋值设置的类型
typedef struct ArrayTest{
	LSZ_SearchE array[MAXCOUNT + 1];
}ArrayTest;

//零值数列
ArrayTest arrayZero = {{{0}}};
//递增数列
ArrayTest arrayIncrease ={{
	{0}, {1}, {2} ,{3}, {4}, {5}, {6}, {7}, {8}, {9},
	{10}, {11}, {12}, {13}, {14}, {15}, {16}, {17}, {18}, {19},
	{20}, {21}, {22}, {23}, {24}, {25}, {26}, {27}, {28}, {29},
	{30}, {31}, {32}, {33}, {34}, {35}, {36}, {37}, {38}, {39},
	{40}, {41}, {42}, {43}, {44}, {45}, {46}, {47}, {48}, {49},
	{50}, {51}, {52}, {53}, {54}, {55}, {56}, {57}, {58}, {59},
	{60}, {61}, {62}, {63}, {64}//, {65}, {66}, {67}, {68}, {69},
//	{70}, {71}, {72}, {73}, {74}, {75}, {76}, {77}, {78}, {79},
//	{80}, {81}, {82}, {83}, {84}, {85}, {86}, {87}, {88}, {89},
//	{90}, {91}, {92}, {93}, {94}, {95}, {96}, {97}, {98}, {99},
//	{100, {101}, {102}, {103}, {104}, {105}, {106}, {107}, {108}, {109},
//	{110, {111}, {112}, {113}, {114}, {115}, {116}, {117}, {118}, {119},
//	{120, {121}, {122}, {123}, {124}, {125}, {126}, {127}, {128}, {129}
}};
ArrayTest arrayIncrease1 = {{
	{0}, {1}, {2} ,{3}, {4}, {5}, {6}, {7}, {8}, {9},
	{10}, {11}, {12}, {13}, {14}, {15}, {16}, {17}, {18}, {19},
	{20}, {21}, {22}, {23}, {24}, {25}, {26}, {27}, {28}, {29},
	{30}, {31}, {32}, {33}, {34}, {35}, {36}, {37}, {38}, {39},
	{40}, {41}, {42}, {43}, {44}, {45}, {46}, {47}, {48}, {49},
	{50}, {51}, {52}, {53}, {54}, {55}, {56}, {57}, {58}, {59},
	{60}, {61}, {62}, {63}, {65}
}};

int main(int argc, char *argv[])
{
	ArrayTest array;
	int arrayTemp[47];
	LSZ_SearchBTArray tree[MAXCOUNT + 1];
	float weight[MAXCOUNT + 1], weightHeap[MAXCOUNT + 1];
	int i;

	LSZ_search_printArrayKeyE(arrayZero.array + 1, MAXCOUNT);
	LSZ_search_printArrayKeyE(arrayIncrease.array + 1, MAXCOUNT);

	printf("\n***********************************\n");
	printf("静态查找\n");
	printf("***********************************\n\n");

	printf("顺序查找***********************************\n");
	//顺序查找
	array = arrayZero;
	array.array[1].key = 32; //0, 1, 32, 64, 65
//	LSZ_search_printArrayKeyE(array.array + 1, MAXCOUNT);
	printf("search index sequently: %d\n",
		LSZ_search_sequence(array.array, 32, MAXCOUNT));
	printf("search index sequently comparision: %d\n",
		LSZ_search_sequenceComparision(array.array, 32, MAXCOUNT));
	
	printf("二分法查找***********************************\n");
	//二分法查找
	array = arrayIncrease;
//	printArray1(array.array, MAXCOUNT);
	printf("search index binary: %d\n",
		LSZ_search_binary(array.array, 64, MAXCOUNT));

	printf("斐波那契查找***********************************\n");
	//斐波那契查找
	array = arrayIncrease1;
//	printArray1(array.array, MAXCOUNT);
	LSZ_getFibonacciNumber(arrayTemp, 47);
//	printArray2(arrayTemp - 1, 47);
	printf("search index fibonacci: %d\n", //55,3,64
		LSZ_search_fibonacci(array.array, 65, MAXCOUNT));//MAXCOUNT));
	printf("search index fibonacci comparision: %d\n", //55,3,64
		LSZ_search_fibonacciComparision(array.array, 0, 1, arrayTemp, MAXCOUNT));
	//已通过测试：
	//对最小键值查找，正确
	//对最大键值查找，正确
	//不存在的相对小的键值查找，正确
	//不存在的相对大的键值查找，正确
	//设置最大能处理的斐波那契树为fNumber[10]，能正确拆分查找

	printf("次优二叉树查找***********************************\n");
	//次优二叉树查找
	array = arrayIncrease1;
	for(i = 0; i < MAXCOUNT + 1; i++){
		weight[i] = i % 5; //构造随机查找概率权值
	}
	LSZ_search_setNearOptimalTree(array.array, tree, weight, weightHeap, MAXCOUNT);
	printf("search index static tree: %d\n", //55,3,64,165
		LSZ_search_staticTree(tree, 5, MAXCOUNT));
	//已通过测试：
	//对最小键值查找，正确
	//对最大键值查找，正确
	//不存在的相对小的键值查找，正确
	//不存在的相对大的键值查找，正确

	printf("\n***********************************\n");
	printf("动态查找\n");
	printf("***********************************\n\n");

	printf("二叉排序树查找***********************************\n");
	//二叉排序树查找
	LSZ_SearchBTNode treeHeader;
	LSZ_SearchE eTemp = {32};;
	LSZ_SEARCH_TREEINIT(treeHeader);
	printf("search key 32 binary tree only: %d\n",
		LSZ_search_treeBinarySorted(&treeHeader, &eTemp, LSZ_SEARCH_ONLY));
	printf("search key 32 binary tree insert: %d\n",
		LSZ_search_treeBinarySorted(&treeHeader, &eTemp, LSZ_SEARCH_INSERT));

	eTemp.key = 1;
	printf("search key 1 binary tree insert: %d\n",
		LSZ_search_treeBinarySorted(&treeHeader, &eTemp, LSZ_SEARCH_INSERT));

	eTemp.key = 64;
	printf("search key 64 binary tree insert: %d\n",
		LSZ_search_treeBinarySorted(&treeHeader, &eTemp, LSZ_SEARCH_INSERT));

	eTemp.key = 0; //64
	printf("search key 0 binary tree only: %d\n",
		LSZ_search_treeBinarySorted(&treeHeader, &eTemp, LSZ_SEARCH_ONLY));

	eTemp.key = 311; //测试结点删除
	printf("search key %d binary tree delete: %d\n", eTemp.key,
		LSZ_search_treeBinarySorted(&treeHeader, &eTemp, LSZ_SEARCH_DELETE));

	eTemp.key = 32; //测试删除后的树
	printf("search key %d binary tree only: %d\n", eTemp.key,
		LSZ_search_treeBinarySorted(&treeHeader, &eTemp, LSZ_SEARCH_ONLY));

	LSZ_search_destroyBST(&treeHeader);
	printf("###destroy the binary sorted tree.\n");
	//已通过测试：
	//对空树仅查找操作，返回-1，正确
	//对空树插入根节点，返回0，正确
	//对根进行左插入返回1，再查找已插入结点返回0，正确
	//对根进行右插入返回1，再查找已插入结点返回0，正确
	//对重复插入结点，返回0，正确
	//对已插入结点删除，返回1，正确
	//对不存在结点删除，返回-1，错误，已改正，返回0，正确
	//对树进行销毁，测试释最大放结点次数3，正确


	printf("二叉排序平衡树查找***********************************\n");
	//二叉排序平衡树查找
	LSZ_SearchBBTNode bTreeHeader;
	LSZ_SEARCH_TREEINIT(bTreeHeader);
	eTemp.key = 32;
	printf("search key 32 binary tree only: %d\n",
		LSZ_search_treeBinarySortedBalanced(&bTreeHeader, &eTemp, LSZ_SEARCH_ONLY));

	for(i = 0; i < 64; i += 8){
//	for(i = 64; i > 0; i -= 8){
		eTemp.key = i;
		printf("search key %d binary tree insert: %d\n", eTemp.key,
			LSZ_search_treeBinarySortedBalanced(&bTreeHeader, &eTemp, LSZ_SEARCH_INSERT));
		printf("search key %d binary tree only: %d\n", eTemp.key,
			LSZ_search_treeBinarySortedBalanced(&bTreeHeader, &eTemp, LSZ_SEARCH_ONLY));
		printf("the root now is : %d\n", ((bTreeHeader.lChild)->element)->key);
		LSZ_search_printTreeKeyBSBT(&bTreeHeader, 1);
	}

	eTemp.key = 8;
	printf("search key %d binary tree insert: %d\n", eTemp.key,
		LSZ_search_treeBinarySortedBalanced(&bTreeHeader, &eTemp, LSZ_SEARCH_INSERT));
	LSZ_search_printTreeKeyBSBT(&bTreeHeader, 1);

	eTemp.key = 56;
	printf("search key %d binary tree delete: %d\n", eTemp.key,
		LSZ_search_treeBinarySortedBalanced(&bTreeHeader, &eTemp, LSZ_SEARCH_DELETE));
	LSZ_search_printTreeKeyBSBT(&bTreeHeader, 1);

	LSZ_search_destroyBSBT(&bTreeHeader);
	printf("###destroy the binary sorted balanced tree.\n");
	//已通过测试：
	//对空树仅查找操作，返回-1，正确
	//对空树插入根节点，返回0，正确
	//对空树进行左左插入8个结点，正确
	//对空树进行右右插入8个结点，正确
	//对重复插入结点，返回0，正确
	//右右插入20，25，64，2后，返回的根结点为25，正确
	//右右插入20，25，64，2后，删除64，返回的根结点为20，正确
	//依次插入20，25，64，2后，再插入22，21，返回的根结点为22，正确
	//右右插入20，25，64，2后，删除25，再插入25，22，21，返回20出错，
	//		删除根操作平衡因子调整出错，导致插入出错，已改正
	//对树进行销毁，测试释最大放结点次数3，正确

	return 0;
}
