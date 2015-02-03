/********************************************************************
 *File Name: LSZ_TreeLBinary.c
 *Author: Linshangze//林上泽
 *Mail: linshangze163@163.com
 *Created Time: 2013-05-21
 *Updated Time: 2015-01-22
 *******************************************************************/

/********************************************************************
 *source file of LSZ_TreeLBinary data structure
 *LSZ_TreeLBinary源文件
 *******************************************************************/

#ifndef _LSZ_TREELBINARY_C_
#define _LSZ_TREELBINARY_C_

#ifndef _LSZ_CHECK_ERROR_
#define _LSZ_CHECK_ERROR_
#endif

#include <malloc.h>
#include "LSZ_TreeLBinary.h"

#define _LSZ_FUN_TREELB_NODE(node) \
	(((node)=(LSZ_TreeLBNode*)malloc(sizeof(LSZ_TreeLBNode))) != NULL)

/**
 * to destroy a binary linked node and its children
 * as well as the data save in it
 * 销毁一二叉链表结构的一结点及它的孩子
 * 还有销毁存储在里边的数据
 */
static int LSZ_TreeLB_del_(LSZ_TreeLBNode *delNode);

/**
 * to initialize a binary linked tree strcuture
 * 初始化一二叉链结构的二叉树
 */
int LSZ_TreeLB_init(LSZ_TreeLBCtl *control)
{
#ifdef _LSZ_CHECK_ERROR_
	if(control == NULL)
		return _LSZ_ERRISNULLPOINTER_;
#endif
	//the tree is empty and hasn't been traversed
	control->boot = control->curNode =  NULL;
	control->count = 0; //树中结点个数为0
	control->next = INITIAL;//the initial direction of traversing
	control->way = STOP;//no traversal
	LSZ_Stack_init(&(control->traversing)); //initialize a stack
	return 0;
}

/**
 * 销毁一二叉树和它动态申请的内存
 */
int LSZ_TreeLB_dest(LSZ_TreeLBCtl *control)
{
#ifdef _LSZ_CHECK_ERROR_
	if(control == NULL)
		return _LSZ_ERRISNULLPOINTER_;
#endif
	if(control->boot != NULL)
		LSZ_TreeLB_del_(control->boot);
	control->boot = control->curNode =  NULL;
	control->count = 0; //树中结点个数为0
	control->next = INITIAL;//the initial direction of traversing
	control->way = STOP;//no traversal
	LSZ_Stack_dest(&(control->traversing)); //initialize a stack
	return 0;
}

/**
 * to chose a way to begin to traverse a tree
 * and it should match with 'end_traverse_LSZ_TreeLBCtl()'
 * 以某种方式开始遍历树
 */
//void LSZ_TreeLB_beginGo(LSZ_TreeLBCtl *control,
//							LSZ_TreeLBGo way)
//{
//	control->curNode = NULL;//there hasn't current node accessed
//	control->traversal = way;//chose way to traverse
//	control->next = INITIAL;//the first time to do traversal
//}

/**
 * to end traversing a tree
 * it must be used after 'begin_traverse_LSZ_TreeLBCtl()'
 * 结束一树的遍历操作,与上一宏成对使用
 */
//void LSZ_TreeLB_endGo(struct tree_b_lk_l *control)
//{
//	control->traversal = STOP;//this flag is used in several operations
//	LSZ_Stack_clear2(&(control)->traversing);//destroy the stack
//}

/**
 * when preorder traversing,
 * the node accessed should be pushed on the stack and go left
 * and the node popped from the stack should be judge its right child.
 * the part circulation mainly in the right, is the 'pop' operation.
 * 先序遍历时,被访问的结点就进栈,然后左走.
 * 退栈时,只判断其右孩子,局部循环操作主要在右,即退栈操作
 * 
 * 1)when preorder traversing,
 * the node accessed for the first time will be pushed on the stack,
 * the next node is its left child. it says that when
 * backtrack just jugde the node's right child.
 * 1)先序遍历时,结点首次被访问即进栈,下个访问其左孩子.
 * 这说明当退栈只需判断其右孩子
 * 
 * 2)when preorder traversing and the next left child is empty,
 * pop node back tracking in the stack
 * and judge its right child(just the currunt node's right child),
 * repeat backtracking till the right child is not empty.
 * the next left child or the node popped are dealed with oparation 1.
 * when the stack be empty, finish traversing.
 * 2)先序遍历时,若左孩子为空,
 * 则退栈判断退栈结点的右孩子(即该结点的右孩子),
 * 对该结点的左孩子或退栈所得的其右孩子执行1操作
 * 若为空则继续退栈.若空栈则结束.
 *
 * make a next step after the 'curNode'
 * as preorder traversing a binary tree
 * and the 'curNode' will be changed
 * 以先序遍历的方式踏出'curNode'的下一步
 */
int LSZ_TreeLB_preorder(LSZ_TreeLBCtl *control)
{
	LSZ_TreeLBNode *temp;//temporary node pointer
	LSZ_MT data;

#ifdef _LSZ_CHECK_ERROR_
	if(control->way != PREORDER) //error way to traversal(错误访问)
		return _LSZ_ERRTREELBINARYTRAVERSAL_;
	if(control == NULL || control->boot == NULL) //空指针或空树
		return _LSZ_ERRISNULLPOINTER_;
#endif
	//the first time to traverse(初次先序遍历树)
	LSZ_MT_init(&data);
	if(control->next == INITIAL){
		temp = control->boot;
		control->curNode = temp; //accesse the boot node
		LSZ_MT_wt(&data, &temp);
		LSZ_Stack_push(&(control->traversing), &data);
		control->next = LEFT;//left child should be accessed first
		return 0;
	}
	if(control->next == LEFT){//the current node's left child node
		temp = control->curNode->lchild;
		if(temp != NULL){
			LSZ_MT_wt(&data, &temp);
			LSZ_Stack_push(&(control->traversing), &data);
			control->curNode = temp;
			control->next = LEFT;
			return 0;
		}
		control->next = RIGHT;
	}
	if(control->next == RIGHT){//the current node's right child node
		while(1){
			if(LSZ_Stack_pop(&(control->traversing), &data) != 0)
				return 1;//finish
			LSZ_MT_rd(&temp, &data);
			if(temp->rchild != NULL)
				break;
		}
		temp = control->curNode = temp->rchild;
		LSZ_MT_wt(&data, &temp);
		LSZ_Stack_push(&(control->traversing), &data);
		control->next = LEFT;
	}
	return 0;
}

/**
 * when access a node should judge its left child first
 * whether should its left child be accessed.
 * if not access itself.
 * the node popped from the stack should be judge its self
 * and its right child.
 * the part circulation mainly in the right, is the 'push' operation.
 * 中序遍历时,要访问的结点要先访问其左孩子直至其为空.
 * 退栈时,要判断退栈结点自身及其右孩子,局部循环操作主要在右,即进栈操作
 * 
 * 1)when inorder traversing,
 * the node accessed judge its left child whether can it be accessed.
 * if yes push it on the stack and go left.
 * repeat this operation till the left child can't be accessed,
 * than access this node and the next node is it right child.
 * it says that when backtrack
 * should access the node popped from the stack
 * and than jugde the node's right child whether can be accessed.
 * 1)中序遍历时,被访问的结点应先判断其左孩子是否可访问,
 * 若可以该结点进栈并且左走下去,重复直至左孩子不可访问,然后访问该结点,
 * 下个再判断其右孩子.这说明当退栈的结点要访问其自身再判断其右孩子
 * 
 * 2)when inorder traversing and access the node's right child,
 * if right can be accessed repeat the operation 1,
 * or pop node from the stack and access it,
 * the next node is the popped node's right child.
 * 2)中序遍历时,若要访问的右孩子为空,则退栈访问退栈结点,
 * 然后再是其右孩子.重复.若右孩子不为空则执行1操作,栈为空则结束
 * 
 * make a next step after the 'curNode'
 * as inorder traversing a binary tree
 * and the 'curNode' will be changed
 * 以中序遍历的方式踏出'curNode'的下一步
 */
int LSZ_TreeLB_inorder(LSZ_TreeLBCtl *control)
{
	LSZ_TreeLBNode *temp;
	LSZ_MT data;

#ifdef _LSZ_CHECK_ERROR_
	if(control->way != INORDER) //error way to traversal
		return _LSZ_ERRTREELBINARYTRAVERSAL_;
	if(control == NULL || control->boot == NULL)
		return _LSZ_ERRISNULLPOINTER_;//empty tree
#endif
	LSZ_MT_init(&data);
	//the first time to traverse(初次中序遍历树)
	if(control->next == INITIAL){
		temp = control->boot;
		control->next = LEFT;//left child should be accessed first
	}
	if(control->next == RIGHT){//the current node's right child node
		if(control->curNode == NULL)
			return -1;//this judgement only for 'LSZ_TreeLB_delete()'
		if((temp = control->curNode->rchild) == NULL){//backtrack
			if(LSZ_Stack_pop(&(control->traversing), &data) != 0)
				return 1;//finish
			LSZ_MT_rd(&temp, &data);
			control->curNode = temp;
			control->next = RIGHT;
			return 0;
		}
		control->next = LEFT;//right child should be accessed first
	}
	if(control->next == LEFT){//the current node's left child node
		while(temp->lchild != NULL){
			LSZ_MT_wt(&data, &temp);
			LSZ_Stack_push(&(control->traversing), &data);
			temp = temp->lchild;
		}
		control->curNode = temp;//this node should be accessed
		control->next = RIGHT;//the next node is its right child
	}
	return 0;
}

/**
 * when postorder traversing and access a node,
 * judge its left child as well as its right child first
 * whether can both they be accessed, if not access it.
 * node popped from the stack should be judge whether it is the
 * parents of the previous node accessed, if yes, access it
 * or postorder traverse it. 
 * the part circulation mainly in find the leaf node.
 * 后序遍历时,要访问的结点前要先判断其孩子是否都为空.
 * 退栈时,要判断退栈结点是否上一结点的父母.
 * 局部循环操作主要查找叶子结点,即进栈操作
 * 
 * 1/when postorder traversing as the node is accessed,
 * judge its left child and its right child
 * whether one or both of them can be accessed, if yes
 * push it and its right child that can be accessed on the stack.
 * and if the left child can be accessed go left, else go right.
 * if not, access this node,
 * and the next node should be accessed is on the stack.
 * 1)后序遍历时,访问的结点前应先判断其孩子是否都为空,
 * 若是则访问该结点,其下个结点在栈上.
 * 若否,则该结点进栈并其右孩子不为空时也要进栈,然后优先向左走下去.
 * 这说明当退栈的结点只要是上一次访问结点的父母就只访问自身,
 * 否则它是上一结点的右兄弟
 * 
 * 2)when postorder traversing,
 * before access the node popped from the stack,
 * if it is the parents of the previously accessed node,
 * access the parents node, and the next node is on the stack.
 * if not deal with the operation 1.
 * when the stack is empty, finish traversing.
 * 2)后序遍历时,在要访问出栈的结点前,
 * 先判断其是否上一次访问结点的父母结点,
 * 若是则对其右孩子执行1操作.空栈则结束遍历.
 * 
 * make a next step after the 'curNode'
 * as postorder traversing a binary tree
 * and the 'curNode' will be changed
 * 以后序遍历的方式踏出'curNode'的下一步
 */
int LSZ_TreeLB_postorder(LSZ_TreeLBCtl *control)
{
	LSZ_TreeLBNode *temp;
	LSZ_MT data;

#ifdef _LSZ_CHECK_ERROR_
	if(control->way != POSTORDER)
		return _LSZ_ERRTREELBINARYTRAVERSAL_;//error way to traversal
	if(control == NULL || control->boot == NULL)
		return -1;//empty tree
#endif
	LSZ_MT_init(&data);
	//the first time to traverse(初次后序遍历树)
	if(control->next == INITIAL){
		temp = control->boot;
		control->next = LEFT;//its left child should be accessed first
	}
	//the current node's right brother node or its parent node
	if(control->next == RIGHT){
		if(LSZ_Stack_pop(&(control->traversing), &data) != 0)
				return 1;//finish backtracking
		LSZ_MT_rd(&temp, &data);
		if(temp->lchild == control->curNode
			|| temp->rchild == control->curNode){
			control->curNode = temp;
			control->next = RIGHT;
			return 0;//is the 'curNode''s parents node
		}//the brother node should judge it's left child
		control->next = LEFT;
	}
	if(control->next == LEFT){//the current node's left child
		//find the leaf node
		while(temp->lchild != NULL || temp->rchild != NULL){
			//this node pushed as a parents node
			LSZ_MT_wt(&data, &temp);
			LSZ_Stack_push(&(control->traversing), &data);
			if(temp->lchild != NULL){//will go left
				if(temp->rchild != NULL){
					LSZ_MT_wt(&data, &(temp->rchild));
					LSZ_Stack_push(&(control->traversing), &data);
				}
				temp = temp->lchild;
			}
			else
				temp = temp->rchild;
		}
		control->curNode = temp;//this node should be accessed
		//the next node is its right child or its right brother
		control->next = RIGHT;
	}
	return 0;
}

/**
 * to find a child node's parents
 * and return its parent's node
 * 返回一结点的父母结点
 */
LSZ_TreeLBNode *LSZ_TreeLB_parent(LSZ_TreeLBCtl *control,
									LSZ_TreeLBNode *child)
{
	int flag = 0;
	LSZ_TreeLBNode *tempParent;
	//because the traversal will change the current node
	LSZ_TreeLBCtl tempTree;

#ifdef _LSZ_CHECK_ERROR_
	//the NULL child's parents is ambiguous
	if(control == NULL || child == NULL)
		return NULL; //_LSZ_ERRISNULLPOINTER_;
	if(control->boot == NULL){//is empty tree
		return NULL;
	}
#endif
	LSZ_TreeLB_init(&tempTree);
	tempTree.boot = control->boot;
	//you can't return before ending to traverse
	LSZ_TreeLB_beginGo(&tempTree, INORDER);
		while(LSZ_TreeLB_inorder(&tempTree) == 0){
			tempParent = tempTree.curNode;
			if((tempParent->lchild != NULL
				&& tempParent->lchild == child)
				|| (tempParent->rchild != NULL
				&& tempParent->rchild == child)){
				flag = 1;//find it
				break;//can't return
			}
		}
	LSZ_TreeLB_endGo(&tempTree);
	if(flag == 1)
		return tempParent;
	return NULL; //not found
}

/**
 * to return a node's left child's node
 * 返回一结点的左孩子的结点
 */
LSZ_TreeLBNode *LSZ_TreeLB_left(LSZ_TreeLBCtl *control,
								LSZ_TreeLBNode *parent)
{
	LSZ_TreeLBNode *tempParent = NULL;
	//the traversal will change the current node
	LSZ_TreeLBCtl tempTree;

#ifdef _LSZ_CHECK_ERROR_
	//the NULL child's parents is ambiguous
	if(control == NULL || parent == NULL)
		return NULL; //_LSZ_ERRISNULLPOINTER_;
	if(control->boot == NULL){//is empty tree
		return NULL;
	}
	LSZ_TreeLB_init(&tempTree);
	tempTree.boot = control->boot;
	LSZ_TreeLB_beginGo(&tempTree, INORDER)
		while(LSZ_TreeLB_inorder(&tempTree) == 0)
			if(tempTree.curNode == parent){
				tempParent = tempTree.curNode;
				break;
			}
	LSZ_TreeLB_endGo(&tempTree);
	if(tempParent == NULL)//the parents node is not found in the tree
		return NULL; //not found
#endif
	return tempParent->lchild;
}

/**
 * to return a node's right child's value
 * 返回一结点的右孩子的结点
 */
LSZ_TreeLBNode *LSZ_TreeLB_right(LSZ_TreeLBCtl *control,
								LSZ_TreeLBNode *parent)
{
	LSZ_TreeLBNode *tempParent = NULL;
	//the traversal will change the current node
	LSZ_TreeLBCtl tempTree;

#ifdef _LSZ_CHECK_ERROR_
	//the NULL child's parents is ambiguous
	if(control == NULL || parent == NULL)
		return NULL; //_LSZ_ERRISNULLPOINTER_;
	if(control->boot == NULL){//is empty tree
		return NULL;
	}
	LSZ_TreeLB_init(&tempTree);
	tempTree.boot = control->boot;
	LSZ_TreeLB_beginGo(&tempTree, INORDER)
		while(LSZ_TreeLB_inorder(&tempTree) == 0)
			if(tempTree.curNode == parent){
				tempParent = tempTree.curNode;
				break;
			}
	LSZ_TreeLB_endGo(&tempTree);
	if(tempParent == NULL)//the parents node not found
		return NULL;
#endif
	return tempParent->rchild;
}

/**
 * If do insert operation, when traversing,
 * the traversing will be damaged.
 * And in order to protect the the stack that record the traversal,
 * the insertoperation only can be done with 'curNode'.
 * 当做插入操作并且是在遍历树操作时调用
 * 遍历可能会被破坏，所以插入操作只允许对'curNode'操作
 * 
 * to insert a data into a tree
 * which will be the child node of 'parent''s node.
 * when parameter 'where' is 'LEFT' is to be left child,
 * when is 'RIGHT' to be right child, when is 'INITIAL' to be root.
 * and the parents' child will be new node's left child
 * 一数据成为双亲结点的孩子结点
 */
int LSZ_TreeLB_add(LSZ_TreeLBCtl *control,
					LSZ_TreeLBNode *node,
					LSZ_MT *data,
					LSZ_TreeLBTo where)
{
	LSZ_TreeLBCtl tempTree;	//temporary tree used to traverse
	LSZ_TreeLBNode *tempParent = NULL, *newChild;

#ifdef _LSZ_CHECK_ERROR_
	if(control == NULL || data == NULL)
		return _LSZ_ERRISNULLPOINTER_;
	//when traversing, insert operation must do with 'curNode'
	//在遍历时只能对'curNode'插入操作
	if(control->way != STOP && control->curNode != NULL
		&& node != control->curNode) //insert after first step
		return _LSZ_ERRTREELBINARYTRAVERSAL_;
#endif
	if(!_LSZ_FUN_TREELB_NODE(newChild))
		return _LSZ_ERRISFAILALLOCATE_;
	LSZ_MT_sign(&(newChild->data), data);
	newChild->lchild = newChild->rchild = NULL;
	if(where == INITIAL){//to be the root
		if(control->boot != NULL) //left child is default
			newChild->lchild = control->boot;
		control->boot = newChild;
		return 0;
	}
#ifdef _LSZ_CHECK_ERROR_
	LSZ_TreeLB_init(&tempTree);
	tempTree.boot = control->boot;
	LSZ_TreeLB_beginGo(&tempTree, INORDER)
		while(LSZ_TreeLB_inorder(&tempTree) == 0)
			if(tempTree.curNode == node){
				tempParent = tempTree.curNode;
				break;
			}
	LSZ_TreeLB_endGo(&tempTree);
	if(tempParent == NULL)//the parents node not found
		return _LSZ_ERRTREELBINARYTRAVERSAL_;
#endif
	//to be the parents node's child
	if(where == LEFT){//default to be left child
		newChild->lchild = node->lchild;
		node->lchild = newChild;
	}else{//default to be left child
		newChild->lchild = node->rchild;
		node->rchild = newChild;
	}
	control->count += 1;
	return 0;
}

/**
 * If do delete operation as traversing,
 * the traversing will be damaged.
 * So the 'curNode' will be the next node
 * after traversing the deleted tree.
 * And in order to protect the the stack
 * that record the traversal, the delete
 * operation only can be done with 'curNode'.
 * 当在遍历中删除操作时，只能对‘curNode’操作。
 * ‘curNode’时会调整下一个‘curNode’。
 * 
 * to delete a node of a tree as well as the node's children
 * and to release the data in it
 * 删除一结点及其孩子,并销毁其数据
 */
int LSZ_TreeLB_del(LSZ_TreeLBCtl *control,
					LSZ_TreeLBNode * delNode,
					LSZ_MT *dataR)
{
	LSZ_TreeLBNode *tempNode = NULL, *tempParent = NULL;
	LSZ_TreeLBCtl tempTree;
	LSZ_MT data;
	int count;

#ifdef _LSZ_CHECK_ERROR_
	//when traversing, delete operation must do with 'curNode'
	//在遍历时只能对'curNode'删除操作
	if(control->way != STOP
		&& delNode != control->curNode)
		return -1;
#endif
	LSZ_TreeLB_init(&tempTree);
	tempTree.boot = control->boot;
	//find the node that will be deleted and its parents node
	LSZ_TreeLB_beginGo(&tempTree, INORDER);
		while(LSZ_TreeLB_inorder(&tempTree) == 0){
			tempNode = tempTree.curNode;
			if(tempNode->lchild == delNode){
				tempParent = tempNode;
				tempParent->lchild = NULL;
				break;
			}
			if(tempNode->rchild  == delNode){
				tempParent = tempNode;
				tempParent->rchild = NULL;
				break;
			}
		}
	LSZ_TreeLB_endGo(&tempTree);
	if(tempParent == NULL){
		//is to delete the boot node
		if(control->boot == delNode){
			delNode = control->boot;
			control->boot = NULL;
			control->count = 0;
		}
		else	//the node isn't in the tree
			return -1;
	}
	LSZ_MT_init(&data);
	switch(control->way){
		case PREORDER://the node accessed have been pushed on the stack
			control->curNode = NULL;//the current node has been deleted
			control->next = RIGHT;//assume that has finished traversing
			while(LSZ_Stack_pop(&(control->traversing), &data) == 0){
				LSZ_MT_rd(&tempNode, &data);
				//backtrack and find the next node of traversing
				if((tempNode = tempNode->rchild) != NULL){
					control->curNode = tempNode;
					LSZ_MT_wt(&data, &tempNode);
					LSZ_Stack_push(&(control->traversing), &data);
					control->next = LEFT;
					break;
				}
			}
			break;
		case INORDER:
			control->curNode = NULL;
			control->next = RIGHT;
			//backtrack also move to the next node of traversing
			LSZ_TreeLB_inorder(control);
			break;
		case POSTORDER:
			control->curNode = NULL;
			control->next = RIGHT;
			//backtrack also move to the next node of traversing
			LSZ_TreeLB_postorder(control);
			break;
		case STOP:
			break;
		default : return -1;
	}
	if(dataR != NULL)
		LSZ_MT_sign(dataR, &(delNode->data));
	//to delete a node and its children
	LSZ_TreeLB_del_(delNode);
	return 0;
}

/**
 * this function isn't for legal inspection
 * that whether the node is in the tree or is traversed
 * 该函数不做合法性检查,
 * 则不检查结点是否在树上,或是否可删,或正在遍历中,所以为静态函数
 * 
 * to destroy a binary linked node and its children
 * as well as the data save in it
 * 销毁一二叉链表结构的一结点及它的孩子
 * 还有销毁存储在里边的数据
 */
static int LSZ_TreeLB_del_(LSZ_TreeLBNode *delNode)
{
	LSZ_TreeLBCtl delTree;

	LSZ_TreeLB_init(&delTree);
	delTree.boot = delNode;
	//can't use the preorder traversal
	//不能使用前序遍历
	LSZ_TreeLB_beginGo(&delTree, POSTORDER);
		while(LSZ_TreeLB_postorder(&delTree) == 0){
			LSZ_MT_dest(&(delTree.curNode->data));
			free(delTree.curNode);
		}
	LSZ_TreeLB_endGo(&delTree);
	return 0;
}

//the end of file
#endif
