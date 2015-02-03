/*********************************************************************
 * File Name: LSZ_SearchDynamicBST.c
 * Author: linshangze
 * Mail: linshangze163@163.com
 * Created Time: 2013-10-30-10:16:31 PM
 ********************************************************************/

//于2013-11-20发表到csdn
//http://blog.csdn.net/lsze_

#ifndef _LSZ_SEARCHDYNAMIC_BST_C_
#define _LSZ_SEARCHDYNAMIC_BST_C_

//动态表查找，为了方便存储空间动态变化，
//对数据的存储使用内存动态申请函数。为了方便编程，
//查找中的树结构的根都会被一个不存放元素数据的头结点指向。

#include <malloc.h>
#include "LSZ_Search.h"

//名称：二叉排序树查找
//关键字：动态查找，二叉排序树
//
//二叉排序树的性质：树为空树；树不为空树，如果其左子树不为空，则左
//子树上所有的结点的值均小于它的根结点，如果其右子树不为空，则右子
//树上所有的结点均大于它的根结点的值；其左右子树均为二叉排序树。
//对树的查找类似于二分法。从树的根结点开始，用要查找的键值和树的
//结点元素键值比较，如果查找的键值小于树结点元素的键值，那么往
//结点的左子树查找，否则往右子树查找，用同样的方法在子树中查找。

/**
 * 二叉排序树查找
 *
 * 执行成功返回值>=0：
 * 原树中查找成功，有插入操作或删除操作，返回1，
 * 原树中查找成功，无插入操作，返回0，
 * 原树中查找失败，无删除操作，返回0，
 * 出错返回-1。
 *
 * tree：其左孩子指向树的根结点。
 * element：当往树中插入结点时，其指向空间存放传入值，
 *			其它情况指向空间用于记录查找到元素的值。
 * mode：仅查找，或带插入的查找，或带删除的查找。
 */
int LSZ_search_treeBinarySorted(LSZ_SearchBTNode *tree,
								LSZ_SearchE *element,
								int mode)
{
	LSZ_SearchBTNode *header = tree, *nodePrevious = tree;
	int where; //插入根结点或者是左孩子或者是右孩子

	tree = tree->lChild; //获取根结点
	while(tree != NULL){
		if(tree->element->key == element->key){ //查找成功
			*element = *(tree->element);
			if(mode != LSZ_SEARCH_DELETE){
				return 0; //查找成功后，插入或仅查，到此返回0
			}
			break;
		}
		else{ //继续查找
			nodePrevious = tree;
			tree = element->key < tree->element->key
				? tree->lChild : tree->rChild;
		}
	}
	if(tree == NULL){
		if(mode == LSZ_SEARCH_ONLY){
			return -1; //查找失败
		}
		if(mode == LSZ_SEARCH_DELETE){
			return 0; //查找失败，不用删除
		}
	}
	//至此，下面代码要么查找成功做删除请求，要么查找失败做插入
	if(nodePrevious != header){ //插入左孩子或右孩子
		where = nodePrevious->element->key > element->key
			? LSZ_SEARCH_LCHILD : LSZ_SEARCH_RCHILD;
	}
	else{ //插入树的根结点
		where = LSZ_SEARCH_PARENT;
	}
	if(mode == LSZ_SEARCH_INSERT){
		return LSZ_search_insertBST(nodePrevious, element, where);
	}
	return LSZ_search_deleteBST(nodePrevious, tree, where);
}

//插入
//在查找的过程中遇到空树时，插入一新结点替代空树就可以。

/**
 * 对二叉排序树进行结点插入
 *
 * nodePrevious：指向插入结点的前驱结点。
 * element：指向空间存放要插入结点的值，或已存在结点的传出值。
 * where：插入位置，根，左孩子，右孩子。
 */
int LSZ_search_insertBST(LSZ_SearchBTNode *nodePrevious,
							LSZ_SearchE *element,
							int where)
{
	LSZ_SearchBTNode *treeNew;

	if((treeNew = (LSZ_SearchBTNode*)malloc(
			sizeof(LSZ_SearchBTNode))) == NULL){
		return -1;
	} //申请树结点空间
	if((treeNew->element = (LSZ_SearchE*)malloc(
			sizeof(LSZ_SearchE))) == NULL){
		free(treeNew); //记得释放树结点
		return -1;
	} //申请数据空间
	*(treeNew->element) = *element; //设置结点值
	treeNew->lChild = treeNew->rChild = NULL; //叶子结点
	if(where == LSZ_SEARCH_PARENT){ //作为根结点
		nodePrevious->lChild = nodePrevious->rChild = treeNew;
	}
	else{ //作为孩子结点
		if(where == LSZ_SEARCH_LCHILD){
			nodePrevious->lChild = treeNew;
		}
		else{
			nodePrevious->rChild = treeNew;
		}
	}
	return 1; //成功插入操作
}

//删除
//对树进行中序遍历，就可以得到结点的从小到大的排序，
//如果被删结点只有一棵子树，直接用子树取代被删除结点即可。
//如果被删结点有两棵子树，那么可以考虑用其前驱或后继来替代该结点。
//假设有这么一棵树：
//                    a
//                  /   \
//                b       c
//              /   \
//            d       e
//          /   \   /   \
//         f     g h     i
//               /  \
//              j    k
//现在要删除的结点是b，对该树的中序遍历顺序为fdjgbhkeiac，
//b的前驱为g，后继为h。g不可能有右子树，因为那样的话b的前驱就在g
//的右子树里了，同理h不可能有左子树。那样我们操作的思路就清晰了。
//如果用b的前驱结点g取代b时，g的父母结点d要接管g的左孩子j，
//如果用b的后继结点h取代b时，h的父母结点e就要接管h的右孩子k。
//因为树是带空的头结点的，所以为了方便编程，采用前驱取代删除结点
//的操作。
//这时又要思考一下g点的父母d的合法性了。如果d没有右孩子，如下：
//                    a
//                  /   \
//                b       c
//              /   \
//            d       e
//          /
//         f
//那么d便是b的前驱，但b同时又是d的父母结点，这就要特殊处理了。
//非特殊情况下，g要接管b的两个孩子。
//为了方便讨论，下面的g或d结点被叫做替换结点，b为删除结点。

/**
 * 对二叉排序树进行删除
 *
 * nodePrevious：指向删除结点的前驱结点。
 * nodeDelete：指向要删除的结点。
 * where：删除的结点的位置，根，左孩子，右孩子。
 */
int LSZ_search_deleteBST(LSZ_SearchBTNode *nodePrevious,
							LSZ_SearchBTNode *nodeDelete,
							int where)
{
	LSZ_SearchBTNode **nodeLink, *nodeFind;

	nodeLink = where == LSZ_SEARCH_LCHILD ?
		&(nodePrevious->lChild) : &(nodePrevious->lChild); //取指针变量的地址
	if(nodeDelete->lChild == NULL){ //左子树空，只需重连接其右子树
		*nodeLink = nodeDelete->rChild;
	}
	else if(nodeDelete->rChild == NULL){ //右子树空，只需重连接其左子树
		*nodeLink = nodeDelete->lChild;
	}
	else{ //左右子树均不为空
		nodeFind = nodeDelete->lChild; //被删结点的左孩子
		if(nodeFind->rChild == NULL){ //这是特殊情况，被删结点的驱刚好为其左子树的根
			*nodeLink = nodeFind; //取代结点替换被删除结点
		}
		else{
			while(nodeFind->rChild != NULL){
				if(nodeFind->rChild->rChild == NULL){
					break; //为了方便记录前驱和节省空间，需要预判一下
				}
				nodeFind = nodeFind->rChild;
			}
			*nodeLink = nodeFind->rChild; //取代结点替换被删除结点nodeFind->rChild = (*nodeLink)->lChild; //取代结点的左孩子被接管

			(*nodeLink)->lChild = nodeDelete->lChild; //取代结点接管删除结点的左孩子
		}
		(*nodeLink)->rChild = nodeDelete->rChild; //取代结点接管删除结点的右孩子
	}
	//释放要删除结点的空间
	LSZ_SEARCH_DESTROYNODE(nodeDelete);
	return 1;
}

/**
 * 销毁二叉排序树
 *
 * tree：指向树的头结点的指针，树的销毁用后续遍历。
 *      这里用递归实现后根遍历。
 */
void LSZ_search_destroyBST(LSZ_SearchBTNode *tree)
{
	if(tree->lChild != NULL) //防止多次销毁错误
		LSZ_search_doDestroyBST(tree->lChild);
	tree->lChild = NULL;
}
void LSZ_search_doDestroyBST(LSZ_SearchBTNode *tree)
{
	if(tree->lChild != NULL){ //先销毁左子树
		LSZ_search_doDestroyBST(tree->lChild);
	}
	if(tree->rChild != NULL){ //再销毁右子树
		LSZ_search_doDestroyBST(tree->rChild);
	}
	//最后销毁根结点
	LSZ_SEARCH_DESTROYNODE(tree);
}

//end of file
#endif

