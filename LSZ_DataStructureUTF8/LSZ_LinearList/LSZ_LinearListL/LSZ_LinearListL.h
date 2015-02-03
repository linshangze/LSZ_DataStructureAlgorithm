/********************************************************************
 * File Name: LSZ_LinearListL.h
 * Author: Linshangze//林上泽
 * Mail: linshangze163@163.com
 * Created Time: 2012-08-14
 * Updated Time: 2015-01-10
 *******************************************************************/

/********************************************************************
 *header file of LSZ_LinearListL data structure
 *LSZ_LinearListL头文件
 *******************************************************************/

#ifndef _LSZ_LINEARLISTL_H_
#define _LSZ_LINEARLISTL_H_

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
 * the node in the linear list of LSZ_LinearListL
 * 节点的结构
 */
typedef struct LSZ_LLLNode{
	LSZ_MT data;//the data saved in LSZ_LinearListL
	struct LSZ_LLLNode *next;//pointer to the next node
}LSZ_LLLNode;

/**
 * the structure controlling the LSZ_LinearListL
 * 控制LSZ_LinearListL的结构
 */
typedef struct LSZ_LLLCtl{
	LSZ_LLLNode *head;//the head node of LSZ_LinearListL
	int count;//the count of the node in LSZ_LinearListL
}LSZ_LLLCtl;

/////////////////////////////////////////////////////////////////////
//declaration of functions
//函数声明
/////////////////////////////////////////////////////////////////////

/**
 * to initialize a LSZ_LinearListL
 * 初始化一LSZ_LinearListL
 */
extern int LSZ_LLL_init(LSZ_LLLCtl *ctl);

/**
 * to destroy a LSZ_LinearListL.
 * 销毁一LSZ_LinearListL.
 */
extern int LSZ_LLL_dest(LSZ_LLLCtl *ctrl);

/**
 * to get the length of a LSZ_LinearListL
 * 取得一LSZ_LinearListL的长度
 */
extern int LSZ_LLL_size(LSZ_LLLCtl *ctl);

/**
 * to insert a new node into a LSZ_LinearListL
 * according to the sequence number
 * 在一LSZ_LinearListL根据结点的序列号新建结点插
 * 入数据并返回序列号
 */
extern int LSZ_LLL_add(LSZ_LLLCtl *ctrl,
					LSZ_MT *data,
					int number);

/**
 * to delete a node in a LSZ_LinearListL
 * according to the sequence number.
 * 在一LSZ_LinearListL中按结点的序列号删除结点
 * 如果data非空，会返回已删除结点的值。
 */
extern int LSZ_LLL_del(LSZ_LLLCtl *ctrl,
				LSZ_MT *data,
				int number);

/**
 * to get data in a LSZ_LinearListL
 * according to the sequence number
 * 在一LSZ_LinearListL根据结点的序列号获取其数据
 */
extern int LSZ_LLL_rd(LSZ_LLLCtl *ctrl,
				LSZ_MT *data,
				int number);

/**
 * to change data in a LSZ_LinearListL
 * according to the sequence number
 * 在一LSZ_LinearListL根据结点的序列号修改其数据
 */
extern int LSZ_LLL_wt(LSZ_LLLCtl *ctrl,
				LSZ_MT *data,
				int number);

/**
 * to traverse a LSZ_LinearListL using the LSZ_LLL_checkFun()
 * until the LSZ_LLL_checkFun() return true
 * and the data parameter will return the data saved in the node
 * 用LSZ_LLL_checkFun()遍历一LSZ_LinearListL
 * 直到LSZ_LLL_checkFun()返回真。
 * 参数data会返回其存储的数据
 */
extern int LSZ_LLL_trav(LSZ_LLLCtl *ctrl,
					int number,
					int (*LSZ_LLL_checkFun)(LSZ_MT*),
					LSZ_MT *data);

/////////////////////////////////////////////////////////////////////
//LSZ_LinearListL在基本操作上增加的操作。
/////////////////////////////////////////////////////////////////////

/**
 * to find the node
 * according to the sequence number
 * 根据序号找到结点
 */
extern LSZ_LLLNode* LSZ_LLL_findNode(LSZ_LLLCtl *ctrl,
								int number);

/**
 * to find the next node of node parameter
 * 找到参数node的后继结点并返回
 */
extern LSZ_LLLNode* LSZ_LLL_nextNode(LSZ_LLLNode *node);

/**
 * to find the prior node of node parameter
 * 找到参数node的前继结点
 */
extern LSZ_LLLNode* LSZ_LLL_priorNode(LSZ_LLLCtl *ctrl,
								LSZ_LLLNode *node);

/**
 * to chaining LSZ_LinearListL b to the end of LSZ_LinearListL a
 * and the LSZ_LinearListL b will be LSZ_LLL_clear1()
 * 将LSZ_LinearListL b链接到LSZ_LinearListL a的尾部
 * 而LSZ_LinearListL b将被初始化
 */
extern int LSZ_LLL_append(LSZ_LLLCtl *actrl,
					LSZ_LLLCtl *bctrl);

/**
 * to swap two nodes no matter whether they are in the
 * same LSZ_LinearListL or not using their prior nodes
 * 用两结点前继交换存在于任意LSZ_LinearListL中的两结点
 */
int LSZ_LLL_swapNextNode(LSZ_LLLNode *aNode,
							LSZ_LLLNode *bNode);

/**
 * to swap two nodes
 * no matter whether they are in the same LSZ_LinearListL or not
 * 交换存在于任意LSZ_LinearListL中的两结点
 */
int LSZ_LLL_swapNode(LSZ_LLLCtl *actrl,
						LSZ_LLLNode *aNode,
						LSZ_LLLCtl *bctrl,
						LSZ_LLLNode *bNode);
//the end of file
#endif

