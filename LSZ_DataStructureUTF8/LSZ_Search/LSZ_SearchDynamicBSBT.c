/*********************************************************************
 * File Name: LSZ_SearchDynamicBSBT.c
 * Author: linshangze
 * Mail: linshangze163@163.com
 * Created Time: 2013-10-30-10:16:31 PM
 ********************************************************************/

//于2013-12-02发表到csdn
//http://blog.csdn.net/lsze_

#ifndef _LSZ_SEARCHDYNAMIC_BSBT_C_
#define _LSZ_SEARCHDYNAMIC_BSBT_C_

//动态表查找，为了方便存储空间动态变化，
//对数据的存储使用内存动态申请函数。为了方便编程，
//查找中的树结构的根都会被一个不存放元素数据的头结点指向。

#include <malloc.h>
#include "./LSZ_Search.h"

//名称：二叉排序平衡树查找
//关键字：二叉平衡树，二叉排序树
//
//在二叉排序树的不断插入查找中，有可能出现极端情况，最坏情况例如：
//每棵树都只有右孩子。那样查找变成了顺序查找了。
//为了使排序树的深度最小，需要对每棵树的左右孩子进行平衡处理，成为
//二叉平衡树。
//二叉平衡树：它是一棵空树，或者，它的左孩子或右孩子不为空的话也为
//平衡二叉树。二叉平衡树的左孩子和右孩子的深度差绝对值不能超过1。
//如果将平衡因子设为左子树的深度减去右子树的深度，那么值有-1，0，1。

/**
 * 二叉排序平衡树查找
 *
 * tree：其左孩子指向树的根结点。
 * element：当往树中插入结点时，其指向空间存放传入值，
 *			其它情况指向空间用于记录查找到元素的值。
 * mode：仅查找，或带插入的查找，或带删除的查找。
 */
int LSZ_search_treeBinarySortedBalanced(LSZ_SearchBBTNode *tree,
										LSZ_SearchE *element,
										int mode)
{
	int depth = LSZ_SEARCH_HIGHERFALSE; //标记树的深度的变化
	LSZ_SearchBBTNode *treeTemp = tree->lChild; //取得根结点

	switch(mode){
		case LSZ_SEARCH_ONLY:
			while(treeTemp != NULL){
				if(treeTemp->element->key == element->key){
					*element = *(treeTemp->element);
					return 0; //查找成功
				}
				else{
					treeTemp = element->key < treeTemp->element->key
						? treeTemp->lChild : treeTemp->rChild;
				}
			}
			break;
		case LSZ_SEARCH_INSERT: //插入查找需要堆栈
			return LSZ_search_insertBSBT(&(tree->lChild), element, &depth); //这里没有初始化右子树
			break;
		case LSZ_SEARCH_DELETE: //删除查找需要堆栈
			return LSZ_search_deleteBSBT(&(tree->lChild), element, &depth);
			break;
	}
	return -1; //出错
}

//讨论一下插入结点时的平衡操作。
//插入结点可以分为两种：
//一插入根结点，二插入叶子结点。
//插入根结点较为简单，着重看插入叶子结点的情况。
//(1)设有树tree1：
//           a(2)                  b(0)
//          /    \                /    \_
//	    b(1)      ar      =>    bl      a(0)
//	   /    \                   ^      /    \_
//   bl      br                 c    br      ar
//   ^
//   c
//   或树tree1'：
//           a(2)              b(0)
//          /                 /    \_
//	    b(1)          =>    bl      a(0)
//	   /
//    ^
//    bl
//因为插入新结点而使树的平衡因子变为2，在这种情况下，需要作
//单向右旋平衡处理：
//b和a交换位置，a接管b的右孩子br，那样树就平衡了，并且树的结点被中
//序遍历的顺序不变。
//(2)设有树tree2：
//           a(-2)                        b(0)
//          /    \                       /    \_
//        al      b(-1)     =>        a(0)     br
//               /     \             /    \    ^
//             bl       br         al      bl  c
//                      ^
//                      c
//   或树tree2'：
//           a(-2)                        b(0)
//               \                       /    \_
//                b(-1)     =>        a(0)     br
//                     \_
//                      ^
//                      br
//因为插入新结点而使树的平衡因子变为-2，在这种情况下，需要作
//单向左旋平衡处理：
//b和a交换位置，a接管b的左孩子bl，那样树就平衡了，并且树的结点被中序
//遍历的顺序不变。因为不确定bl是否为NULL，所以a的平衡因子不确定。
//(3)设有树tree3：
//           a(2)                       a(2)               ____br(0)____
//          /    \                     /    \             /             \_
//     b(-1)      ar    =>        br(?)      ar   =>  b(?)               a(?)
//    /    \                     /     \             /    \             /    \_
//  bl      br(?)            b(?)    null\d        bl      c\null null\d      ar
//         /     \          /    \_
//   c\null       null\d  bl      c\null
//  或树tree3'：
//           a(2)                   a(2)             br(0)
//          /                      /                /     \_
//     b(-1)            =>    br(1)        =>   b(0)       a(0)
//         \                 /
//          ^            b(0)
//          br
//因为插入新结点或d结点而使树的平衡因子变为2，在这种情况下，需要作
//双向旋转（先左后右）平衡处理：先b和br作单向左旋，然后br和a作单向
//右旋，那样树就平衡了。并且树的结点被中序遍的顺序不变。
//(4)设有树tree4：
//           a(-2)               a(-2)                     ____bl(0)____
//          /    \              /    \                    /             \_
//        al      b(1)  =>    al      bl(?)   =>      a(?)               b(?)
//               /    \              /     \         /    \             /    \_
//          bl(?)      br      c\null       b(?)   al      c\null null\d      br
//            /  \                         /    \_
//      c\null    null\d             null\d      br
//   或树tree4'：
//           a(-2)               a(-2)                  bl(0)
//               \                   \                 /     \_
//                b(1)  =>            bl(-1)   =>  a(0)       b(0)
//               /                          \_
//              ^                           b(0)
//              bl
//因为插入新结点或d结点而使树的平衡因子变为-2，在这种情况下，需要作
//双向旋转（先右后左）平衡处理：先b和bl作单向右旋，然后br和a作单向
//左旋，那样树就平衡了。并且树的结点被中序遍的顺序不变。

/**
 * 二叉排序平衡树带插入的查找
 *
 * (*tree)：指向需要被查找的树的树根的指针的地址。
 *         注意(*tree)必须在原来的树结构中并指向树根。
 * element：指向空间存放要插入结点的值，或已存在结点的传出值。
 * isHigher：在执行插入函数后，返回树是否长高。
 */
int LSZ_search_insertBSBT(LSZ_SearchBBTNode **tree,
							LSZ_SearchE *element,
							int *isHigher)
{
	int result; //记录调用插入函数的返回值，判断是否执行了插入操作

	if((*tree) == NULL){ //空树
		if((*tree = (LSZ_SearchBBTNode*)malloc(
				sizeof(LSZ_SearchBBTNode))) == NULL){
			return -1;
		}
		if(((*tree)->element = (LSZ_SearchE*)malloc(
				sizeof(LSZ_SearchE))) == NULL){
			free(*tree);
			return -1;
		}
		(*tree)->lChild = (*tree)->rChild = NULL;
		*((*tree)->element) = *element;
		(*tree)->fBalance = LSZ_SEARCH_EQUALHIGH; //新插入结点的平衡因子
		*isHigher = LSZ_SEARCH_HIGHERTRUE; //树的高度发生变化
		return 1;
	}
	else{ //树非空
		if((*tree)->element->key == element->key){
			*element = *((*tree)->element);
			*isHigher = LSZ_SEARCH_HIGHERFALSE;
			return 0; //已存在结点，查找成功
		}
		if((*tree)->element->key > element->key){ //往左子树中插入
			if((result = LSZ_search_insertBSBT(&((*tree)->lChild), element, isHigher)) == -1){
				return -1; //插入失败
			}
			if(*isHigher == LSZ_SEARCH_HIGHERTRUE){ //左子树变高，需要修改平衡因子和判断整棵树是否长高
				switch((*tree)->fBalance){ //原来树根的平衡因子
					case LSZ_SEARCH_LEFTHIGH:
						LSZ_search_lBalanceBSBT(tree); //需要进行左平衡处理
						*isHigher = LSZ_SEARCH_HIGHERFALSE;
						break;
					case LSZ_SEARCH_EQUALHIGH:
						(*tree)->fBalance = LSZ_SEARCH_LEFTHIGH;
						*isHigher = LSZ_SEARCH_HIGHERTRUE;
						break;
					case LSZ_SEARCH_RIGHTHIGH:
						(*tree)->fBalance = LSZ_SEARCH_EQUALHIGH;
						*isHigher = LSZ_SEARCH_HIGHERFALSE;
						break;
				}
			}
		}
		else{ //往右子树插入
			if((result = LSZ_search_insertBSBT(&((*tree)->rChild), element, isHigher)) == -1){
				return -1; //插入失败
			}
			if(*isHigher == LSZ_SEARCH_HIGHERTRUE){ //右子树变高，需要修改平衡因子和判断整棵树是否长高
				switch((*tree)->fBalance){ //原来树根的平衡因子
					case LSZ_SEARCH_LEFTHIGH:
						(*tree)->fBalance = LSZ_SEARCH_EQUALHIGH;
						*isHigher = LSZ_SEARCH_HIGHERFALSE;
						break;
					case LSZ_SEARCH_EQUALHIGH:
						(*tree)->fBalance = LSZ_SEARCH_RIGHTHIGH;
						*isHigher = LSZ_SEARCH_HIGHERTRUE;
						break;
					case LSZ_SEARCH_RIGHTHIGH:
						LSZ_search_rBalanceBSBT(tree); //需要进行右平衡处理
						*isHigher = LSZ_SEARCH_HIGHERFALSE;
						break;
				}
			}
		}
		return result;
	}
}

//讨论一下删除结点时的平衡操作。
//因为要保持有序性，所以对二叉排序平衡树的结点的删除操作和对
//二叉排序树的删除操作类似，不过二叉排序平衡树还需要作平衡操作。
//
//对树进行中序遍历，就可以得到结点的从小到大的排序，
//如果被删结点只有一棵子树，直接用子树取代被删除结点即可。
//如果被删结点有两棵子树，那么可以考虑用其前驱或后继来替代该结点。
//在二叉排序树中假设有这么一棵树：
//                         a
//                       /   \_
//                     b       c
//                   /   \_
//                 d       e
//               /   \   /   \_
//              f     g h     i
//                   /   \_
//                  j     k
//但在二叉排序平衡树中不会出现这样的情况的，因为上面的树不平衡。
//现在选定用前驱代替删除结点，所以现在重新假设有树：
//                           ___a(?)___
//                          /          \_
//                   ___b(?)_           c(?)/null
//                  /        \            ^
//         d(?)/null          e(?)/null   ...
//        /         \           ^
//  f/null      g(?)/null  ...
//                  /
//            j/null
//在上图中假设c子树和e子树的高度能使a树平衡。
//这样就可以分情况分析b点的删除对树平衡的影响了。
//现在要删除的结点是b，对该树的中序遍历顺序为fdjgb...a...。
//(1)如果b只有左孩子
//   很明显，只要将b的左孩子直接连接到b的前驱，再将b结点删除。
//   那么它此时的a的平衡因子就会减1，a树的高度也发生了变化，
//   此时要回溯到最小不平衡树，进行平衡调整，因为调整可能导致
//   最小不平衡树的父节点不平衡，所以要继续回溯调整，直到根结
//   点。增加高度的旋转操作和降低高度的旋转操作对称。单左旋和
//   右左旋刚好为对称操作。
//(2)如果b只有右孩子
//   同理，只要将b的右孩子直接连接到b的前驱，在将b结点删除。
//   a树的高度发生变化，然后进行相应的旋转操作。
//(3)如果b的左右孩子均不为空
//   同BST树的删除操作，删除后的树为：
//                           ___a(?)___
//                          /          \_
//                   ___g(?)_           c(?)/null
//                  /        \            ^
//         d(?)/null          e(?)/null   ...
//        /         \           ^
//  f/null           j/null     ...
//  或当g为空时：
//                           ___a(?)___
//                          /          \_
//                   ___d(?)_           c(?)/null
//                  /        \            ^
//            f/null          e(?)/null   ...
//                              ^
//                              ...
//  由以上看到，发生高度变化的树有d树，g树，a树。需要进行调整。
//  平衡因子的变化：
//  如果b的左孩子或右孩子为空，回溯调整a。
//  如果g为空，删除b后，则d的平衡因子不变，回溯调整a。
//  如果g不为空，删除b后，d的平衡因子加1，回溯调整g和a。
//      g的平衡因子取b原来的平衡因子。
//      因此树的平衡调整从d结点开始，到g，再到a。也就是说，
//      是在替换删除结点的结点开始平衡调整的。为了代码方便，
//      这种情况就只是用替换结点的值对删除结点的值进行替换，
//      实际删除的结点是替换点（便于编程实现回溯）。但平衡
//      因子不能被替换。
//
//  编程错误并改正：
//  一，因为用函数调用栈实现回溯，当删除结点为根结点时，没有修
//      改平衡因子的回溯，要修改其平衡因子。
//  二，二叉排序树查找没有考虑平衡因子操作，所以在重用其代码时
//      要注意结点为空的情况，此时不用修改平衡因子。

/**
 * 二叉排序平衡树带删除的查找
 *
 * (*tree)：指向需要被查找的树的树根的指针的地址。
 *         注意(*tree)必须在原来的树结构中并指向树根。
 * element：指向空间存放要删除结点的值。
 * isHigher：在执行插入函数后，返回树是否长高。
 */
int LSZ_search_deleteBSBT(LSZ_SearchBBTNode **tree,
							LSZ_SearchE *element,
							int *isLower)
{
	int result; //记录调用删除函数的返回值，判断是否执行了删除操作
	LSZ_SearchBBTNode *nodeDelete, **nodeFind;
	LSZ_SearchE *elementTemp; //用于替换结点和删除结点的交换

	if((*tree) == NULL){ //空树
		*isLower = LSZ_SEARCH_LOWERFALSE; //树的高度未发生变化
		return 0;
	}
	else{ //树非空
		if((*tree)->element->key == element->key){ //找到删除结点
			nodeDelete = *tree;
			*element = *((*tree)->element);
			//下面的删除要按照二叉排序树的删除方法
			if(nodeDelete->lChild == NULL || nodeDelete->rChild == NULL){
				if(nodeDelete->lChild == NULL){
					*tree = nodeDelete->rChild;
					if(*tree != NULL){ //相当于少一右孩子，防止删除根结点平衡因子不更新出错
						(*tree)->fBalance += LSZ_SEARCH_BALANCEDIFF;
					} //因为要操作平衡因子，防止两结点都为空的情况
				}
				else{ //删除结点无右孩子
					*tree = nodeDelete->lChild;
					if(*tree != NULL){ //相当于少一左孩子，防止删除根结点平衡因子不更新出错
						(*tree)->fBalance -= LSZ_SEARCH_BALANCEDIFF;
					} //因为要操作平衡因子，防止两结点都为空的情况
				}
				*isLower = LSZ_SEARCH_LOWERTRUE; //高度变化
				LSZ_SEARCH_DESTROYNODE(nodeDelete);
				return 1; //删除成功
			}
			else{ //删除结点同时有左右孩子，注意平衡因子的调整
				nodeFind = &(nodeDelete->lChild);
				if((*nodeFind)->rChild == NULL){ //删除结点的后继的特殊情况
					*tree = (*nodeFind);
					(*tree)->fBalance -= 1; //相当于少一左孩子，防止删除根结点平衡因子出错
					(*tree)->rChild = nodeDelete->rChild;
					LSZ_SEARCH_DESTROYNODE(nodeDelete);
					*isLower = LSZ_SEARCH_LOWERTRUE; //高度变化
					return 1;
				}
				else{ //删除结点后继的一般情况
					while((*nodeFind)->rChild != NULL){
						(*nodeFind) = (*nodeFind)->rChild;
					}
					//删除结点的值赋予替换结点的值，但不包括平衡因子
					(*nodeFind)->fBalance = nodeDelete->fBalance;
					elementTemp = nodeDelete->element; //交换元素
					nodeDelete->element = (*nodeFind)->element;
					(*nodeFind)->element = elementTemp;
					goto ToDelete; //为了利用函数递归的堆栈，强制转跳，最终要删除的结点为替换结点
				} //一般情况
			} //删除结点同时有左右孩子
		} //找到删除结点
		if((*tree)->element->key > element->key){ //往左子树中删除
ToDelete:	result = LSZ_search_deleteBSBT(&((*tree)->lChild), element, isLower);
			if(*isLower == LSZ_SEARCH_LOWERTRUE){ //左子树变矮，需要修改平衡因子和判断整棵树是否变矮
				switch((*tree)->fBalance){ //原来树根的平衡因子
					case LSZ_SEARCH_LEFTHIGH:
						(*tree)->fBalance = LSZ_SEARCH_EQUALHIGH;
						*isLower = LSZ_SEARCH_LOWERTRUE;
						break;
					case LSZ_SEARCH_EQUALHIGH:
						(*tree)->fBalance = LSZ_SEARCH_RIGHTHIGH;
						*isLower = LSZ_SEARCH_LOWERFALSE;
						break;
					case LSZ_SEARCH_RIGHTHIGH:
						LSZ_search_rBalanceBSBT(tree); //需要进行右平衡处理
						*isLower = LSZ_SEARCH_LOWERTRUE;
						break;
				}
			}
		} //往左子树删除
		else{ //往右子树删除
			result = LSZ_search_deleteBSBT(&((*tree)->rChild), element, isLower);
			if(*isLower == LSZ_SEARCH_LOWERTRUE){ //右子树变矮，需要修改平衡因子和判断整棵树是否变矮
				switch((*tree)->fBalance){ //原来树根的平衡因子
					case LSZ_SEARCH_LEFTHIGH:
						LSZ_search_lBalanceBSBT(tree); //需要进行左平衡处理
						*isLower = LSZ_SEARCH_LOWERTRUE;
						break;
					case LSZ_SEARCH_EQUALHIGH:
						(*tree)->fBalance = LSZ_SEARCH_LEFTHIGH;
						*isLower = LSZ_SEARCH_LOWERFALSE;
						break;
					case LSZ_SEARCH_RIGHTHIGH:
						(*tree)->fBalance = LSZ_SEARCH_EQUALHIGH;
						*isLower = LSZ_SEARCH_LOWERTRUE;
						break;
				}
			}
		} //往右子树删除
		return result;
	} //树非空
}

/**
 * 左子树（长高）导致失衡时的左平衡调整函数
 *
 * (*tree)：指向最小的失衡树的树根。
 *         注意(*tree)必须在原来的树结构中。
 */
void LSZ_search_lBalanceBSBT(LSZ_SearchBBTNode **tree)
{
 	LSZ_SearchBBTNode **lChild;

 	lChild = &((*tree)->lChild); //最小非平衡树的左孩子
	switch((*lChild)->fBalance){ //检查左子树，确定单向旋转还是双旋转
		case LSZ_SEARCH_LEFTHIGH: //新结点插入在左左孩子上，只需单向右旋
			(*tree)->fBalance = (*lChild)->fBalance = LSZ_SEARCH_EQUALHIGH;
			LSZ_search_rRotateBSBT(tree); //经过旋转，(*tree)已改变
			break;
		case LSZ_SEARCH_RIGHTHIGH: //新结点插入在左右孩子上，需要进行双旋转
			switch((*lChild)->rChild->fBalance){ //需要判断和调整平衡因子
				case LSZ_SEARCH_LEFTHIGH: //新结点插入在左右孩子的左孩子上
					(*tree)->fBalance = LSZ_SEARCH_RIGHTHIGH;
					(*lChild)->fBalance = LSZ_SEARCH_EQUALHIGH;
					break;
				case LSZ_SEARCH_EQUALHIGH:
					(*tree)->fBalance = (*lChild)->fBalance = LSZ_SEARCH_EQUALHIGH;
					break;
				case LSZ_SEARCH_RIGHTHIGH:
					(*tree)->fBalance = LSZ_SEARCH_EQUALHIGH;
					(*lChild)->fBalance = LSZ_SEARCH_LEFTHIGH;
					break;
			}
			(*lChild)->rChild->fBalance = LSZ_SEARCH_EQUALHIGH;
			LSZ_search_lRotateBSBT(lChild);
			LSZ_search_rRotateBSBT(tree);
			break;
	}
}

/**
 * 右子树（长高）导致失衡时的左平衡调整函数
 *
 * (*tree)：指向最小的失衡树的树根。
 *         注意(*tree)必须在原来的树结构中。
 */
void LSZ_search_rBalanceBSBT(LSZ_SearchBBTNode **tree)
{
 	LSZ_SearchBBTNode **rChild;

 	rChild = &((*tree)->rChild); //最小非平衡树的右孩子
	switch((*rChild)->fBalance){ //检查左子树，确定单向旋转还是双旋转
		case LSZ_SEARCH_LEFTHIGH: //新结点插入在右左孩子上，需要进行双旋转
			switch((*rChild)->lChild->fBalance){ //需要判断和调整平衡因子
				case LSZ_SEARCH_LEFTHIGH:
					(*tree)->fBalance = LSZ_SEARCH_EQUALHIGH;
					(*rChild)->fBalance = LSZ_SEARCH_RIGHTHIGH;
					break;
				case LSZ_SEARCH_EQUALHIGH:
					(*tree)->fBalance = (*rChild)->fBalance = LSZ_SEARCH_EQUALHIGH;
					break;
				case LSZ_SEARCH_RIGHTHIGH:
					(*tree)->fBalance = LSZ_SEARCH_LEFTHIGH;
					(*rChild)->fBalance = LSZ_SEARCH_EQUALHIGH;
					break;
			}
			(*rChild)->lChild->fBalance = LSZ_SEARCH_EQUALHIGH;
			LSZ_search_rRotateBSBT(rChild);
			LSZ_search_lRotateBSBT(tree);
			break;
		case LSZ_SEARCH_RIGHTHIGH: //新结点插入在右右孩子上，只需单向左旋
			(*tree)->fBalance = (*rChild)->fBalance = LSZ_SEARCH_EQUALHIGH;
			LSZ_search_lRotateBSBT(tree); //经过旋转，(*tree)已改变
			break;
	}
}

/**
 * 单向左旋平衡操作函数
 *
 * (*tree)：指向需要旋转的树的树根。
 *         注意(*tree)必须在原来的树结构中并指向树根。
 */
void LSZ_search_lRotateBSBT(LSZ_SearchBBTNode **tree)
{
	LSZ_SearchBBTNode *axesNode; //旋转轴结点

	axesNode = (*tree)->rChild; //取得旋转轴结点
	(*tree)->rChild = axesNode->lChild; //旋转结点接管轴结点的左孩子
	axesNode->lChild = *tree; //旋转轴结点指向原根结点
	*tree = axesNode; //旋转轴作为新根结点
}

/**
 * 单向右旋平衡操作函数
 *
 * (*tree)：指向需要旋转的树的树根。
 *         注意(*tree)必须在原来的树结构中并指向树根。
 */
void LSZ_search_rRotateBSBT(LSZ_SearchBBTNode **tree)
{
	LSZ_SearchBBTNode *axesNode; //旋转轴结点

	axesNode = (*tree)->lChild; //取得旋转轴结点
	(*tree)->lChild = axesNode->rChild; //旋转结点接管轴结点的右孩子
	axesNode->rChild = *tree; //旋转轴结点指向原根结点
	*tree = axesNode; //旋转轴作为新根结点
}

/**
 * 销毁二叉排序平衡树
 *
 * tree：指向树的头结点的指针，树的销毁用后续遍历。
 *      这里用递归实现后根遍历。
 */
void LSZ_search_destroyBSBT(LSZ_SearchBBTNode *tree)
{
	if(tree->lChild != NULL)
		LSZ_search_doDestroyBSBT(tree->lChild);
	tree->lChild = NULL; //重新设置空指向
}
void LSZ_search_doDestroyBSBT(LSZ_SearchBBTNode *tree)
{
	if(tree->lChild != NULL){ //先销毁左子树
		LSZ_search_doDestroyBSBT(tree->lChild);
	}
	if(tree->rChild != NULL){ //再销毁右子树
		LSZ_search_doDestroyBSBT(tree->rChild);
	}
	//最后销毁根结点
	LSZ_SEARCH_DESTROYNODE(tree);
}

//end of file
#endif

