/*********************************************************************
 * File Name: LSZ_MatrixChainMultiplication.c
 * Author: linshangze
 * Mail: linshangze163@163.com 
 * Created Time: 2013-10-13-05:24:25 PM
 ********************************************************************/

//于2013-10-21发表到csdn博客
//http://blog.csdn.net/u010882617
//http://blog.csdn.net/lsze_
//////////////////////////////////////////////////////////////////////
// 算法描述
//
// 问题：
//
// 对于矩阵的链式相乘，如果没一定的算法思想，可能需要相当大的计算量。
// 本文中的矩阵表示为
//	matrix(row,column); //row为行数，Column为列数。
// 矩阵相乘的规则是：设有矩阵a(x,y)和矩阵b(y,z)相乘得到c(?,?)矩阵，
// 那么a[i][j]和b[j][k]会构成c[i][k]，结果会等到一个矩阵c(x,z)。
// 矩阵的相乘满足结合律，多矩阵相乘，不同的结合方法，运算就可能不同。
// 例如有矩阵a(8,4)，b(4,8)，c(8,2)，
// 如果按照从左到右的运算顺序，矩阵的乘法运算量为8*4*8+8*8*2=384，
// 如果先算后两个矩阵，矩阵的乘法运算量为4*8*2+8*4*2=128,
// 两种运算方式乘法的运算量之比为384/128=3。可见，对于矩阵链式相乘需
// 用一定的算法来提高效率。
// 这里要解决的问题就是矩阵的怎么优化多个矩阵相乘时的结合顺序呢？
//
// 分析：
//
// 1定义运算规则
//  设有一序列的矩阵m0,m1...mn，并表示为m[0:n]。它之间的链式相乘表示
//  为chainMul(m[0:n])，矩阵m[0:n]相乘的过程中的结合方法不定。
//  对m[0:n]的链式相乘的乘法运算量表示为countMul{chainMul(m[0:n])}，
//  如果在mi处将矩阵链断开，那么有：
//  公式a
//	countMul{chainMul(m[0:n])} =
//		countMul{chainMul(m[0:i])} + countMul{chainMul(m[i+1:n])}
//		+countMul{chainMul(m[0:i])*chainMul(m[i+1:n]};
//  公式b
//	countMul{chainMul(m[i])} = 0;
//  公式c（可由公式a和b推导）：
//	countMul{chainMul(m[i:i+1])} = countMul{m[i]*m[i+1]};
//
// 2分析运算规则
//  依据1，很清楚看到公式a中是一个可递归的运算式。
//  countMul{chainMul(m[0:i])}和countMul{chainMul(m[i+1:n])}是两个
//  子链，同样可作公式a的运算，公式b和c是递归的底部。
//  递归的重要性质是一个问题可以分解为规模较小的若干个问题，并且问题
//  的解法相同。
//  countMul{chainMul(m[0:i])}+countMul{chainMul(m[i+1:n])}可以看成
//  是子问题，而公式a就可以看成是整体问题，两个子问题的合并会影响到
//  整体问题的countMul{chainMul(m[0:i])*chainMul(m[i+1:n]}项。
//  这里很明显的问题是：
//  一，如果在所有的合法i取值中，
//    countMul{chainMul(m[0:i])}+countMul{chainMul(m[i+1:n])}最小，
//    那么countMul{chainMul(m[0:i])*chainMul(m[i+1:n]}是不是最小？
//  二，反过来说，countMul{chainMul(m[0:i])*chainMul(m[i+1:n]}最小，
//    countMul{chainMul(m[0:i])}+countMul{chainMul(m[i+1:n])}最小吗？
//  三，以上那两种的优先取小可以使countMul{chainMul(m[0:n])}最小？
//    如果是一的情况，可以由子问题决定整体问题，子问题的最优解肯定就
//    是只有一个矩阵的时候，countMul{}为0.然后就是选择两个合并，再选择
//    两个合并，每次合并的countMul{}最小，如此循环,直得到问题的整体解。
//    如果是二的情况，可以由整体问题决定子问题，根据矩阵的乘法和结合
//    律，即那么只要先整体规划，决定好i的位置，再同样处理每个子问题，
//    那么问题就可以简单取得解。
//    问题三正好决定了自上向下解决问题还是自下向上解决问题。
//  四，从以上的递归式中无法看到方法的正确性，可能以上的问题一和问题
//    二的说法都是一个极端，在不同的情况下，即在每一层的求解，都需要
//    权衡一个最优值，才能使整体问题得到解决。如果找不到有效的方法，
//    就只能用穷举的方法。
//
// 3问题首次求解
//  对于上述的问题三，给不了证明，无法知道是否为正确解。
//  对于问题四，就是穷举解决问题。
//  试试使用常规的穷举求解：
//  由公式a可以看出，问题具有递归性质，用递归进行穷举，代码相对简单。
//  为了写出递归程序，采用自上至下的求解的方式，对于每个问题，
//  穷举取i值，用a公式来计算该问题，而a公式中的子问题项也按同样的
//  方法递归用a公式计算。并在计算的过程中保存最终取得最优解的断点。
//  为了方便循环中穷举中的比较，先要给每一次循环中的第一次赋予初值，
//  然后在进入循环对初值进行更新。
//  设置变量：
//  int rowColumn[n+1]，
//  顺序记录第一个矩阵的行数，第一个矩阵的列数，即第二个矩阵的行数），
//  第二个矩阵的列数（第三个矩阵的行数）...第n个矩阵的列数。
//  为了方便计算，设置rowColumnFix=dimension+1，使rowColumnFix[-1]合法。
//  int **breakpoint，
//  为了方便编程，注意这里是二维指针，而不是二维数组。事实上应该模拟成一个
//  n*n的二维数组。
//  int k = breakpoint[i][j]记录在矩阵链段m[i:j]中最优的断开位置，
//  即有countMul{chainMul(m[i:j])}最优时，
//	countMul{chainMul(m[i:j])} =
//		countMul{chainMul(m[i:k])} + countMul{chainMul(m[k+1:j])}
//		+countMul{chainMul(m[i:k])*chainMul(m[k+1:j]};
//	具体代码见函数LSZ_Matrix_countMulRecursion()。
//
// 4.分析首次求解
//  观察代码，这样较为直观地看到，因为i的取值在不停的递归中，j的值
//  是不改变的，导致了有很多地方被重复计算，如果是一个较长的m[0:n]，
//  经过递归，那样的计算量是相对大的。
//
// 5动态规划
//   动态规划，通过组合子问题的解而解决整个问题。动态规划适用于许多子
//   问题不是独立的情况，各子问题包含公共的子子问题，而在这种情况下用
//   分治算法时会产生许多重复计算。
//   适合使用动态规划解决的问题的特征：
//   一，最优子结构，问题的最优解包含子问题的最优解，此解释为递归形式。
//	 利用该性质，对问题能从相对小的子问题出发，自下至上求解。
//   二，重叠子问题，每次产生的子问题不总是新问题，有些子问题被重复计算。
//   
//   对动态规划的理解：
//   一，最优子结构，这个性质也就是说，对于每个子问题，只要解得该子
//	 问题的最优解，而无需得到它的所有解，因为问题的最优解包含子问题
//	 的最优解，考虑当前的问题就只需考虑它的最优。这样问题就可一自下
//	 至上地从子问题到合问题层次地求解。
//
//   二，重叠子问题，这个就是动态规划的用空间换时间所利用的特征。如果
//	 是简单的分治来解问题，那么有的子问题就会被重复计算，于是动态规划
//	 是需要建立一个所有子问题的解表。如果一个子问题需要用到它的子问题，
//	 就可以直接依据子问题的解表来直接得到结果。无法直接知道哪个子问题
//	 会被使用，所以需记录所有子问题的最优解，这是穷举。子问题重叠越突
//       出，算法效率越高。
//
//   三，我目前学过的动态规划的问题有一些特征可以总结一下。
//	 问题的子问题通常是按照规模来分的，就是问题的性质是一样的，不过规
//       模缩小了。通常，问题的子问题既是它的一部分，又是同样性质的问题，
//       这样的按规模来划分子问题的问题都满足重叠子问题。因为规模大的肯定
//       包含规模小的问题，子问题间不是独立划分，所以通常满足子问题重叠这
//       个特征。这样其实就是递归地划分问题。
//   
//   动态规划的问题按规模划分可以有以下示意，每个子问题旁边的括号是它
//   包含的子问题。
//   sub0   sub1       sub2       problem
//   a1     b1(a1,a2)
//   a2                c1(a2,b2)  d1(c1,b1,a1)
//   a3     b2(a3)
//   因此，一般的动态规划解题步骤可以是：
//   1，分析问题，抽象出定义式，建立数学公式，等等。
//   2，根据定义，公式分析问题的结构是否有最优解子结构划分的特征。通常
//      递归地定义问题最优解，这样新问题就包含了子问题。
//   3，居于问题的最优子结构划分，分析问题的子问题重叠性。确定子问题的
//      记录表。
//   4，选择一种划分方法来刻画问题自下至上求解（递归，自上至下，利用递
//      归返回实动态现子问题动态划分；循环，自下向上求解，子问题被整齐
//      划分）。自上至下和自下自上的方法是有区别的。自上至下所求的子问题
//      都是必须的子问题，但需要占用堆栈，而自下至上所求解的子问题未必都
//      是最终解所需要。
//   5，编程。
//
//   重叠子问题这个特征才能实现时间换空间，如果这个特征变弱，算法会
//   退化到一般的穷举分治求解，因为不仅子问题的最优解需要记录，
//   子问题的非最优解也需要记录，记录所有的不重复子问题浪费记录空间。
//   如果子问题是异构的，算法会退化到一般穷举顺序求解，因为子问题是
//   不同的问题，每个问题都需要不同的代码来处理，那么就相当顺序求解。
//
//   证明本问题的最优子结构特征：
//	 由公式a中可看到，如果countMul{chainMul(m[0:n])}取得优解，那么，
//   子问题countMul{chainMul(m[0:i])}和countMul{chainMul(m[i+1:n])}
//   是不是最优解呢？假设子问题不是最优解，那么就会存在另外一种解法
//   使得countMul{chainMul(m[0:i])}或countMul{chainMul(m[i+1:n])}的
//   解更优，此时的总问题的解比原来的解更优，那么与原来总问题为最优
//   解相矛盾。到此可证得。
//   证明本问题的重叠子问题特征：
//   在3首次求解中可以发现，利用穷举法会出现很多重复运算，这也符合重
//   叠子问题特征。
//   矩阵链式相乘最小乘法运算求解这个问题是可以用动态规划来解决。
//
//  6动态规划求解
//   该程序的实现不需要递归调用来实现分治（递归需带备忘，有兴趣就实
//   现），直接由下至上求解。为了实现所有的子问题的求解记录，会增加
//   一个变量countMul，countMul[i][j]
//   记录在矩阵链m[i][j]的countMul{chainMul([i:j])}最优解的值。
//   这里对代码进行简单的解读。在程序中需要对每一个规模的子问题都穷举
//   出并求解，所以程序的第一个循环体是设定子矩阵链的长度。第二个循环
//   体是用来限定子矩阵链m[i:j]的i下标，对于每相同长度的子矩阵链，i一
//   直在改变，方便穷举。第三个循环体是利用已有的小规模子问题的解来选择
//   该子问题的最优解。所以代码对链的求解顺序示意为下：
//    lengthSub | m[i:j]
//      1       | [0:1], [1:2], [2:3], ..., [n-1:n-1-1]
//      2       | [0:2], [1:3], [2:4], ..., [n-2:n-2-1]
//      ...     | ...
//      n       | [0:n-1]
//  
//  7代码优化
//   在问题的求解中，发现有两矩阵（breakPoint，countMul）其实各只用了
//   一半的空间。因为在使用时，breakPoint[i][j]的i<j，countMul[i][j]的
//   i<=j。这样的两个矩阵可以合并成一个矩阵。小技巧是，只要在操作其中
//   的一个矩阵时将i和j倒过来使用就好了^_^。
//////////////////////////////////////////////////////////////////////

#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>

//the chain multiplication of matrices
//parameters
//matrices : array of matrices, number of which is count+1
//rowColumn : array of row and column of matrices, number of which is
//            count+1
//count : the number of matrices
//矩阵的链式相乘
//参数
//matrices : 存放矩阵的数组，个数为count+1
//rowColumnFix : 矩阵的行和列信息数组，个数为count+1，允许-1索引
//count : 矩阵的个数
int LSZ_Matrix_multiplyChain(double **matricesFix[],
								double *matrixResultFix[],
								int *rowColumnFix,
								int countMatrices)
{
	int **recordTable;
	int i;

	if((recordTable = (int**)malloc(sizeof(int*) * countMatrices))
			== NULL){
		return -1;
	}
	for(i = 0; i < countMatrices; i++){
		if((recordTable[i] = (int*)malloc(sizeof(int) * countMatrices))
				== NULL){
			exit(-1);
		}
	}
	LSZ_Matrix_countChainMulDynamicImprove(rowColumnFix,
		rowColumnFix, recordTable, countMatrices);
	//do matrices multiplication here
	for(i = 0; i < countMatrices; i++){
		free(recordTable[i]);
	}
	free(recordTable);
	return 0;
}

//每次矩阵相乘的结果用括号括起
void LSZ_Matrix_multiplyChainSimulation(int *recordTableFix[],
										int indexI,
										int indexJ)
{
	if(indexI == indexJ){
		printf("m[%d]", indexI);
		return;
	}
	printf("(");
	LSZ_Matrix_multiplyChainSimulation(recordTableFix,
		indexI, recordTableFix[indexI][indexJ]);
	printf("*");
	LSZ_Matrix_multiplyChainSimulation(recordTableFix,
		recordTableFix[indexI][indexJ] + 1, indexJ);
	printf(")");
}

//动态规划求解矩阵链式相乘最小乘法运算次数，代码优化
//注释省略了
int LSZ_Matrix_countChainMulDynamicImprove(int *rowColumnFix,
											int *recordTableFix[],
											int countMatrices)
{
	int iSub, jSub, lengthSub;
	int k, countTemp;
	int iSubBound;

	for(k = 0; k < countMatrices; k++){
		recordTableFix[k][k] = 0;
	}
	for(lengthSub = 1; lengthSub <= countMatrices; lengthSub++){
		iSubBound = countMatrices - lengthSub;
		for(iSub = 0; iSub < iSubBound; iSub++){
			jSub = iSub + lengthSub;
			recordTableFix[jSub][iSub] = recordTableFix[jSub][jSub] + recordTableFix[jSub][iSub + 1]
				+ rowColumnFix[iSub - 1] * rowColumnFix[iSub] * rowColumnFix[jSub];
			recordTableFix[iSub][jSub] = iSub;
			for(k = iSub + 1; k < jSub; k++){
				countTemp = recordTableFix[k][iSub] + recordTableFix[jSub][k + 1]
					+ rowColumnFix[iSub - 1] * rowColumnFix[k] * rowColumnFix[jSub];
				if(recordTableFix[jSub][iSub] > countTemp){
					recordTableFix[jSub][iSub] = countTemp;
					recordTableFix[iSub][jSub] = k;
				}
			}
		}
	}
	return recordTableFix[countMatrices - 1][0];
}

//动态规划求解矩阵链式相乘最小乘法运算次数
//参数
//rowColumnFix : 矩阵的行和列信息数组，个数为count+1，允许-1索引
//breakPoint : breakPoint[i][j]记录矩阵countMul{chainMul(m[i:k:j])}
//             取得最优时的断点k，i<=k<j
//countMul : countPoint[i][j]记录矩阵链countMul{chainMul(m[i:k:j])}
//             取得最优时的值
//countMatrix : 矩阵链的长度
int LSZ_Matrix_countChainMulDynamic(int *rowColumnFix,
									int *breakPointFix[],
									int *countMulFix[],
									int countMatrix)
{
	int iSub, jSub, lengthSub; //m[iSub,jSub], jSub-iSub+1=lengthSub
	int k, countTemp; //m[iSub:k:jSub], iSub<=k<jSub
	int iSubBound; //the uppper i bound of sub chain m[i:j]

	for(k = 0; k < countMatrix; k++){
		countMulFix[k][k] = 0; //countMulFix{chainMul(m[i])} = 0
	}
	for(lengthSub = 1; lengthSub <= countMatrix; lengthSub++){ //the length of sub chain
		iSubBound = countMatrix - lengthSub; //iSubBound is the upper bound of iSub
		for(iSub = 0; iSub < iSubBound; iSub++){
			jSub = iSub + lengthSub; //the j of sub chain
			//get the initial value of count for loop
			countMulFix[iSub][jSub] = countMulFix[iSub][iSub] + countMulFix[iSub + 1][jSub]
				+ rowColumnFix[iSub - 1] * rowColumnFix[iSub] * rowColumnFix[jSub];
			breakPointFix[iSub][jSub] = iSub; //get the initial breakPointFix of m[i:j]
			for(k = iSub + 1; k < jSub; k++){
				countTemp = countMulFix[iSub][k] + countMulFix[k + 1][jSub]
					+ rowColumnFix[iSub - 1] * rowColumnFix[k] * rowColumnFix[jSub];
				if(countMulFix[iSub][jSub] > countTemp){
					countMulFix[iSub][jSub] = countTemp;
					breakPointFix[iSub][jSub] = k;
				}
			}
		}
	}
	return countMulFix[0][countMatrix - 1];
}

//递归求解矩阵链式相乘最小乘法运算次数
//参数
//rowColumnFix : 矩阵的行和列信息数组，个数为count+1，允许-1索引
//breakPointFix : breakPointFix[i][j]记录矩阵countMulFix{chainMul([i:k:j])}
//             取得最优时的断点k，i<=k<j
//i : 矩阵链的开始坐标，由0开始
//j : 矩阵链的结束坐标，由0开始
//已对特殊值i=j，i+1=j，作了测试
int LSZ_Matrix_countChainMulRecursion(int *rowColumnFix,
									int *breakPointFix[],
									int i,
									int j)
{
	int count; //the count of multiplication
	int k, countTemp; //m[i:k:j], i<=k<j

	if(i == j) //the end of recursion
		return 0;
	//get the initial value of count for exhaustion
	count = LSZ_Matrix_countChainMulRecursion(rowColumnFix, breakPointFix, i, i)
		+ LSZ_Matrix_countChainMulRecursion(rowColumnFix, breakPointFix, i + 1, j)
		+ rowColumnFix[i - 1] * rowColumnFix[i] * rowColumnFix[j];
	//get the initial breakPointFix of m[i:j]
	breakPointFix[i][j] = i;
	//reflash the count and the breakPointFix
	for(k = i + 1; k < j; k++){
		countTemp = LSZ_Matrix_countChainMulRecursion(rowColumnFix, breakPointFix, i, k)
			+ LSZ_Matrix_countChainMulRecursion(rowColumnFix, breakPointFix, k + 1, j)
			+ rowColumnFix[i - 1] * rowColumnFix[k] * rowColumnFix[j];
		//update the count and breakPointFix
		if(countTemp < count){
			count = countTemp;
			breakPointFix[i][j] = k;
		}
	}
	return count; //return the count
}
