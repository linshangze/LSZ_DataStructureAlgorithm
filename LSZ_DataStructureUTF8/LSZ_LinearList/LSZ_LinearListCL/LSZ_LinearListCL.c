/********************************************************************
 *File Name: LSZ_LinearListCL.c
 *Author: Linshangze//林上泽
 *Mail: linshangze163@163.com
 *Created Time: 2013-08-29
 *Updated Time: 2015-01-20
 *******************************************************************/

/********************************************************************
 *source file of LSZ_LinearListCL data structure
 *LSZ_LinearListCL源文件
 *******************************************************************/

#ifndef _LSZ_LINEARLISTCL_C_
#define _LSZ_LINEARLISTCL_C_

#ifndef _LSZ_CHECK_ERROR_
#define _LSZ_CHECK_ERROR_
#endif

#include <malloc.h>
#include "LSZ_LinearListCL.h"

/**
 * 创建一LSZ_LLLNode结点。
 */
#define _LSZ_FUN_LLCL_NODE(n) \
	((n = (LSZ_LLCLNode*)malloc(sizeof(LSZ_LLCLNode))) != NULL)

/**
 * to initialize a LSZ_LinearListCL
 * 初始化一LSZ_LinearListCL
 */
int LSZ_LLCL_init(LSZ_LLCLCtl *control)
{

#ifdef _LSZ_CHECK_ERROR_
	if(control == NULL)
		return _LSZ_ERRISNULLPOINTER_;
#endif
	control->first = NULL; //empty lists//空链
	control->count = 0; //the length is 0//长度为空
	return 0;
}

/**
 * to destroy a LSZ_LinearListCL.
 * 销毁一LSZ_LinearListCL。。
 */
int LSZ_LLCL_dest(LSZ_LLCLCtl *control)
{
	//because there is no first node in the list，just do clearing.
	//因为没有头结点，所以调用清除函数就好
	return LSZ_LLCL_clear(control);
}

/**
 * difference.//不同于单向普通链表
 * to clear a LSZ_LinearListCL.
 * 清空一LSZ_LinearListCL。
 */
int LSZ_LLCL_clear(LSZ_LLCLCtl *control)
{
	LSZ_LLCLNode *tempNode, *freeNode;

#ifdef _LSZ_CHECK_ERROR_
	if(control == NULL)
		return _LSZ_ERRISNULLPOINTER_;
#endif
	if((tempNode = control->first) == NULL)
		return 0; //is empty list//是空链
	while(tempNode->next != control->first){ //if isn't the tail
		freeNode = tempNode;
		tempNode = freeNode->next;
		LSZ_MT_dest(&(freeNode->data)); //销毁数据
		free(freeNode);
	} //如果只有一个结点，头结点也就是尾结点
	LSZ_MT_dest(&(tempNode->data)); //销毁数据
	free(tempNode); //release the tail node//释放尾结点
	control->first = NULL; //empty list
	control->count = 0; //set length 0//长度设置为0
	return 0;
}

/**
 * to get the length of a LSZ_LinearListCL.
 * 取得一LSZ_LinearListCL的长度。
 */
int LSZ_LLCL_size(LSZ_LLCLCtl *control)
{
#ifdef _LSZ_CHECK_ERROR_
	if(control == NULL)
		return _LSZ_ERRISNULLPOINTER_;
#endif
	return control->count; //return the length//返回长度
}

/**
 * difference//不同于单向普通链表
 * to insert a new node into a LSZ_LinearListCL
 * according to the sequence number
 * 在一LSZ_LinearListCL根据结点的序列号新建结点插入数据
 */
int LSZ_LLCL_add(LSZ_LLCLCtl *control,
					LSZ_MT *data,
					int number)
{
	int i;
	LSZ_LLCLNode *priorNode, *nextNode, *newNode;

#ifdef _LSZ_CHECK_ERROR_
	if(control == NULL || data == NULL)
		return _LSZ_ERRISNULLPOINTER_;
#endif
	(control->count)++; //注意：计算假设插入后的序号
	//negative number or bigger number is possible
	//因为是循环链表，支持负数和大数，计算新结点的取代的序号。
	if(control->count != 0)
		number = (number % (control->count) + (control->count))
			% (control->count);
	(control->count)--; //还原
#ifdef _LSZ_CHECK_ERROR_
	if((number < 0) || (number > control->count)){
		return _LSZ_ERRISOUTOFBORDER_;
	}
#endif
	if(!_LSZ_FUN_LLCL_NODE(newNode)){
		return _LSZ_ERRISFAILALLOCATE_;
	}
	LSZ_MT_init(&(newNode->data));
	LSZ_MT_sign(&(newNode->data), data);
	//the first node will have two prior nodes
	//第一个结点有两个前继，控制结点和尾结点
	if(control->first == NULL){
		if(number != 0)
			return _LSZ_ERRISOUTOFBORDER_;
		control->first = newNode;
		newNode->next = newNode;
	}else{
		nextNode = control->first;
		for(i = 0; i < number; i++)
			nextNode = nextNode->next;//find the next node
		//find prior node of the node that will be inserted
		//找到要插入的结点的前继结点
		priorNode = nextNode;
		while(priorNode->next != nextNode)
			priorNode = priorNode->next;
		priorNode->next = newNode;
		newNode->next = nextNode;
		if(number == 0)
			control->first = newNode;
	}
	(control->count)++;
	return number;
}

/**
 * difference//不同于单向普通链表
 * to delete a node in a LSZ_LinearListCL
 * according to the sequence number and
 * the data in it will be released
 * 在一LSZ_LinearListCL根据结点的序列号删除结点
 * 而存储在其中的数据将会被销毁
 */
int LSZ_LLCL_del(LSZ_LLCLCtl *control,
					LSZ_MT *data,
					int number)
{
	int i;
	LSZ_LLCLNode *priorNode, *nextNode;

#ifdef _LSZ_CHECK_ERROR_
	if(control == NULL || control->first == NULL)
		return _LSZ_ERRISNULLPOINTER_;
#endif
	number = (number % (control->count) + (control->count))
		% (control->count);
#ifdef _LSZ_CHECK_ERROR_
	if((number < 0) || (number > control->count))
		return _LSZ_ERRISOUTOFBORDER_;
#endif
	if(1 == (control->count)){
		if(number != 0)
			return _LSZ_ERRISOUTOFBORDER_;
		if(data != NULL)
			LSZ_MT_sign(data, &(control->first->data));
		LSZ_MT_dest(&(control->first->data));
		free(control->first);
		control->first = NULL;
	}else{
		nextNode = control->first;
		for(i = 0; i < number; i++) //find the node that will be deleted
			nextNode = nextNode->next;
		priorNode = nextNode;
		while(priorNode->next != nextNode)
			priorNode = priorNode->next;
		nextNode = nextNode->next;
		LSZ_MT_sign(data, &(priorNode->next->data));
		LSZ_MT_dest(&(priorNode->next->data));
		free(priorNode->next);
		priorNode->next = nextNode;
		if(number == 0)
			control->first = nextNode;
	}
	(control->count)--;
	return number;
}

/**
 * difference.//不同于单向普通链表。
 * to get data in a LSZ_LinearListCL.
 * according to the sequence number.
 * return its sequence number(>= 0)if successfully.
 * 在一LSZ_LinearListCL根据结点的序列号获取其数据。
 * 如果成功返回其序列号（>=0）。
 */
int LSZ_LLCL_rd(LSZ_LLCLCtl *control,
				LSZ_MT *data,
				int number)
{
	int i;
	LSZ_LLCLNode *tempNode;

#ifdef _LSZ_CHECK_ERROR_
	if(control == NULL || data == NULL)
		return _LSZ_ERRISNULLPOINTER_;
	if((tempNode = control->first) == NULL)
		return _LSZ_ERRISOUTOFBORDER_; //is empty list//是空链
#endif
	number = (number % control->count + control->count)
		% control->count;
#ifdef _LSZ_CHECK_ERROR_
	if((number < 0) || (number > control->count))
		return _LSZ_ERRISOUTOFBORDER_;
#endif
	tempNode = control->first;
	for(i = 0; i < number; i++)
		tempNode = tempNode->next;
	LSZ_MT_sign(data, &(tempNode->data));
	return number;
}

/**
 * difference.//不同于单向普通链表。
 * to write data in a LSZ_LinearListCL.
 * according to the sequence number.
 * return its sequence number(>= 0)if successfully.
 * 在一LSZ_LinearListCL根据结点的序列号修改其数据。
 * 如果成功返回其序列号（>=0）。
 */
int LSZ_LLCL_wt(LSZ_LLCLCtl *control,
				LSZ_MT *data,
				int number)
{
	int i;
	LSZ_LLCLNode *tempNode;

#ifdef _LSZ_CHECK_ERROR_
	if(control == NULL || data == NULL)
		return _LSZ_ERRISNULLPOINTER_;
	if((tempNode = control->first) == NULL)
		return _LSZ_ERRISOUTOFBORDER_; //is empty list//是空链
#endif
	number = (number % control->count + control->count)
		% control->count;
#ifdef _LSZ_CHECK_ERROR_
	if((number < 0) || (number > control->count))
		return _LSZ_ERRISOUTOFBORDER_;
#endif
	tempNode = control->first;
	for(i = 0; i < number; i++)
		tempNode = tempNode->next;
	LSZ_MT_sign(&(tempNode->data), data);
	return number;
}

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
int LSZ_LLCL_trav(LSZ_LLCLCtl *control,
					int number,
					int (*LSZ_LLCL_checkFun)(LSZ_MT*),
					LSZ_MT *data)
{
	int i;
	LSZ_LLCLNode *tempNode;

#ifdef _LSZ_CHECK_ERROR_
	if(control == NULL || control->first == NULL)
		return _LSZ_ERRISNULLPOINTER_;
	if((tempNode = control->first) == NULL)
		return _LSZ_ERRISOUTOFBORDER_;
#endif
	number = (number % control->count + control->count)
		% control->count;
#ifdef _LSZ_CHECK_ERROR_
	if((number < 0) || (number > control->count))
		return _LSZ_ERRISOUTOFBORDER_;
#endif
	for(i = 0; i < number; i++)
		tempNode = tempNode->next;
	do{
		if(LSZ_LLCL_checkFun(&(tempNode->data))){
			if(data != NULL)
				LSZ_MT_sign(data, &(tempNode->data));
			return i;
		}
		tempNode = tempNode->next;
		i++;
	}while(tempNode != control->first);
	return _LSZ_ERRISOUTOFBORDER_;
}

/////////////////////////////////////////////////////////////////////
//LSZ_LinearListL在基本操作上增加的操作。
/////////////////////////////////////////////////////////////////////

/**
 * difference//不同于单向普通链表
 * to find the node
 * according to the sequence number
 * 根据序号找到结点
 */
LSZ_LLCLNode* LSZ_LLCL_findNode(LSZ_LLCLCtl *control,
								int number)
{
	int i;
	LSZ_LLCLNode *tempNode;

#ifdef _LSZ_CHECK_ERROR_
	if(control == NULL || (tempNode =  control->first) == NULL)
		return NULL; //_LSZ_ERRISNULLPOINTER_
#endif
	number = (number % control->count + control->count)
		% control->count;
#ifdef _LSZ_CHECK_ERROR_
	if((number < 0) || (number > control->count))
		return NULL; //_LSZ_ERRISOUTOFBORDER_;
#endif
	for(i = 0; i < number; i++)
		tempNode = tempNode->next;
	return tempNode;
}

/**
 * to find the next node of node parameter
 * 找到参数node的后继结点并返回
 */
LSZ_LLCLNode* LSZ_LLCL_nextNode(LSZ_LLCLNode *node)
{
	return node != NULL ? node->next : NULL;
}

/**
 * difference//不同于单向普通链表
 * to find the prior node of node parameter
 * 找到参数node的前继结点
 */
LSZ_LLCLNode* LSZ_LLCL_priorNode(LSZ_LLCLNode *node)
{
	LSZ_LLCLNode *tempNode;

#ifdef _LSZ_CHECK_ERROR_
	if(node == NULL)
		return NULL; //_LSZ_ERRISNULLPOINTER_
#endif
	tempNode = node;
	while(tempNode->next != node)
		tempNode = tempNode->next;
	return tempNode;
}

/**
 * difference//不同于单向普通链表
 * to chaining LSZ_LinearListCL b to the end of LSZ_LinearListCL a
 * and the LSZ_LinearListCL b will be LSZ_LLCL_clear1()
 * 将LSZ_LinearListCL b链接到LSZ_LinearListCL a的尾部
 * 而LSZ_LinearListCL b将被初始化
 */
int LSZ_LLCL_append(LSZ_LLCLCtl *aControl,
					LSZ_LLCLCtl *bControl)
{
	LSZ_LLCLNode *tempNode;

#ifdef _LSZ_CHECK_ERROR_
	if(aControl == NULL || bControl == NULL)
		return _LSZ_ERRISNULLPOINTER_;
#endif
	if(bControl->first == NULL)
		return 0;
	if(aControl->first == NULL){//a is empty
		aControl->first = bControl->first;
	}
	else{
		//find the end of LSZ_LinearListCL a
		tempNode = aControl->first;
		while(tempNode->next != aControl->first)
			tempNode = tempNode->next;
		tempNode->next = bControl->first;//link the first of b
		//find the end of LSZ_LinearListCL b
		tempNode = bControl->first;
		while(tempNode->next != bControl->first)
			tempNode = tempNode->next;
		tempNode->next = aControl->first;//link the end of b
	}
	aControl->count += bControl->count;
	bControl->first = NULL;
	bControl->count = 0;
	return 0;
}

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
						LSZ_LLCLNode *bNode)
{
	LSZ_LLCLNode *aPriorNode, *bPriorNode,
				 *aNextNode, *bNextNode, *tempNode;

#ifdef _LSZ_CHECK_ERROR_
	if(aControl == NULL || aControl->first == NULL ||
		bControl == NULL || bControl->first == NULL ||
		aNode == NULL || bNode == NULL)
		return _LSZ_ERRISNULLPOINTER_;
#endif
	aPriorNode = LSZ_LLCL_priorNode(aNode);
	bPriorNode = LSZ_LLCL_priorNode(bNode);
	if(bPriorNode->next == aPriorNode){
		tempNode = aPriorNode;
		aPriorNode = bPriorNode;
		bPriorNode = tempNode;
	}//aPriorNode是结点bPriorNode的前继方便操作
	if(aPriorNode->next == bPriorNode){ //只有两相邻结点也成立。
		if(aControl->first == aNode) //修改第一个结点
			aControl->first = bNode;
		else if(bControl->first == bNode) //避免相邻结点
			bControl->first = aNode;
		//原第结点改为现在第一结点
		aPriorNode->next = bPriorNode->next;
		//现在的第二结点前驱即原第一结点指向原第二结点的后继
		bPriorNode->next = bPriorNode->next->next;
		//原第二结点调已为第一结点并指向原第一结点
		aPriorNode->next->next = bPriorNode;
	}else{
		if(aControl->first == aNode) //不同于向相邻结点
			aControl->first = bNode;
		if(bControl->first == bNode)
			bControl->first = aNode;
		aNextNode = aNode->next; //保存后继
		bNextNode = bNode->next;
		if(aNode == aNextNode){ //a链只有一个结点
			bNode->next = bNode; //b的前继指向自己
		}else{ //将b放入a链
			aPriorNode->next = bNode;
			bNode->next = aNextNode;
		}
		if(bNode == bNextNode){ //b链只有一个结点
			aNode->next = aNode; //a的前继指向自己
		}else{ //将a放入b链
			bPriorNode->next = aNode;
			aNode->next = bNextNode;
		}
	}
	return 0;
}

//the end of file
#endif
