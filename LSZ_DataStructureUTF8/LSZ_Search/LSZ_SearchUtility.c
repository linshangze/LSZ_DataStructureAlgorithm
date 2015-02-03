/*********************************************************************
 * File Name: LSZ_SearchUtility.c
 * Author: linshangze
 * Mail: linshangze163@163.com
 * Created Time: 2013-12-04-02:44:52 PM
 ********************************************************************/

#include <stdio.h>
#include "LSZ_Search.h"
#include "LSZ_SearchUtility.h"

/**
 * 打印整形int数组。
 * 打印下标从1到count。
 */
void LSZ_search_printArrayInt(int list[],
								int count)
{
	int i;
	printf(">>>the int in array:\n");
	for(i = 0; i <= count; i++){
		printf("%d  ", list[i]);
	}
	printf("\n");
	printf(">>>end\n");
}

/**
 * 打印浮点float数组。
 */
void LSZ_search_printArrayFloat(float list[],
								int count)
{
	int i;
	printf(">>>the float in array:\n");
	for(i = 0; i <= count; i++){
		printf("%f  ", list[i]);
	}
	printf("\n");
	printf(">>>end\n");
}

/**
 * 打印数组存储的LSZ_SearchE类型的元素的键值。
 */
void LSZ_search_printArrayKeyE(LSZ_SearchE list[],
								int count)
{
	int i;
	printf(">>>the key(E) in array:\n");
	for(i = 0; i <= count; i++){
		printf("%d  ", list[i].key);
	}
	printf("\n");
	printf(">>>end\n");
}

/**
 * 打印组数存储的二叉树结点LSZ_SearchBTArray类型的结点的键值。
 */
void LSZ_search_printArrayKeyBT(LSZ_SearchBTArray tree[],
								int count)
{
	int i;
	printf(">>>the key(BT) in array:\n");
	for(i = 0; i <= count; i++){
		printf("tree=%d, l= %d, r=%d\n", i, tree[i].lChild, tree[i].rChild);
	}
	printf("\n");
	printf(">>>end\n");
}

/**
 * 打印二叉排序平衡树的结点LSZ_SearchBBTNode类型的键值。
 */
void LSZ_search_printTreeKeyBSBT(LSZ_SearchBBTNode *tree,
									int mode)
{
	printf(">>>the key(BSBT) in tree (style %d):\n", mode);
	switch(mode){
		case 1:
			LSZ_search_doPrintTreeKeyBSBT1(tree->lChild);
			break;
		default:
			LSZ_search_doPrintTreeKeyBSBT0(tree->lChild);
			printf("\n");
	}
	printf(">>>end\n");
}

void LSZ_search_doPrintTreeKeyBSBT0(LSZ_SearchBBTNode *tree)
{
	printf("(");
	if(tree != NULL){
		if(tree->lChild != NULL){
			LSZ_search_doPrintTreeKeyBSBT0(tree->lChild);
			printf("<-");
		}
		printf("%d[%d]", tree->element->key, tree->fBalance);
		if(tree->rChild != NULL){
			printf("->");
			LSZ_search_doPrintTreeKeyBSBT0(tree->rChild);
		}
	}
	printf(")");
}

void LSZ_search_doPrintTreeKeyBSBT1(LSZ_SearchBBTNode *tree)
{
	static int depth = 0;
	int i;

	if(tree != NULL){
		if(tree->rChild != NULL){
			depth++;
			LSZ_search_doPrintTreeKeyBSBT1(tree->rChild);
		}
		for(i = 0; i < depth; i++){
			if(i + 1 != depth){
				printf("        ");
			}
			else{
				printf("    ---|");
			}
		}
		printf("%d[%d]\n", tree->element->key, tree->fBalance);
		if(tree->lChild != NULL){
			depth++;
			LSZ_search_doPrintTreeKeyBSBT1(tree->lChild);
		}
		depth--;
	}
	if(depth == -1){
		depth = 0;
	}
}

//end of file

