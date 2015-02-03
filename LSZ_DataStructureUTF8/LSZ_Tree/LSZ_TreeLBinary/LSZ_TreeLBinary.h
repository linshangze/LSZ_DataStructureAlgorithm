/********************************************************************
 *File Name: LSZ_TreeLBinary.h
 *Author: Linshangze//林上泽
 *Mail: linshangze163@163.com
 *Created Time: 2012-10-19
 *Updated Time: 2015-01-22
 *******************************************************************/

/********************************************************************
 *header file of LSZ_TreeLBinary data structure
 *LSZ_TreeLBinary头文件
 *******************************************************************/

#ifndef _LSZ_TREELBINARY_H_
#define _LSZ_TREELBINARY_H_

#include "../../LSZ_DataType/LSZ_DataType.h"
#include "../../LSZ_DataType/LSZ_ErrorType.h"
#include "../../LSZ_Stack/LSZ_Stack.h"
#include "../../LSZ_Queue/LSZ_Queue.h"

/////////////////////////////////////////////////////////////////////
//macro
/////////////////////////////////////////////////////////////////////

/**
 * to chose a way to begin to traverse a tree
 * and it should match with 'LSZ_TreeLB_endGo()'
 * 以某种方式开始遍历树
 */
#define LSZ_TreeLB_beginGo(control, traversal); \
	{(control)->curNode=NULL,\
	(control)->way=traversal,(control)->next=INITIAL;

/**
 * to end traversing a tree
 * it must be used after 'LSZ_TreeLB_beginGo()'
 * 结束一树的遍历操作,与上一宏成对使用
 */
#define LSZ_TreeLB_endGo(control); \
	(control)->way=STOP,\
	LSZ_Stack_dest(&((control)->traversing));}

/**
 * 遍历失败返回值。
 */
#define _LSZ_ERRTREELBINARYTRAVERSAL_ -4

/////////////////////////////////////////////////////////////////////
//definition of type
//数据类型定义
/////////////////////////////////////////////////////////////////////

/**
 * the node structure of binary linked tree
 */
typedef struct LSZ_TreeLBNode
{
	LSZ_MT data; //the data saved
	struct LSZ_TreeLBNode *lchild;//the left child of the node
	struct LSZ_TreeLBNode *rchild;//the right child of the node
}LSZ_TreeLBNode; //enumeration, the direction of travrsing a tree

/**
 * 指示当前树结点的下一个结点。
 */
typedef enum LSZ_TreeLBTo{
	INITIAL, //指示根
	LEFT, //指示左孩子
	RIGHT //指示有孩子
}LSZ_TreeLBTo;
/**
 * the way to traverse a tree
 * 指示树的遍历方式。
 */
typedef enum LSZ_TreeLBGo{
	STOP, //没有遍历操作
	PREORDER, //前序遍历
	INORDER, //中序遍历
	POSTORDER //后序遍历
}LSZ_TreeLBGo;

/**
 * the structure controling binary linked tree
 */
typedef struct LSZ_TreeLBCtl{
	//point to the boot node of a tree
	//树根结点
	LSZ_TreeLBNode *boot;
	//结点个数。
	int count;
	//the last node that has been traversed
	//在遍历中，最后被遍历到的结点
	LSZ_TreeLBNode *curNode;
	//the next step when traversing a tree
	//指示遍历的下一个方向
	LSZ_TreeLBTo next;
	//the way to traverse a tree
	//当前的遍历方式
	LSZ_TreeLBGo way;
	//stack of traveral, used to backtrack
	//遍历时使用的栈
	LSZ_StackCtl traversing;
}LSZ_TreeLBCtl;

/////////////////////////////////////////////////////////////////////
//declaration of functions
//函数声明
/////////////////////////////////////////////////////////////////////
//
/**
 * to initialize a binary linked tree strcuture
 * 初始化一二叉链结构的二叉树
 */
extern int LSZ_TreeLB_init(LSZ_TreeLBCtl *control);

/**
 * 销毁一二叉树和它动态申请的内存
 */
extern int LSZ_TreeLB_dest(LSZ_TreeLBCtl *control);

/**
 * to insert a data into a tree
 * which will be the child node of 'parent''s node.
 * when parameter 'where' is 'LEFT' is to be left child,
 * when is 'RIGHT' to be right child, when is 'INITIAL' to be root.
 * and the parents' child will be new node's left child
 * 一数据成为双亲结点的孩子结点
 */
extern int LSZ_TreeLB_add(LSZ_TreeLBCtl *control,
					LSZ_TreeLBNode *node,
					LSZ_MT *data,
					LSZ_TreeLBTo where);

/**
 * to delete a node of a tree as well as the node's children
 * and to release the data in it
 * 删除一结点及其孩子,并销毁其数据
 */
extern int LSZ_TreeLB_del(LSZ_TreeLBCtl *control,
					LSZ_TreeLBNode * delNode,
					LSZ_MT *dataR);

/**
 * make a next step after the 'curNode'
 * as preorder traversing a binary tree
 * and the 'curNode' will be changed
 * 以先序遍历的方式踏出'curNode'的下一步
 */
extern int LSZ_TreeLB_preorder(LSZ_TreeLBCtl *control);

/**
 * make a next step after the 'curNode'
 * as inorder traversing a binary tree
 * and the 'curNode' will be changed
 * 以中序遍历的方式踏出'curNode'的下一步
 */
extern int LSZ_TreeLB_inorder(LSZ_TreeLBCtl *control);

/**
 * make a next step after the 'curNode'
 * as postorder traversing a binary tree
 * and the 'curNode' will be changed
 * 以后序遍历的方式踏出'curNode'的下一步
 */
extern int LSZ_TreeLB_postorder(LSZ_TreeLBCtl *control);

/**
 * to find a child node's parents
 * and return its parent's node
 * 返回一结点的父母结点
 */
extern LSZ_TreeLBNode *LSZ_TreeLB_parent(LSZ_TreeLBCtl *control,
									LSZ_TreeLBNode *child);

/**
 * to return a node's left child's node
 * 返回一结点的左孩子的结点
 */
extern LSZ_TreeLBNode *LSZ_TreeLB_left(LSZ_TreeLBCtl *control,
								LSZ_TreeLBNode *parent);

/**
 * to return a node's right child's value
 * 返回一结点的右孩子的结点
 */
extern LSZ_TreeLBNode *LSZ_TreeLB_right(LSZ_TreeLBCtl *control,
								LSZ_TreeLBNode *parent);

//the end of file
#endif

