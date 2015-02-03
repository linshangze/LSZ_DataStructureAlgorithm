/*********************************************************************
 * File Name: LSZ_SearchHeader.h
 * Author: linshangze
 * Mail: linshangze163@163.com
 * Created Time: 2013-10-25-01:22:02 PM
 ********************************************************************/

#ifndef _LSZ_SEARCH_H_
#define _LSZ_SEARCH_H_

#include "LSZ_SearchElement.h"

//大于等于1小于等于46，能处理的斐波那契数极限
#define LSZ_SEARCH_FIBONACCI_MAX 46

//动态查找时标记是否进行操作常量
#define LSZ_SEARCH_ONLY 0 //仅作查找
#define LSZ_SEARCH_INSERT 1 //没有则插入
#define LSZ_SEARCH_DELETE 2 //找到则删除

//////////////////////////////////////////////////////////////////////
//静态查找
//////////////////////////////////////////////////////////////////////
//顺序表查找-顺序查找
extern int LSZ_search_sequence(LSZ_SearchE list[],
								LSZ_SearchK key,
								int count);
extern int LSZ_search_sequenceComparision(LSZ_SearchE list[],
								LSZ_SearchK key,
								int count);
//有序顺序表-二分法查找
extern int LSZ_search_binary(LSZ_SearchE list[],
								LSZ_SearchK key,
								int count);
extern int LSZ_search_binaryComparision(LSZ_SearchE list[],
								LSZ_SearchK key,
								int count);
//有序顺序表-斐波那契查找
extern int LSZ_search_fibonacci(LSZ_SearchE list[],
								LSZ_SearchK key,
								int count);
extern int LSZ_search_fibonacciComparision(LSZ_SearchE list[],
								int low,
								LSZ_SearchK key,
								int fibonacciNumber[],
								int count);
extern int LSZ_search_fibonacciFixComparision(LSZ_SearchE list[],
									int low,
									LSZ_SearchK key,
									int fibonacciNumber[],
									int fibonacciIndex);
extern int LSZ_getFibonacciNumber(int fibonacciNumber[],
									int countNumber);
//有序顺序表-被查找概率分布不均-静态树查找
extern int LSZ_search_staticTree(LSZ_SearchBTArray tree[],
									LSZ_SearchK key,
									int count);
extern int LSZ_search_setNearOptimalTree(LSZ_SearchE list[],
											LSZ_SearchBTArray tree[],
											float weight[],
											float weightHeap[],
											int count);
extern int LSZ_search_nearOptimalTree(LSZ_SearchE list[],
											LSZ_SearchBTArray tree[],
											float weightHeap[],
											int low,
											int high);
//////////////////////////////////////////////////////////////////////
//动态查找
//////////////////////////////////////////////////////////////////////
//删除树结点的宏
#define LSZ_SEARCH_DESTROYNODE(node) (free((node)->element),free(node))
//初始化树头结点的宏
#define LSZ_SEARCH_TREEINIT(tree) ((tree).lChild=NULL)

//动态查找-二叉排序树查找
extern int LSZ_search_treeBinarySorted(LSZ_SearchBTNode *tree,
										LSZ_SearchE *element,
										int mode);
extern int LSZ_search_insertBST(LSZ_SearchBTNode *treePrevious,
								LSZ_SearchE *element,
								int where);
extern int LSZ_search_deleteBST(LSZ_SearchBTNode *treePrevious,
								LSZ_SearchBTNode *treeDelete,
								int where);
extern void LSZ_search_destroyBST(LSZ_SearchBTNode *tree);
extern void LSZ_search_doDestroyBST(LSZ_SearchBTNode *tree);

//动态查找-二叉排序平衡树查找
extern int LSZ_search_treeBinarySortedBalanced(LSZ_SearchBBTNode *tree,
												LSZ_SearchE *element,
												int mode);
extern int LSZ_search_insertBSBT(LSZ_SearchBBTNode **tree,
									LSZ_SearchE *element,
									int *isHigher);
extern int LSZ_search_deleteBSBT(LSZ_SearchBBTNode **tree,
									LSZ_SearchE *element,
									int *isLower);
extern void LSZ_search_lBalanceBSBT(LSZ_SearchBBTNode **tree);
extern void LSZ_search_rBalanceBSBT(LSZ_SearchBBTNode **tree);
extern void LSZ_search_lRotateBSBT(LSZ_SearchBBTNode **tree);
extern void LSZ_search_rRotateBSBT(LSZ_SearchBBTNode **tree);
extern void LSZ_search_destroyBSBT(LSZ_SearchBBTNode *tree);
extern void LSZ_search_doDestroyBSBT(LSZ_SearchBBTNode *tree);

//end of file
#endif
