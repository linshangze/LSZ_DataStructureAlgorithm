/********************************************************************
 *File Name: testLSZ_TreeLBinary.c
 *author: Linshangze//林上泽
 *Mail: linshangze163@163.com
 *Created Time: 2013-05-25
 *Updated Time: 2015-01-22
 *******************************************************************/

/********************************************************************
 *test file for LSZ_TreeLBinary.c
 *LSZ_TreeLBinary.c测试源文件
 *******************************************************************/

#include <stdio.h>
#include <malloc.h>
#include "LSZ_TreeLBinary.h"

int main(void)
{
	LSZ_TreeLBCtl tree;
	LSZ_MT data;
	char temp, temp2;
	int i;

	LSZ_TreeLB_init(&tree);
	LSZ_MT_init(&data);

	printf("add ;\n");
	temp = 'a';
	LSZ_MT_wt(&data, &temp);
	printf("insert, root: %d %c\n",
			LSZ_TreeLB_add(&tree, tree.boot, &data, INITIAL), temp);
	i = 0;
	//构建树：
	//            a
	//        b       c
	//     d    e   f   g
	LSZ_TreeLB_beginGo(&tree, PREORDER);
		while(LSZ_TreeLB_preorder(&tree) == 0){
			if(i == 0){ //b c
				temp = 'b';
				LSZ_MT_wt(&data, &temp);
				printf("insert, right: %d %c\n",
					LSZ_TreeLB_add(&tree, tree.curNode, &data, LEFT), temp);
				temp = 'c';
				LSZ_MT_wt(&data, &temp);
				printf("insert, right: %d %c\n",
					LSZ_TreeLB_add(&tree, tree.curNode, &data, RIGHT),temp);
			}else if(i == 1){ //d e
				temp = 'd';
				LSZ_MT_wt(&data, &temp);
				printf("insert, right: %d %c\n",
					LSZ_TreeLB_add(&tree, tree.curNode, &data, LEFT), temp);
				temp = 'e';
				LSZ_MT_wt(&data, &temp);
				printf("insert, right: %d %c\n",
					LSZ_TreeLB_add(&tree, tree.curNode, &data, RIGHT),temp);
			}else if(i == 2){ //回溯
			}else if(i == 4){ //f g
				temp = 'f';
				LSZ_MT_wt(&data, &temp);
				printf("insert, right: %d %c\n",
					LSZ_TreeLB_add(&tree, tree.curNode, &data, LEFT), temp);
				temp = 'g';
				LSZ_MT_wt(&data, &temp);
				printf("insert, right: %d %c\n",
					LSZ_TreeLB_add(&tree, tree.curNode, &data, RIGHT),temp);			}
			i++;
		}
	LSZ_TreeLB_endGo(&tree);

	printf("preorder:\n");
	LSZ_TreeLB_beginGo(&tree, PREORDER);
		while(LSZ_TreeLB_preorder(&tree) == 0){
			LSZ_MT_rd(&temp, &(tree.curNode->data));
			printf("%c\t", temp);
		}
	LSZ_TreeLB_endGo(&tree);
	printf("\n");

	printf("inorder:\n");
	LSZ_TreeLB_beginGo(&tree, INORDER);
		while(LSZ_TreeLB_inorder(&tree) == 0){
			LSZ_MT_rd(&temp, &(tree.curNode->data));
			printf("%c\t", temp);
		}
	LSZ_TreeLB_endGo(&tree);
	printf("\n");

	printf("postorder:\n");
	LSZ_TreeLB_beginGo(&tree, POSTORDER);
		while(LSZ_TreeLB_postorder(&tree) == 0){
			LSZ_MT_rd(&temp, &(tree.curNode->data));
			printf("%c\t", temp);
		}
	LSZ_TreeLB_endGo(&tree);
	printf("\n");

	//修改树：
	//            a
	//        b       c
	//     d    e       g
	LSZ_TreeLB_beginGo(&tree, INORDER);
		while(LSZ_TreeLB_inorder(&tree) == 0){
				LSZ_MT_rd(&temp, &(tree.curNode->data));
				if(temp == 'c'){
					LSZ_MT_rd(&temp2, \
						&(LSZ_TreeLB_parent(&tree, tree.curNode)->data));
					printf("%c parents is %c\n", temp, temp2);
					LSZ_MT_rd(&temp2, \
						&(LSZ_TreeLB_left(&tree, tree.curNode)->data));
					printf("%c left is %c\n", temp, temp2);
					LSZ_MT_rd(&temp2, \
						&(LSZ_TreeLB_right(&tree, tree.curNode)->data));
					printf("%c right is %c\n", temp, temp2);
					printf("del, : %d %c\n",
						LSZ_TreeLB_del(&tree, tree.curNode, &data), temp);
				}
		}
	LSZ_TreeLB_endGo(&tree);

	printf("inorder:\n");
	LSZ_TreeLB_beginGo(&tree, INORDER);
		while(LSZ_TreeLB_inorder(&tree) == 0){
			LSZ_MT_rd(&temp, &(tree.curNode->data));
			printf("%c\t", temp);
		}
	LSZ_TreeLB_endGo(&tree);
	printf("\n");

	LSZ_MT_dest(&data);
	LSZ_TreeLB_dest(&tree);

	return 0;
}


