/********************************************************************
 *File Name: LSZ_LinearListL.c
 *Author: Linshangze//林上泽
 *Mail: linshangze163@163.com
 *Created Date: 2012-08-14
 *Updated Date: 2015-01-10
 *******************************************************************/

/********************************************************************
 *source file of LSZ_LinearListL data structure
 *LSZ_LinearListL源文件
 *******************************************************************/

#ifndef _LSZ_LINEARLISTL_C_
#define _LSZ_LINEARLISTL_C_

#ifndef _LSZ_CHECK_ERROR_
#define _LSZ_CHECK_ERROR_
#endif

#include "LSZ_LinearListL.h"

/////////////////////////////////////////////////////////////////////
//LSZ_LinearListL基本操作。
/////////////////////////////////////////////////////////////////////

/**
 * 创建一LSZ_LLLNode结点。
 */
#define _LSZ_FUN_LLL_NODE(n) \
	((n = (LSZ_LLLNode*)malloc(sizeof(LSZ_LLLNode))) != NULL)

/**
 * to initialize a LSZ_LinearListL
 * 初始化一LSZ_LinearListL
 */
int LSZ_LLL_init(LSZ_LLLCtl *ctl)
{
#ifdef _LSZ_CHECK_ERROR_
	if(ctl == NULL)
		return _LSZ_ERRISNULLPOINTER_;
#endif
	if((ctl->head = (LSZ_LLLNode*)
			malloc(sizeof(LSZ_LLLNode))) == NULL)
		return _LSZ_ERRISFAILALLOCATE_;
	LSZ_MT_init(&(ctl->head->data));
	ctl->head->next = NULL;//empty lists(空链)
	ctl->count = 0;
	return 0;
}

/**
 * to destroy a LSZ_LinearListL.
 * 销毁一LSZ_LinearListL.
 */
int LSZ_LLL_dest(LSZ_LLLCtl *ctrl)
{
	int count = 0;
#ifdef _LSZ_CHECK_ERROR_
	if(ctrl == NULL || ctrl->head == NULL)
		return _LSZ_ERRISNULLPOINTER_;
#endif
	while(LSZ_LLL_size(ctrl) > 0){
		LSZ_LLL_del(ctrl, NULL, 0);
		count++;
	}
	return count;
}

/**
 * to get the length of a LSZ_LinearListL
 * 取得一LSZ_LinearListL的长度
 */
int LSZ_LLL_size(LSZ_LLLCtl *ctrl)
{
#ifdef _LSZ_CHECK_ERROR_
	if(ctrl == NULL || ctrl->head == NULL)
		return _LSZ_ERRISNULLPOINTER_;
#endif
	return ctrl->count;
}

/**
 * to insert a new node into a LSZ_LinearListL
 * according to the sequence number
 * 在一LSZ_LinearListL根据结点的序列号新建结点插
 * 入数据并返回序列号
 */
int LSZ_LLL_add(LSZ_LLLCtl *ctrl,
					LSZ_MT *data,
					int number)
{
	int count;
	LSZ_LLLNode *tempNode, *newNode;

#ifdef _LSZ_CHECK_ERROR_
	if(ctrl == NULL || ctrl->head == NULL)
		return _LSZ_ERRISNULLPOINTER_;
#endif
	tempNode = ctrl->head;
	count = 0;
	while(count < number && tempNode->next != NULL){
		tempNode = tempNode->next;
		count++;
	}
	if(count != number)
		return _LSZ_ERRISOUTOFBORDER_;
	if(!_LSZ_FUN_LLL_NODE(newNode))
		return _LSZ_ERRISFAILALLOCATE_;
	LSZ_MT_init(&(newNode->data));
	LSZ_MT_sign(&(newNode->data), data);
	newNode->next = tempNode->next;
	tempNode->next = newNode;
	(ctrl->count)++;
	return count;
}

/**
 * to delete a node in a LSZ_LinearListL
 * according to the sequence number.
 * 在一LSZ_LinearListL中按结点的序列号删除结点
 * 如果data非空，会返回已删除结点的值。
 */
int LSZ_LLL_del(LSZ_LLLCtl *ctrl,
				LSZ_MT *data,
				int number)
{
	int count;
	LSZ_LLLNode *tempNode1, *tempNode2;

#ifdef _LSZ_CHECK_ERROR_
	if(ctrl == NULL || ctrl->head == NULL)
		return _LSZ_ERRISNULLPOINTER_;
#endif
	tempNode1 = ctrl->head;
	tempNode2 = tempNode1->next;
	count = 0;
	while(count < number && tempNode2 != NULL){
		tempNode1 = tempNode2;
		tempNode2 = tempNode1->next;
		count++;
	}
	if(count != number || tempNode2 == NULL) //上下界。
		return _LSZ_ERRISOUTOFBORDER_;
	tempNode1->next = tempNode2->next;
	if(data != NULL)
		LSZ_MT_sign(data, &(tempNode2->data));
	LSZ_MT_dest(&(tempNode2->data));
	free(tempNode2);
	(ctrl->count)--;
	return count;
}

/**
 * to get data in a LSZ_LinearListL
 * according to the sequence number
 * 在一LSZ_LinearListL根据结点的序列号获取其数据
 */
int LSZ_LLL_rd(LSZ_LLLCtl *ctrl,
				LSZ_MT *data,
				int number)
{
	int count;
	LSZ_LLLNode *tempNode;

#ifdef _LSZ_CHECK_ERROR_
	if(ctrl == NULL || ctrl->head == NULL)
		return _LSZ_ERRISNULLPOINTER_;
#endif
	tempNode = ctrl->head->next;
	for(count = 0; count < number && tempNode != NULL; count++)
		tempNode = tempNode->next;
	if(count != number || tempNode == NULL) //上下界。
		return _LSZ_ERRISOUTOFBORDER_;
	if(data != NULL)
		LSZ_MT_sign(data, &(tempNode->data));
	return count;
}

/**
 * to change data in a LSZ_LinearListL
 * according to the sequence number
 * 在一LSZ_LinearListL根据结点的序列号修改其数据
 */
int LSZ_LLL_wt(LSZ_LLLCtl *ctrl,
				LSZ_MT *data,
				int number)
{
	int count;
	LSZ_LLLNode *tempNode;

#ifdef _LSZ_CHECK_ERROR_
	if(ctrl == NULL || ctrl->head == NULL)
		return _LSZ_ERRISNULLPOINTER_;
#endif
	tempNode = ctrl->head->next;
	for(count = 0; count < number && tempNode != NULL; count++)
		tempNode = tempNode->next;
	if(count != number || tempNode == NULL) //上下界。
		return _LSZ_ERRISOUTOFBORDER_;
	if(data != NULL)
		LSZ_MT_sign(&(tempNode->data), data);
	return count;
}

/**
 * to traverse a LSZ_LinearListL using the LSZ_LLL_checkFun()
 * begin with the node of number until the LSZ_LLL_checkFun()
 * return true and the data parameter will return the data
 * saved in the node if it isn't NULL.
 * 用LSZ_LLL_checkFun()从number遍历一LSZ_LinearListL
 * 直到LSZ_LLL_checkFun()返回真。
 * 参数data如非空会返回其存储的数据
 */
int LSZ_LLL_trav(LSZ_LLLCtl *ctrl,
					int number,
					int (*LSZ_LLL_checkFun)(LSZ_MT*),
					LSZ_MT *data)
{
	int count = 0;
	LSZ_LLLNode *tempNode;

#ifdef _LSZ_CHECK_ERROR_
	if(ctrl == NULL || ctrl->head == NULL)
		return _LSZ_ERRISNULLPOINTER_;
	if(count > number) //下界
		return _LSZ_ERRISOUTOFBORDER_;
#endif
	tempNode = ctrl->head;
	while(tempNode->next != NULL){
		tempNode = tempNode->next;
		if(count >= number && LSZ_LLL_checkFun(&(tempNode->data))){
			if(data != NULL)
				LSZ_MT_sign(data, &(tempNode->data));
			return count;
		}
		count++;
	}
	return _LSZ_ERRISOUTOFBORDER_;
}

/////////////////////////////////////////////////////////////////////
//LSZ_LinearListL在基本操作上增加的操作。
/////////////////////////////////////////////////////////////////////

/**
 * to find the node
 * according to the sequence number
 * 根据序号找到结点
 */
LSZ_LLLNode* LSZ_LLL_findNode(LSZ_LLLCtl *ctrl,
								int number)
{
	int count = 0;
	LSZ_LLLNode *tempNode;

#ifdef _LSZ_CHECK_ERROR_
	if(ctrl == NULL || ctrl->head == NULL)
		return NULL; //_LSZ_ERRISNULLPOINTER_;
#endif
	tempNode = ctrl->head->next;
	while(count < number && tempNode != NULL){
		tempNode = tempNode->next;
		count++;
	}
	if(count != number || tempNode == NULL) //上下界
		return NULL; //_LSZ_ERRISOUTOFBORDER_;
	return tempNode;
}

/**
 * to find the next node of node parameter
 * 找到参数node的后继结点并返回
 */
LSZ_LLLNode* LSZ_LLL_nextNode(LSZ_LLLNode *node)
{
	return node != NULL ? node->next : NULL;
}

/**
 * to find the prior node of node parameter
 * 找到参数node的前继结点
 */
LSZ_LLLNode* LSZ_LLL_priorNode(LSZ_LLLCtl *ctrl,
								LSZ_LLLNode *node)
{
	LSZ_LLLNode *tempNode;

#ifdef _LSZ_CHECK_ERROR_
	if(ctrl == NULL || ctrl->head == NULL)
		return NULL;//_LSZ_ERRISNULLPOINTER_
#endif
	tempNode = ctrl->head;
	while(tempNode != NULL && tempNode->next != node)
		tempNode = tempNode->next;
	return tempNode;
}

/**
 * to chaining LSZ_LinearListL b to the end of LSZ_LinearListL a
 * and the LSZ_LinearListL b will be LSZ_LLL_clear1()
 * 将LSZ_LinearListL b链接到LSZ_LinearListL a的尾部
 * 而LSZ_LinearListL b将被初始化
 */
int LSZ_LLL_append(LSZ_LLLCtl *actrl,
					LSZ_LLLCtl *bctrl)
{
	LSZ_LLLNode *tempNode;

#ifdef _LSZ_CHECK_ERROR_
	if(actrl == NULL || actrl->head == NULL
			|| bctrl == NULL || bctrl->head == NULL)
		return _LSZ_ERRISNULLPOINTER_;
#endif
	tempNode = actrl->head;
	while(tempNode->next != NULL)//find the end of LSZ_LinearListL a
		tempNode = tempNode->next;
	tempNode->next = bctrl->head->next;
	actrl->count += bctrl->count;
	bctrl->head->next = NULL;
	bctrl->count = 0;
	return 0;
}

/**
 * to swap two nodes no matter whether they are in the
 * same LSZ_LinearListL or not using their prior nodes
 * 用两结点前继交换存在于任意LSZ_LinearListL中的两结点
 */
int LSZ_LLL_swapNextNode(LSZ_LLLNode *aNode,
							LSZ_LLLNode *bNode)
{
	LSZ_LLLNode *cNode;

#ifdef _LSZ_CHECK_ERROR_
	if(aNode == NULL || bNode == NULL
			|| aNode->next == NULL || bNode->next == NULL)
		return _LSZ_ERRISNULLPOINTER_;
#endif
	if(bNode->next == aNode){
		cNode = aNode;
		aNode = bNode;
		bNode = cNode;
	}//aNode是结点bNode的前继方便操作
	if(aNode->next == bNode){//they are adjacent nodes(为两相邻结点)
		//the original seconde node be the fist node now
		//原第二结点改为现在第一结点
		aNode->next = bNode->next;
		//the now previous second node's prior node which
		//also is the previous first node change its direction
		//现在的第二结点前驱即原第一结点指向原第二结点的后继
		bNode->next = bNode->next->next;
		//the previous second node that has been the first node
		//change its direction to the previous first node
		//原第二结点调已为第一结点并指向原第一结点
		aNode->next->next = bNode;
	}else{
		//the prior nodes of two nodes swap the next pointer
		//前继交换指向
		cNode = aNode->next;
		aNode->next = bNode->next;
		bNode->next = cNode;
		//two nodes swap the the next pointer
		//要交换的两结点交换后继
		cNode = aNode->next->next;
		aNode->next->next = bNode->next->next;
		bNode->next->next = cNode;
	}
	return 0;
}

/**
 * to swap two nodes
 * no matter whether they are in the same LSZ_LinearListL or not
 * 交换存在于任意LSZ_LinearListL中的两结点
 */
int LSZ_LLL_swapNode(LSZ_LLLCtl *actrl,
						LSZ_LLLNode *aNode,
						LSZ_LLLCtl *bctrl,
						LSZ_LLLNode *bNode)
{
	LSZ_LLLNode *aPriorNode, *bPriorNode;

#ifdef _LSZ_CHECK_ERROR_
	if(actrl == NULL || actrl->head == NULL ||
		bctrl == NULL || bctrl->head == NULL)
		return _LSZ_ERRISNULLPOINTER_;
	if(aNode == actrl->head || bNode == bctrl->head)
		return _LSZ_ERRISOUTOFBORDER_;
#endif
	aPriorNode = LSZ_LLL_priorNode(actrl, aNode);
	bPriorNode = LSZ_LLL_priorNode(bctrl, bNode);
	return LSZ_LLL_swapNextNode(aPriorNode, bPriorNode);
}

//the end of file
#endif

