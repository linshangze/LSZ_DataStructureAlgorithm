/********************************************************************
 *File Name: LSZ_LinearListCL.h
 *Author: Linshangze//林上泽
 *Mail: linshangze163@163.com
 *Created Time: 2013-08-29
 *Updated Time: 2015-01-20
 *******************************************************************/

/********************************************************************
 *firster file of LSZ_LinearListCL data structure
 *LSZ_LinearListCL头文件
 *******************************************************************/
//没有头结点的双向链表。
//  ------     -----           -----
// |*first|-->|data |-->...-->|data |--
// |count |   |*next|         |*next|  |
//  ------     -----           -----   |
//               ^                     |
//               |                     |
//                ---------------------

#ifndef _LSZ_LINEARLISTCL_H_
#define _LSZ_LINEARLISTCL_H_

#include <malloc.h>
#include "../../LSZ_DataType/LSZ_DataType.h"
#include "../../LSZ_DataType/LSZ_ErrorType.h"

/////////////////////////////////////////////////////////////////////
//macro
//宏定义
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
//definition of type
//数据类型定义
/////////////////////////////////////////////////////////////////////

/**
 * the node in the linear list of LSZ_LinearListCL.
 * 节点的结构
 */
typedef struct LSZ_LLCLNode{
	LSZ_MT data; //the data saved in LSZ_LinearListCL
	struct LSZ_LLCLNode *next; //pointer to the next node
}LSZ_LLCLNode;
/**
 * the structure controlling the LSZ_LinearListCL.
 * 控制LSZ_LinearListCL的结构
 */
typedef struct LSZ_LLCLCtl{
	LSZ_LLCLNode *first; //point to the first node of LSZ_LinearListCL
	int count; //the count of the nodes in LSZ_LinearListCL
}LSZ_LLCLCtl;

/////////////////////////////////////////////////////////////////////
//declaration of functions
//函数声明
/////////////////////////////////////////////////////////////////////

/**
 * to initialize a LSZ_LinearListCL
 * 初始化一LSZ_LinearListCL
 */
extern int LSZ_LLCL_init(LSZ_LLCLCtl *control);

/**
 * to destroy a LSZ_LinearListCL.
 * 销毁一LSZ_LinearListCL。。
 */
extern int LSZ_LLCL_dest(LSZ_LLCLCtl *control);

/**
 * difference.//不同于单向普通链表
 * to clear a LSZ_LinearListCL.
 * 清空一LSZ_LinearListCL。
 */
extern int LSZ_LLCL_clear(LSZ_LLCLCtl *control);

/**
 * to get the length of a LSZ_LinearListCL.
 * 取得一LSZ_LinearListCL的长度。
 */
extern int LSZ_LLCL_size(LSZ_LLCLCtl *control);

/**
 * difference//不同于单向普通链表
 * to insert a new node into a LSZ_LinearListCL
 * according to the sequence number
 * 在一LSZ_LinearListCL根据结点的序列号新建结点插入数据
 */
extern int LSZ_LLCL_add(LSZ_LLCLCtl *control,
					LSZ_MT *data,
					int number);
/**
 * difference//不同于单向普通链表
 * to delete a node in a LSZ_LinearListCL
 * according to the sequence number and
 * the data in it will be released
 * 在一LSZ_LinearListCL根据结点的序列号删除结点
 * 而存储在其中的数据将会被销毁
 */
extern int LSZ_LLCL_del(LSZ_LLCLCtl *control,
					LSZ_MT *data,
					int number);

/**
 * difference.//不同于单向普通链表。
 * to get data in a LSZ_LinearListCL.
 * according to the sequence number.
 * return its sequence number(>= 0)if successfully.
 * 在一LSZ_LinearListCL根据结点的序列号获取其数据。
 * 如果成功返回其序列号（>=0）。
 */
extern int LSZ_LLCL_rd(LSZ_LLCLCtl *control,
				LSZ_MT *data,
				int number);

/**
 * difference.//不同于单向普通链表。
 * to write data in a LSZ_LinearListCL.
 * according to the sequence number.
 * return its sequence number(>= 0)if successfully.
 * 在一LSZ_LinearListCL根据结点的序列号修改其数据。
 * 如果成功返回其序列号（>=0）。
 */
extern int LSZ_LLCL_wt(LSZ_LLCLCtl *control,
				LSZ_MT *data,
				int number);

/**
 * difference//不同于单向普通链表
 * to traverse a LSZ_LinearListCL using the LSZ_LLCL_checkFun()
 * begin with the node of number until the LSZ_LLCL_checkFun()
 * return true and the data parameter will return the data
 * saved in the node if it isn't NULL.
 * 用LSZ_LLCL_checkFun()从number遍历一LSZ_LinearListCL
 * 直到LSZ_LLCL_checkFun()返回成功
 * 参数data如非空会返回其存储的数据
 */
extern int LSZ_LLCL_trav(LSZ_LLCLCtl *control,
					int number,
					int (*LSZ_LLCL_checkFun)(LSZ_MT*),
					LSZ_MT *data);

/////////////////////////////////////////////////////////////////////
//LSZ_LinearListL在基本操作上增加的操作。
/////////////////////////////////////////////////////////////////////

/**
 * difference//不同于单向普通链表
 * to find the node
 * according to the sequence number
 * 根据序号找到结点
 */
extern LSZ_LLCLNode* LSZ_LLCL_findNode(LSZ_LLCLCtl *control,
								int number);

/**
 * to find the next node of node parameter
 * 找到参数node的后继结点并返回
 */
extern LSZ_LLCLNode* LSZ_LLCL_nextNode(LSZ_LLCLNode *node);

/**
 * difference//不同于单向普通链表
 * to find the prior node of node parameter
 * 找到参数node的前继结点
 */
extern LSZ_LLCLNode* LSZ_LLCL_priorNode(LSZ_LLCLNode *node);

/**
 * difference//不同于单向普通链表
 * to chaining LSZ_LinearListCL b to the end of LSZ_LinearListCL a
 * and the LSZ_LinearListCL b will be LSZ_LLCL_clear1()
 * 将LSZ_LinearListCL b链接到LSZ_LinearListCL a的尾部
 * 而LSZ_LinearListCL b将被初始化
 */
extern int LSZ_LLCL_append(LSZ_LLCLCtl *aControl,
					LSZ_LLCLCtl *bControl);

/**
 * difference//不同于单向普通链表//还没实现
 * to find the prior node of node parameter
 * to swap two nodes
 * no matter whether they are in the same LSZ_LinearListCL or not
 * 交换存在于任意LSZ_LinearListCL中的两结点
 */
 int LSZ_LLCL_swapNode(LSZ_LLCLCtl *aControl,
						LSZ_LLCLNode *aNode,
						LSZ_LLCLCtl *bControl,
						LSZ_LLCLNode *bNode);

//the end of file
#endif
