/*********************************************************************
 * File Name: LSZ_SearchDynamicB_T.c
 * Author: linshangze
 * Mail: linshangze163@163.com
 * Created Time: 2013-11-21-09:47:53 PM
 ********************************************************************/

#ifndef LSZ_SEARCHDYNAMIC_BPLUST_C_
#define LSZ_SEARCHDYNAMIC_BPLUST_C_

#include <malloc.h>
#include <stdlib.h>
#include "LSZ_Search.h"

//名称：B+树查找
//关键字：B_树，B+树，多路搜索
//
//b-树（balanced tree）的概念。
//
//B_树的定义：
//    树为空树，或树为m阶树。m阶树的约束条件如下：
//    (1)每个结点至多有m棵子树，最多有m-1个键值。
//    (2)根结点如果不是叶子结点，则至少有2棵子树（则至少有1个关键字）。
//    (3)除根以外的非终端结点（叶子结点）至少有m/2（上取整）棵子树。
//       2和3特征是和树的动态变化有关。
//    (4)所有的非终端结点中包含下列信息数据：
//        (count, child0, key1, ..., keyn, childn);
//       其中count为该结点key的个数，(m+1)/2-1<=count<=m-1。
//       keyi<keyi+1(i=1,...,n-1)。
//       child是指向子树根结点的指针，childi子树的所有结点的关键字
//       均大于keyi且小于keyi+1。
//       上面没有写出的还有count个对应关键字的记录数据。
//    (5)树的所有的叶子结点深度相同，叶子结点为空结点，平衡特征。
//    B_树是一种平衡树。
//    例如一3阶B_树示意：
//                     (a1,   k1,   a2,    k2    a2)
//                      /            |            \
//      (b1,k3,b2,k4,b3)     (c1,k5,c2,k6,c3)     (e1,k7,e2)
//       |     |     |        |     |     |         |     |
//       n     n     n        n     n     n         n     n
//    其中abcde为指向子树根的指针，每个结点的k都不同，n为空结点。图中
//    没有画出键值对应的数据记录。
//
//B_树的查找：
//  查找和二叉排序树的查找有相似，先用目标键值和树的根结点的键值依次比
//  较，结点的键值是有序的，可以用折半等有序的查找方法查找。如果在一个
//  结点没有要查找的键值，根据子树的结点的键值和该结点键值的关系，找到
//  符合范围的子树，继续查找子树就好了。
//
//B_树的查找分析：
//  设m阶的B_树深度为l+1，根据B_树的定义，第一层至少有1个键值，第二层
//  至少有2个键值，除根之外的结点至少有m/2（上取整）棵子树，所以第三层
//  至少有2*m/2（m/2是上取整，后说明略）个键值。以此类推，第l+1层至少
//  有2*((m/2)^(l-1))个键值，且l+1层为叶子结点。因此，该B_树上有N个键
//  值时，则叶子查找不成功的结点为N+1，可得：
//  N+1>=2*((m+1)/2)^(l-1);
//  反之：
//  l<=log(m/2)(((N+1)/2)+1);
//  说明了，在N个关键子的B_树查找时，涉及结点树不超过
//  log(m/2)(((N+1)/2)+1)。

/**
 * B_树查找
 * 仅查找成功返回0，有插入或删除动作执行返回1，失败返回-1。
 *
 * tree：其children[0]成员指向树的根结点。
 * element：当往树中插入结点时，其指向空间存放传入值，
 *	       其它情况指向空间用于记录查找到元素的值。
 * mode：仅查找，或带插入的查找，或带删除的查找。
 */
int LSZ_search_treeBlanced(LSZ_SearchB_TNode *tree,
							LSZ_SearchE *element,
							int mode)
{
	int index;
	LSZ_SearchB_TNode *nodeTemp = (tree->children)[0]; //树的根结点

	while(nodeTemp != NULL){ //结点不为空。
		if(LSZ_search_treeBlancedOneNode(
				nodeTemp, element, &index) == 0){
			return 0;
		}
		nodeTemp = (nodeTemp->children)[index]; //查找孩子结点。
	}
	return -1;
}

/**
 * B_树一个结点键值的查找
 * 查找成功返回0，查找失败返回-1。
 *
 * list：结点的记录表。
 * element：指向要查找的记录的键值，查找成功后存储查找到的记录的值。
 * index：如果查找失败，返回记录下标，否则，用于返回要查找的子树位置。
 * countKey：记录的个数。
 */
int LSZ_search_treeBlancedOneNode(LSZ_SearchB_TNode *node,
									LSZ_SearchE *element,
									int *index)
{
	int low = 1, high = node->countKey, mid;

	while(low <= high){
		mid = (low + high) / 2;
		if(((node->elements)[mid])->key == element->key){
			*index = mid;
			*element = *((node->elements)[mid]);
			return 0;
		}
		else if(((node->elements)[mid])->key > element->key){
			high = mid - 1;
		}
		else{
			low = mid + 1;
		}
	}
	//上面查找失败，low和high的值会相差1，而high刚好为子树的位置。
	*index = high;
	return -1;
}

//B_树的插入
//
//B_树在动态插入的过程中，怎么和它的特征相应呢？
//  假设有3阶B_树
//  1)空树
//    header->NULL
//
//  2)插入根结点记录k1
//                       *  *  *
//    header------>boot(a1,k1,a2)
//                      |      |
//                     NULL   NULL
//
//  3)继续往新结点中插入记录直至
//                          *  *
//    header------>boot(a1,k2,a3,k1,a2)
//                      ||     |    ||
//                     NULL   NULL  NULL
//
//  4)继续往新结点中插入记录，假设插入k3
//                                *  *
//    header------>boot(a1,k2,a3,k3,a4,k1,a2)
//                      ||    ||     |    ||
//                     NULL  NULL   NULL  NULL
//    此时进行“分裂”
//    header------>?   (a1,k2,a3)   (b1,k3,b2)   (a4,k1,a2)
//                      ||    ||     |      |     ||    ||
//                     NULL   NULL  NULL   NULL  NULL   NULL
//    连接
//                       *  *  *
//    header------>boot(b1,k3,b2)
//                      |      |
//             (a1,k2,a3)      (a4,k1,a2)
//              ||    ||        ||    ||
//             NULL   NULL     NULL   NULL
//
//  5)继续往右结点中插入记录，直至：
//    header------>boot(b1,k3,b2)
//                     ||      ||               *  *
//             (a1,k2,a3)      (a4,k1,a2,k4,c1,k5,c2)
//              ||    ||        ||    ||    ||     |
//             NULL   NULL     NULL   NULL  NULL  NULL
//    右结点“分裂”后，合并部分到父母结点。
//                                      *    *
//    header------>boot(b1,  k3,  b2,  k4,  d1)
//                     ||         ||         |
//             (a1,k2,a3)     (a4,k1,a2)     (c1,k5,c2)
//              ||    ||       ||    ||       ||    ||
//             NULL   NULL    NULL   NULL    NULL   NULL
//
//  6)继续往右结点中插入记录，直至：
//    header------>boot(b1,  k3,  b2,  k4,  d1)
//                     ||         ||         ||               *  *
//             (a1,k2,a3)     (a4,k1,a2)     (c1,k5,c2,k6,e1,k7,e2)
//              ||    ||       ||    ||       ||    ||    ||    |
//             NULL   NULL    NULL   NULL    NULL  NULL  NULL  NULL
//
//                                                *    *
//    header------>boot(b1,  k3,  b2,  k4,  d1,  k6,  f1)
//                     ||         ||        ||         |
//             (a1,k2,a3)    (a4,k1,a2)  (c1,k5,c2)    (e1,k7,e2)
//              ||    ||      ||    ||    ||    ||      ||    ||
//             NULL   NULL   NULL  NULL  NULL  NULL    NULL  NULL
//
//                        *             *             *
//    header------>boot(g1,           k4,             g2)
//                       |                            |
//                     (b1,  k3,  b2)      (d1,  k6,  f1)
//                     ||         ||        ||         ||
//             (a1,k2,a3)    (a4,k1,a2)  (c1,k5,c2)    (e1,k7,e2)
//              ||    ||      ||    ||    ||    ||      ||    ||
//             NULL   NULL   NULL  NULL  NULL  NULL    NULL  NULL
//
//  图中带*号的键值或子树被标记为新插入，用||连接的子树为不变的子树。
//  可已看到，B_树的插入是由端点结点向根调整的，并且由于“分裂”操
//  作，保持了树是平衡的。插入操作和B_树的特征是一致的。
//
//  为保持一致操作，如果插入的是结点的第一个记录，那么需确认它的
//  左子树和右子树，否则，当由端点结点向父母结点调整时，父母结点
//  新键值的左结点还是指向原来的结点（是上图分裂结点的左边），其
//  右孩子结点是新结点（上图分裂的右边）。孩子结点的指向不变。
//
//  在编程中，要注意某一步骤的动态空间申请失败导致树的结构被破坏或
//  内存泄露。在代码里，为了实现恢复，尽量少破坏原结点的信息，并利
//  用新“分裂”出来的结点空闲部分来保存恢复信息。代码的实现要求B_树
//  的阶至少为3。

/**
 * 往B_树中插入结点
 *
 * tree：指向树的头结点，其parent成员指向树根。
 * node：指向树插入记录的结点。
 * index：新记录插入的位置。
 * element：指插入记录的存放空间。
 */
int LSZ_Search_insertB_T(LSZ_SearchB_TNode *tree,
							LSZ_SearchB_TNode *node,
							int index,
							LSZ_SearchE *element)
{
	int indexTemp; //在插入记录前用于挪动数据。
	LSZ_SearchE *elementNew; //指向记录要插入的空间。
	LSZ_SearchB_TNode *nodeSplit = NULL; //指向用于“分裂”的临时结点。
	LSZ_SearchB_TNode *nodeSplitTrack = NULL; //记录“分裂”结点的轨迹，用于出错恢复。

	//申请新记录空间。
	if((elementNew = (LSZ_SearchE*)malloc(sizeof(LSZ_SearchE))) == NULL){
		return -1;
	}
	*elementNew = *element; //记录空间被赋值。
	while(node != NULL){
		//挪动元素并在elements[index]插入记录，index>=1。
		for(indexTemp = node->countKey; indexTemp != index; indexTemp--){
			(node->elements)[indexTemp] = (node->elements)[indexTemp - 1];
			(node->children)[indexTemp] = (node->children)[indexTemp - 1];
		}
		node->elements[index] = elementNew; //插入记录
		node->children[index] = nodeSplit; //新记录的右孩子需要改变。
		//保存恢复信息
		nodeSplit->children[LSZ_SEARCH_B_T_ORDERMAX - 1] = node;
		nodeSplit->children[LSZ_SEARCH_B_T_ORDERMAX] = nodeSplitTrack;
		nodeSplitTrack = nodeSplit;

		if(++(node->countKey) == LSZ_SEARCH_B_T_ORDERMAX){ //需要“分裂”。
			if((nodeSplit = (LSZ_SearchB_TNode*)malloc(
					sizeof(LSZ_SearchB_TNode))) == NULL){ //“分裂”失败，需要恢复。
				(node->countKey)--; //记录个数恢复。
				while(nodeSplitTrack != NULL){
					//恢复原结点和分裂结点，直至回溯到最初的“分裂”结点。
					node = (nodeSplitTrack->children)[LSZ_SEARCH_B_T_ORDERMAX - 1];
					nodeSplit = (nodeSplitTrack->children)[LSZ_SEARCH_B_T_ORDERMAX];
					node->countKey = LSZ_SEARCH_B_T_ORDERMAX - 1; //因为原结点只被更记录个数。
					nodeSplitTrack = (nodeSplitTrack->children)[LSZ_SEARCH_B_T_ORDERMAX];
					free(nodeSplit);
				}
			}
		}
	}
	return 1;
}

/**
 * B_树一个结点记录的插入
 * 插入成功返回1。
 *
 * node：指向插入记录的结点。
 * element：指向要查找的记录的键值，查找成功后存储查找到的记录的值。
 * index：如果查找失败，则用于返回要查找的子树位置。
 * countKey：记录的个数。
 */
int LSZ_search_insertB_TOneNode(LSZ_SearchB_TNode *node,
								LSZ_SearchB_TNode *child,
								int index,
								LSZ_SearchE *element)
{
	int indexTemp;
	//挪动元素并在elements[index]插入记录，index>=1。
	for(indexTemp = node->countKey; indexTemp != index; indexTemp--){
		(node->elements)[indexTemp] = (node->elements)[indexTemp - 1];
		(node->children)[indexTemp] = (node->children)[indexTemp - 1];
	}
	node->elements[index] = element; //插入记录
	node->children[index] = child; //新记录的右孩子需要改变。
	return 1;
}

//end of file
#endif

