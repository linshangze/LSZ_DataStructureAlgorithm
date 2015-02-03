/*********************************************************************
 * File Name: LSZ_SearchElement.h
 * Author: linshangze
 * Mail: linshangze163@163.com
 * Created Time: 2013-10-24-06:24:25 PM
 ********************************************************************/

#ifndef _LSZ_SEARCHELEMENT_H_
#define _LSZ_SEARCHELEMENT_H_

/**
 * 树的结点位置标识常量。
 */

//父母结点。
#define LSZ_SEARCH_PARENT 0
//左孩子结点。
#define LSZ_SEARCH_LCHILD 1
//右孩子结点。
#define LSZ_SEARCH_RCHILD 2

/**
 * 树的平衡因子常量。
 */

//平衡因子之差绝对值。
#define LSZ_SEARCH_BALANCEDIFF 1
//左右子树深度平衡。
#define LSZ_SEARCH_EQUALHIGH 0
//左子树深。
#define LSZ_SEARCH_LEFTHIGH \
	((LSZ_SEARCH_EQUALHIGH)+(LSZ_SEARCH_BALANCEDIFF))
//右子树深。
#define LSZ_SEARCH_RIGHTHIGH \
	((LSZ_SEARCH_EQUALHIGH)-(LSZ_SEARCH_BALANCEDIFF))

/**
 * 树高度的变化。
 */

//树的高度是否增加。
#define LSZ_SEARCH_HIGHERTRUE 1
#define LSZ_SEARCH_HIGHERFALSE 0
//树的高度是否减少。
#define LSZ_SEARCH_LOWERTRUE 1
#define LSZ_SEARCH_LOWERFALSE 0

/**
 * 元素的关键字类型
 */

typedef int LSZ_SearchK;

/**
 * 元素类型
 */

typedef struct LSZ_SearchE{ //element
	LSZ_SearchK key; //元素的键值，用于唯一标识
}LSZ_SearchE;

/**
 * 顺序存储的树的子树的索引类型
 */

typedef int LSZ_SearchTreeIndex;

/**
 * 顺序存储的查找树结构的元素类型
 */

//二叉树的结点类型
typedef struct LSZ_SearchBTArray{ //binary tree
	LSZ_SearchE *element;
	LSZ_SearchTreeIndex lChild;
	LSZ_SearchTreeIndex rChild;
}LSZ_SearchBTArray;

/**
 * 非顺序存储的查找树的结构元素类型
 */

//二叉树的结点类型
typedef struct LSZ_SearchBTNode{ //binary tree
	LSZ_SearchE *element;
	struct LSZ_SearchBTNode *lChild;
	struct LSZ_SearchBTNode *rChild;
}LSZ_SearchBTNode;

/**
 * 带平衡因子的非顺序存储的查找树的结构元素类型
 */

//二叉平衡树的结点类型
typedef struct LSZ_SearchBBTNode{ //binary,balance, tree
	int fBalance; //factor of balance
	LSZ_SearchE *element;
	struct LSZ_SearchBBTNode *lChild;
	struct LSZ_SearchBBTNode *rChild;
}LSZ_SearchBBTNode;

/**
 * 非顺序存储的m阶B_树（balanced tree of order m）的结构元素类型。
 */

//B-树（B_树）的结点类型。
#define LSZ_SEARCH_B_T_ORDERMAX 8 //B_树的阶数，因为代码实现原因阶数>=3。
#define LSZ_SEARCH_B_T_INDEXMID \
	((LSZ_SEARCH_B_T_ORDERMAX>>2)+1)//B_树结点记录数组的“分裂”处下标。
#define LSZ_SEARCH_B_T_COUNTSPLIT \
	(LSZ_SEARCH_B_T_ORDERMAX-LSZ_SEARCH_B_T_INDEXMID)//B_树结点“分裂”出来的结点初始记录个数。

typedef struct LSZ_SearchB_TNode{
	int countKey; //the number of keys
	struct LSZ_SearchB_TNode *parent; //在树的平衡调整时会用到。
	LSZ_SearchE *(elements[LSZ_SEARCH_B_T_ORDERMAX + 1]); //首元素保留用。
	struct LSZ_SearchB_TNode *(children[LSZ_SEARCH_B_T_ORDERMAX + 1]); //指向子树根结点，第一个元素使用。
}LSZ_SearchB_TNode;

//end of file
#endif

