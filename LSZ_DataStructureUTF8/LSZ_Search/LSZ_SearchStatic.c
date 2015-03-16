/*********************************************************************
 * File Name: LSZ_SearchStatic.c
 * Author: linshangze
 * Mail: linshangze163@163.com
 * Created Time: 2013-10-24-05:58:31 PM
 ********************************************************************/

//于2013-11-11发表到csdn
//http://blog.csdn.net/lsze_

#ifndef _LSZ_SEARCHSTATIC_C_
#define _LSZ_SEARCHSTATIC_C_

//因为为静态表查找，所以使用数组作为存储
//为了统一，函数所查找的数组的0下标元素为保留位
//查找函数查找失败返回为0

#include <math.h>
#include "./LSZ_Search.h"

//
//名称：顺序查找
//关键字：顺序，监视哨
//
//在顺序表list中查找关键字等于key的数据。
//本查找中设置监视哨，这样可以免去每一步都要检查表list是否查找完毕。
//为了方便实现监视哨，list的0号元素留空，并且list所占空间为count+1。
//
//顺序表
//关键字
//顺序表元素个数
//
int LSZ_search_sequence(LSZ_SearchE list[],
						LSZ_SearchK key,
						int count)
{
	int i;

	list[0].key = key;
	for (i = count; list[i].key != key; i--){
		;
	}
	return i;
}	
//此函数是上函数的对比
int LSZ_search_sequenceComparision(LSZ_SearchE list[],
									LSZ_SearchK key,
									int count)
{
	int i;

	for (i = count; i > 0; i--){
		if(list[i].key == key){
			return i;
		}
	}
	return i;
}

//名称：折半查找
//关键字：顺序存储，有序，折半
//
//在有序顺序表list中查找关键字等于key的数据。
//注意程序中的折半是用/取整运算的，对结果是没影响的。
int LSZ_search_binary(LSZ_SearchE list[],
						LSZ_SearchK key,
						int count)
{
	int low = 1, high = count, mid;

	while(low <= high){
		mid = (low + high) / 2; //取中元素
		if(list[mid].key == key){
			return mid;
		}
		else if(list[mid].key < key){
			low = mid + 1; //往前半段查找
		}
		else{
			high = mid - 1;
		}
	}
	return 0;
}

//名称：斐波那契查找
//关键字：顺序存储，有序，斐波那契，黄金分割
//
//斐波那契序列：0,1,1,2,3,5,8,13...
//设斐波那契数列第i个数为f[i]=f[i-1]+f[i-2]。
//当i越大时，f[i]/f[i-1]越接近黄金分割比例0.6180339887...
//在元素个数为f[i]-1的有序表list中查找关键字等于key的数据。
//为什么是有f[i]-1个元素的序列才能用斐波那契查找呢，因为算法
//是使用斐波那契的序列作为分割依据，每次判断时，对于长度为
//f[i]-1长度的表是list[f[i-1]]元素和关键字比较。如果list[f[i-1]]不
//等于关键字，以它为分界，将序列分成两部分（不包括第f[i-1]个元素），
//然后每一部分的个数刚好也为同样结构。
//前部分长度为f[i-1]-1，后部分的长度为f[i-2]-1=(f[i]-1)-(f[i-1]-1)-1。
//此算法为递归求解。
//递归设计：
//不满足的部分：
//对于该部分，先寻找最大能满足斐波那契查找的部分，剩下的部分，
//也可以采用递归的方法来查找。设其结果为F2(list,low,key,f,n)
//list[low+k]为k号元素（low初始值为0，k>=1）。
//F1(list,low,key,f,n)={
//		求取合适的斐波那契数f[i];
//		判断list[f[i-1]]是否等于key，是则返回low+f[i-1];
//		用斐波那契查找F2来查找元素，如果找到则返回;
//		如果还有剩余，对剩余部分继续调用F1()查找;
//}
//对于每一有序列表，可一分成一部分长度满足f[i]-1，和剩下不满足条件的
//另一部分。
//满足的部分：
//设其结果为F1(list,low,key,f,i)，f[i]-1为序列长度。
//斐波那契数列为0,1,1,2...这里的实现不支持0下标元素。因为当列表中只有
//一个元素时，那么查找到的斐波那契数应该是f[3],此时要判断的是下标为
//f[2]=1的元素，在继续查找已重复了。如果想使用0下标元素只需将下标减1。
//F2(list,low,key,f,i)={
//		判断list[f[i-1]]是否等于key，是则返回low+f[i-1];
//		如果key小于list[f[i-1]]并且没查找完毕，
//			则继续对上半部调用F2()查找;
//		如果key大于list[f[i-1]]并且没查找完毕，
//			则继续对下半部调用F2()查找;
//}
//因为递归结构简单，可以用循环结构来解决问题，并做一些优化。
int LSZ_search_fibonacci(LSZ_SearchE list[],
							LSZ_SearchK key,
							int count)
{
	int i, j, low1 = 0, low2;
	LSZ_SearchK cutPointKey;
	static int fNumber[47] = {0, 1, 1, 2, 3,
				5, 8, 13, 21, 34,
				55, 89, 144, 233, 377,
				610, 987, 1597, 2584, 4181,
				6765, 10946, 17711, 28657, 46368,
				75025, 121393, 196418, 317811, 514229,
				832040, 1346269, 2178309, 3524578, 5702887, 
				227465, 14930352, 24157817, 39088169, 63245986,
				102334155, 165580141, 267914296, 433494437, 701408733,
				1134903170, 1836311903
	}; //列举避免重复计算

	do{
		if(count <= fNumber[LSZ_SEARCH_FIBONACCI_MAX]){
			for(i = 2; count > fNumber[i]; i++){
				; //循环查找适合的斐波那契数
			}
		}
		else{ //为下面i的使用加1，i极限为46
			i = LSZ_SEARCH_FIBONACCI_MAX + 1; //int能存储的最大斐波那契值为f[46]
		}
		if(key == list[low1 + fNumber[--i]].key){
			return low1 + fNumber[i];
		}
		low2 = low1; //low2用于内循环的规范的斐波那契查找
		j = i - 1; //fNumber[j]-1为用于规范斐波那契查找的数列长度
		while(j >= 2){ //该处为规范的斐波那契查找
			cutPointKey = list[low2 + fNumber[j]].key;
			if (key == cutPointKey){
				return low2 + fNumber[j];
			}
			else{
				if(key < cutPointKey){
					j--; //前部分
				}
				else{
					low2 += fNumber[j];
					j -= 2; //后部分
				}
			}
		}
		low1 += fNumber[i]; //用于查找不满足斐波那契数部分
	}while((count -= fNumber[i]) > 0);
	return 0;
}
//用于比较上两个函数
int LSZ_search_fibonacciComparision(LSZ_SearchE list[],
							int low,
							LSZ_SearchK key,
							int fNumber[],
							int count)
{
	int i, result;
	for(i = 2; count > fNumber[i]; i++)
		; //循环查找适合的斐波那契数
	if(key == list[low + fNumber[--i]].key)
		return low + fNumber[i];
	result = LSZ_search_fibonacciFixComparision(list, low, key, fNumber, i);
	if(result != 0)
		return result; //在前半部成功找到
	if((count -= fNumber[i]) < 0) //斐波那契数已越界
		return 0;
	return LSZ_search_fibonacciComparision(list, low + fNumber[i], key, fNumber, count);
}
int LSZ_search_fibonacciFixComparision(LSZ_SearchE list[],
							int low,
							LSZ_SearchK key,
							int fNumber[],
							int fIndex)
{
	if(--fIndex < 2){ //只剩一个元素时fIndex应为2，否则为查找失败
		return 0;
	}
	else{
		if (list[low + fNumber[fIndex]].key == key){
			return low + fNumber[fIndex];
		}
		else{
			if (key < list[low + fNumber[fIndex]].key){
				return LSZ_search_fibonacciFixComparision(list, low, key, fNumber, fIndex);
			}
			else{
				return LSZ_search_fibonacciFixComparision(list, low + fNumber[fIndex], key, fNumber, fIndex - 1);
			}
		}
	}
}
//斐波那契序列构造函数
//因为使用int类型，countNumber<=47，fibonacciNumber[47]=1836311903
int LSZ_getFibonacciNumber(int fibonacciNumber[],
							int countNumber)
{
	int i;

	if(countNumber > 0){
		fibonacciNumber[0] = 0; //只有一个斐波那契数
		if(countNumber > 1){
			fibonacciNumber[1] = 1; //有两个斐波那契数
			for(i = 2; i < countNumber; i++){ //两个以上
				fibonacciNumber[i] = fibonacciNumber[i - 1] + fibonacciNumber[i - 2];
			}
		}
		return 0;
	}
	return -1;
}

//名称：静态树表的查找
//关键字：有序，元素被查找概率不等，二叉树，次优查找树
//
//当元素被查找的概率不均匀分布时，怎么提高查找效率呢？
//被查找概率高的元素如果优先被搜索到，那就很好了。该
//算法就是将有序的数列按照其被查找的概率分布在一棵二叉树中，
//该树的特点就是，所有分布在右子树的元素都大于分布在左子树的元素，
//每棵树的根元素大于或等于左子树的根元素（或小于等于右子树的元素）。
//每个元素以它被搜索到的概率作为权值，整棵树的所有元素结点到根的
//带权路径长度（可以理解为：到根路径*权值）之和应该最小。
//算法的关键是树的构建。
//有一个虽然不是最优解，但是近似最优解的数构建方法，这方法构建的树
//称为次优查找树。该方法是只对子树进行权值总和的粗略衡量，不管其路
//径，而且使左右子树的权值总和尽量平衡，因此可以从根开始构建树。
//有大量实验证明，次优查找树和最优查找树性能只差仅为1%到2%，很少超3%。
//设元素序列list[i],(l<=i<=h)，序列元素对应权值为w[i],(l<=i<=h)，
//对于元素序列l~h，取list[r]为根结点，两子树的分别为tree1(l~r-1)，
//tree2(r+1~h)，括号里为其包含元素的下标。依据上述衡量思想，设置变
//量diff衡量带权路径长，diff[r]=|(w[r+1]+...+w[h])-(w[l]+...w[r-1])|，
//显然每次构建树tree(l~h)，需要找最小的diff[r]。
//为了计算方便，设累计权值，wHeap[i]=w[l]+...+w[i]，所以有
//diff[r]=|(wHeap[h]-wHeap[r])-(wHeap[r-1]-wHeap[l-1])|
//		 =|(wHeap[h]+wHeap[l-1])-wHeap[r]-wHeap[r-1]|;
//还需要设定wHeap[l-1]=0，w[l-1]=0。
//在下面给出递归求解的实现。
//在程序实现中，为了避免在算法中使用动态空间，我采用数组来构造树，
//程序中的数组空间均又使用者提供。
int LSZ_search_staticTree(LSZ_SearchBTArray tree[],
							LSZ_SearchK key,
							int count)
{
	LSZ_SearchTreeIndex index;
	LSZ_SearchK keyCheck; //用于暂存关键字

	index = tree[0].lChild; //获取树的根结点
	do{ //树的右孩子大于左孩子
		keyCheck = (tree[index].element)->key;
		if(keyCheck == key){
			return index;
		}
		else if(key < keyCheck){
			index = tree[index].lChild;
		}
		else{
			index = tree[index].rChild;
		}
	}while(index != 0); //查找过树叶后仍未查找到即查找失败
	return 0;
}
//名称：设置次优查找树
int LSZ_search_setNearOptimalTree(LSZ_SearchE list[],
									LSZ_SearchBTArray tree[],
									float weight[],
									float weightHeap[],
									int count)
{
	int i, sum;

	for(i = sum = 0; i <= count; i++){
		sum += weight[i]; //weight[0]相对于w[l-1]=0
		weightHeap[i] = sum; //weightHeap[0]相当于wHeap[l-1]=0
	}
	return (tree[0].lChild = tree[0].rChild = LSZ_search_nearOptimalTree(list, tree, weightHeap, 1, count)); //设置次优查找树，并用返回值设置树根坐标
}
int LSZ_search_nearOptimalTree(LSZ_SearchE list[],
								LSZ_SearchBTArray tree[],
								float weightHeap[],
								int low,
								int high)
{
	int i = low, j, diff,
		diffPart = weightHeap[high] + weightHeap[low - 1],
		min = fabs(diffPart - weightHeap[low] - weightHeap[low - 1]);

	for(j = low + 1; j <= high; j++){ //根据公式，选择较优的树根
		diff = fabs(diffPart - weightHeap[j] - weightHeap[j - 1]);
		if(diff < min){
			i = j;
			min = diff;
		}
	}
	tree[i].lChild = i == low? 0: LSZ_search_nearOptimalTree(list, tree, weightHeap, low, i - 1); //如果low元素已作为根，那么其左孩子为0
	tree[i].rChild = i == high? 0: LSZ_search_nearOptimalTree(list, tree, weightHeap, i + 1, high);
	tree[i].element = list + i; //存储元素的地址

	return i; //返回根元素下标
}
	
//end of file
#endif
