/*********************************************************************
 * File Name: LSZ_SearchUtility.h
 * Author: linshangze
 * Mail: linshangze163@163.com
 * Created Time: 2013-12-04-03:17:08 PM
 ********************************************************************/

#ifndef _LSZ_SEARCHUTILITY_H_
#define _LSZ_SEARCHUTILITY_H_

void LSZ_search_printArrayInt(int list[],
								int count);

void LSZ_search_printArrayFloat(float list[],
								int count);

void LSZ_search_printArrayKeyE(LSZ_SearchE list[],
								int count);

void LSZ_search_printArrayKeyBT(LSZ_SearchBTArray tree[],
								int count);

void LSZ_search_printTreeKeyBSBT(LSZ_SearchBBTNode *tree,
									int mode);

void LSZ_search_doPrintTreeKeyBSBT1(LSZ_SearchBBTNode *tree);

void LSZ_search_doPrintTreeKeyBSBT0(LSZ_SearchBBTNode *tree);

//end of file
#endif

