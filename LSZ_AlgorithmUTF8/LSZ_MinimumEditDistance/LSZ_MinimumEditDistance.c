/*********************************************************************
 * File Name: LSZ_MinimumEditDistance.c
 * Author: linshangze
 * Mail: linshangze163@163.com 
 * Created Time: 2013-11-04-08:42:57 AM
 ********************************************************************/

//于2013-11-08发表到csdn博客
//http://blog.csdn.net/u010882617
//////////////////////////////////////////////////////////////////////
//最短编辑距离
//
//问题
// 有两个字符串a和b。现在对这两个字符串的许可编辑方法有：一、将一个字
// 符替换成另一个字符，二、添加一个字符、三、删除一个字符。
// 如何用许可的编辑方法，经过最小次数（距离）地编辑a串，使a串变成b串？
// 例如a="linszesze"，b="lszlsz"。
// lnszesze(删除i)，
// lszesze(删除n)，
// lszlsze(替换e为l)，
// lszlsz(删除e)。
// 编辑距离为4。如果每种编辑方法都需要消耗一定的代价，那最短编辑距离问
// 题就变成最小编辑代价问题。
//
//分析
//
//1定义运算规则
// 设串a和串b分别表示为strA和strB。
// 编辑方法：
// 替换串a第i个字符记为：strSubstitute(strA,i)，代价为costSubstitute。
// 添加串a第i个字符记为：strInsert(strA,i)，代价为costInsert。
// 删除串a第i个字符记为：strDelete(strA,i),代价为costDelete。
// 从a串到b串的编辑方法记为：
// 公式a
// edit(strA,strB) = str*(strA,i)+...+str*(strA,j);
// 这里的+号不是数学的加，是编辑的步骤的累加。
// str*可为任意许可的编辑方法。
// 从a串到b串的编辑代价记为：
// 公式b
// cost(edit(strA,strB)) = cost*+...+cost*; //cost*可为str*方法的代价。
//
// 因为用不同的编辑方法，cost(edit(strA,strB))就可能不同，所以，
// 目标最小编辑代价：minCost(strA,strB) = minimun{costEdit(strA,strB)}，
// 其对应的编辑方法记为minEdit(strA,strB)。
//
//2分析运算规则
// 对于两个长串，很难作出最小代价编辑方法判断。对串进行添加和删除后，
// 串中的字符坐标就可能发生化。那么，有没有方法先将一个长串转换成更
// 小的串，然后再利用这个小的串的解来对长串求解？
// 为了适应从小串到长串的求解分析，串的表示方法也可以记为：
// strA = strA(lowA,highA);
// lowA和highA分别为串的第一个字符的下标和最后一个字符的下标。
// strA串的第i个字符表示为：
// strA[i];
// 从a串转换到b串的最小编辑代价表示为：
// minCost(strA(lowA,highA), strB(lowB,highB));
//
//3尝试求解
// 现在尝试对a串和b串的转换做一种规模划分。假设有
// strA(lowA,lowA)和strB(lowB,lowB)。
// a串转换成b串时，a串可以分割为两部分strA(lowA,i)和strA(i+1,highA)，
// 同样b串也可以分割为两部分strB(lowB,j)和strB(j+1,highB)，如果有：
// strA(lowA,i)转换成strB(lowB,j)，strA(i+1,highA)转换成strB(j+1,highB)
// 那么可以记为：
//	edit(strA(lowA,highA),strB(lowB,highB)) =
// 						edit(strA(lowB,i),strB(lowB,j))
//						+edit(strA(i+1,highA),strB(j+1,highB));
// 那么，以上的转换代价就可以写成：
// 	cost(edit(strA(lowA,highA),strB(lowB,highA))) =
//						cost(edit(strA(lowA,i),strB(lowB,j)))
//						+cost(edit(strA(i+1,highA),strB(j+1,highB)));
// 这样，问题的解就可以用规模更小的问题来解决了。上式是一个递归式，
// 那么还要找到递归式的递归底部。因为对于完全一样的串，不用编辑操作，
// 所以设置一空操作记为：
// strIdle(strA,i); //代价为costIdle=0，
// 该代价的值应是最小的，因为这相当不发生任何操作。
// 找递归底部，当串的规模缩小到等于1或等于1时，可递归返回，伪代码：
//	minEdit(strA(lowA,higA),strB(lowB,highB))={
//		如果(a串的规模等于1 并且 b串的规模等于1){
//			如果(两串相等){
//				执行空操作;
//			}
//			否则{
//				执行替换操作;
//			}
//		}
//		否则如果(两串均空){
//			执行空操作;
//		}
//		否则如果(只有a串为空){
//			执行插入操作;
//		}
//		否则如果(只有b串为空){
//			执行删除操作;
//		}
//		否则{
//			调用edit()继续穷举所有分割情况并选择最优分割;
//		}
//	}
// 伪代码的意思是对strA(i,i)采用什么编辑操作，计算编辑代价时，
// 只要调用cost()对编辑操作再运算即可。
// 程序的实现采用0下标为开始坐标，见函数
// LSZ_String_editMinCostDivideRecursion();
//
// 编程发现，该递归无法对自身规模的问题来求解，如果当a串被分割成两个串
// NULL+strA或strA+NULL时，在对b串从NULL+strB分割到strB+NULL分割来穷举
// 求解时，在递归调用的过程中又会出现求strA编辑为strB的编辑代价。如果
// a串避免分割成出现strA或b串避免分割成出现strB的话，又无法完成所有的
// 编辑操作穷举。可见该问题无法这样分割来解决。而且算法的代价计算不严谨，
// 替换操作是可以用删除和插入操作代替的。但考虑插入和删除的代价和小于
// 替换操作的话，那就没有替换操作的必要了，所以在讨论中是假设插入和删除
// 操作的代价和是大于替换操作的。
//
//4参考改进
// 那么strA(lowA,highA)串怎么最小代价地编辑为strB(lowB,highB)？
// 串的编辑变化太多了的，但串中的每个字符对编辑的影响也是有局限性的，//矩阵链式相乘最终的合并有乘法，而这里只有加法
// 能不能用局部递增的方法从小问题到大问题求解？假设有：
//	strA(lowA,highA);
//	strB(lowB,highB);
//	costMin(strA(lowA,highA),strB(lowB,highB))={
//		如果(strA和strB的长度均为1){
//			如果(strA等于strB){
//				返回 空操作代价;
//			}
//			否则{
//				返回 替换字符代价;
//			}
//		}
//		否则如果(strA和strB的长度均为空){
//			返回 空操作代价;
//		}
//		否则如果(strA为空且strB不为空){
//			返回 插入代价*strB的长度;
//		}
//		否则如果(strB为空且strA不为空){
//			返回 删除代价*strA的长度;
//		}
//		否则{
//			...
//		}
//	}
// 以上的已知返回值的部分，是否能推导“否则”省略的部分呢？
// 已知strA到strB的最小编辑代价，如果strA或strB增加长度1，那么编
// 辑代价会怎么样变化？如果能利用以前的解来对新问题求解就最好了，
// 首先看个例，在串的尾部增加1长度会怎样影响原来的解。假设有串：
// strA="ab",strB="ab";
// 现在要将strA编辑为strB，假设我现在已经求得将"a"编辑为"ab"的最小编辑
// 代价为插入操作，那么当源串"a"增加一字符时，变成了"ab"，这时
// 的最小编辑代价变为空操作代价了。代价反而变小了，代价并不一定是线
// 性增长的，而且无法清楚当前操作会对下一步操作构成什么影响。这样，
// 就不能利用原解对新串求解了？
//
// 再试一试穷举，假设已经成功将strA(lowA,i)转换成strB(lowB,j)，
// 列举所有对strA[i]可能采用的编辑方法，从而计算所有可能的编辑代价。
//	{
//		如果(strA[i]为源串转换到目标串的合适字符
//			且 不需要更多字符){
//			空操作，
//			该次的编辑操作代价=上一次的编辑操作代价;
//			(strA[i]被加入，推导出该步的编辑包含
//			strA(lowA,i-1)到strB(lowB,j-1)的编辑。
//			因为这时strA[i]肯定是等于strB[j])
//		}
//		如果(strA[i]为源串转换到目标串时的累赘字符){
//			删除字符操作，
//			该次的编辑操作代价=上一次的编辑操作代价+删除操作代价;
//			(strA[i]被删除，推导出该步的编辑包含
//			strA(lowA,i-1)到strB(lowB,j)的编辑。
//			这时strA[i]和strB[j]的关系不确定)
//		}
//		如果(strA[i]被替换后成为源串转换为目标串时的合适字符){
//			替换字符操作，
//			该次的编辑操作代价=上一次的编辑操作代价+替换操作代价;
//			(strA[i]被替换，推导出该步的编辑包含
//			strA(lowA,i-1)到strB(lowB,j-1)的编辑。
//			这时strA[i]肯定不等于strB[j])
//		}
//		//以上均是对原串字符操作
//		如果(strA[i]为源串转换到目标串的合适字符
//			且 还需要插入k字符){
//			插入字符操作，
//			该次的编辑操作代价=上一次的编辑操作代价+插入操作代价*(j-k);
//			(strA[i]被加入，推导出该步的编辑包含
//			strA(lowA,i)到strB(lowB,k)的编辑，k<=j-1。
//			这时strA[i]肯定是等于strB[k])
//		}
//	}
// 从上面的算法中可以看到一种递归的定义了，上面列举的是对一次操作
// 所有可能情况，问题求解需要的是取最小操作代价，因此需要选择代价
// 最小的操作，还有插入操作，因为无法知道需要插入多少字符，只能用
// k来表示，当串的规模是以1字符为单位递增时，那么每次就递增1字符，
// 这时strA[i]就等于strB[j-1]了。伪代码：
//	costMin(strA(lowA,i),strB(lowB,j))={
//		if(i==lowA && j==lowB){
//			if(strA[i]==strB[i]){
//				return costIdle;
//			}
//			else{
//				return costSubstitute;
//			}
//		}
//		else if(i<lowA && j < lowB){
//			return costIdle;
//		}
//		else if(i<lowA){
//			return costInsert*(j-lowB+1);
//		}
//		else if(j<lowB){
// 			return costDelete*(i-lowA+1);
//		}
//		else{
//			if(strA[i]==strB[i]){ //优先考虑无操作
//				return costMin(strA(lowA,i-1),strB(lowB,j-1));
//		}
//		else{ //考虑其它操作
//			return Minimum{
//					costMin(strA(lowA,i-1),strB(lowB,j)+costDelete,
//					costMin(strA(lowB,i),strB(lowB,j-1)+costInsert,
//					costMin(strA(lowB,i-1),strB(lowB,j-1)+costSubstitute
//			}
//		}
//	}
// 代码实现见函数
// LSZ_String_editMinCostRecursion();
//
// 观察代码，很容易发现相同的调用可能不止一次，而且每一次会有三个
// 递归分枝，重复计算量大，这让人想到动态规划重复子问题的特性。
// 还有一个是最优子结构特性，在这里不多证明。
// 该问题现在被转化成适合用动态规划解决的问题。这里动态规划求解比简单
// 的递归求解更高效率。
//
// 观察上面算法分析，有两个变量i和j，它们的组合枚举很适合用二维数组表
// 示。于是一设问题的解记录表costEdit[m+1][n+1]，m为源串strA的长度，
// n为目标串strB的长度，考虑到会出现空串，维度要比串的长度加1。
// 于是可以写出递归式：
// 公式e
//	costEdit[i][j]={
//		if(i==-1){ //源串为空
//			return costDelete*j;
//		}
//		if(j==-1){ //目标串为空
//			return costInsert*i;
//		}
//		if(strA[i]==strB[j]){
//			return costEdit[i-1][j-1]+costIdle;
//		}
//		else{
//			return min{ //取最小代价操作
//					costEdit[i-1][j]+costDelete,
//					costEdit[i][j-1]+costInsert,
//					costEdit[i-1][j-1]+costSubstitute
//			}
//		}
// }
// 写出自下至上的动态规划实现，要保证问题所需要的子问题都已求解，观察
// 公式e，看到要求costEdit[i][j]，要保证行坐标小于i和纵坐标小于j的值
// 须先求出。串为空的情况可以较简单的初始化到数组中，然后双重循环i和j
// 递增求解即可。
// 代码实现见函数
// LSZ_String_editMinCostDynamic();
//
//5问题总结
// 最后，经过分析是可以求得两个串的最小编辑代价。编辑的过程是否能求取
// 出来？是可以的，只要参考求得的costEdit数组，从costEdit的右下顶角往
// 左或上或左上回溯至左上顶角，根据回溯的方向就可以求得解，解可能不止
// 一种。
// 这里算法的重点是求出最小编辑的代价而不关心过程。如果需要用计算机这
// 样麻烦的求取编辑方法的话，可能用直接用目标串来覆盖源串消耗的代价更
// 少。
//
//////////////////////////////////////////////////////////////////////

//算法要求以下代价的定义满足
//(LSZ_COST_STRDELETE+LSZ_COST_STRINSERT)>LSZ_COST_STRSUBSTITUTE
//LSZ_COST_STRIDLE<minimun{
//		LSZ_COST_STRDELETE,LSZ_COST_STRINSERT,LSZ_COST_STRSUBSTITUTE}
#define LSZ_COST_STRDELETE 1 //一个删除操作需要的代价
#define LSZ_COST_STRINSERT 1 //一个插入操作需要的代价
#define LSZ_COST_STRSUBSTITUTE 1 //一个交换操作需要的代价
#define LSZ_COST_STRIDLE 0 //空操作的代价

//错误的递归求解两串最小编辑代价
int LSZ_String_editMinCostDivideRecursion(char strSource[],
											int lowSrc,
											int highSrc,
											char strDestination[],
											int lowDst,
											int highDst)
{
	int indexSrc, indexDst, costMin, costCheck;

	if(lowSrc == highSrc && lowDst == highDst){ //每个串都满足只有一个字或空字符
		if(strSource[lowSrc] == strDestination[lowDst]){
			return LSZ_COST_STRIDLE; //相等，空操作
		}
		else{
			return LSZ_COST_STRSUBSTITUTE; //不等，替换
		}
	}
	else if(lowSrc > highSrc && lowDst > highDst){
			return LSZ_COST_STRIDLE; //两串都为空串，空操作
	}
	else if(lowSrc > highSrc){ //只有源串为空
		return LSZ_COST_STRINSERT * (highDst - lowDst + 1);
	}
	else if(lowDst > highDst){ //只有目标串为空
		return LSZ_COST_STRDELETE * (highSrc - lowSrc + 1);
	}
	for(indexDst = lowDst - 1; indexDst <= highDst; indexDst++){
		//循环初始值
		costMin = LSZ_String_editMinCostDivideRecursion(strSource, lowSrc,
					lowSrc - 1, strDestination, lowDst, indexDst)
			+ LSZ_String_editMinCostDivideRecursion(strSource, lowSrc,
				lowSrc, strDestination, indexDst + 1, highDst);
		for(indexSrc = lowSrc + 1; indexSrc <= highSrc; indexSrc++){
			costCheck = LSZ_String_editMinCostDivideRecursion(strSource,
					lowSrc, indexSrc, strDestination, lowDst, indexDst)
				+ LSZ_String_editMinCostDivideRecursion(strSource,
					indexSrc + 1, highSrc, strDestination, indexDst + 1,
				   	highDst);
			if(costCheck < costMin){
				costMin = costCheck;
			}
		}
	}
	return costMin;
}

//递归解两串的最小编辑代价
//参数
//strSource：源串
//countSrc：源串的长度
//strDestination：目标串
//countDst：目标串的长度
int LSZ_String_editMinCostRecursion(char strSource[],
									int countSrc,
									char strDestination[],
									int countDst)
{
	int costDelete, costInsert, costSubstitute;

	if(countSrc == 1 && countDst == 1){ //串的规模均为1
		if(strSource[0] == strDestination[0]){
			return LSZ_COST_STRIDLE;
		}
		else{
			return LSZ_COST_STRSUBSTITUTE;
		}
	}
	else if(countSrc < 0 && countDst < 0){
		return LSZ_COST_STRIDLE;
	}
	else if(countSrc < 0){
		return LSZ_COST_STRINSERT * countDst;
	}
	else if(countDst < 0){
		return LSZ_COST_STRDELETE * countSrc;
	}
	else{
		if(strSource[countSrc - 1] == strDestination[countDst - 1]){ //优先考虑无操作
			return LSZ_String_editMinCostRecursion(strSource, countSrc - 1,
						strDestination, countDst - 1) + LSZ_COST_STRIDLE;
		}
		else{ //考虑其它操作
			costDelete = LSZ_String_editMinCostRecursion(strSource, countSrc - 1,
				strDestination, countDst) + LSZ_COST_STRDELETE,
			costInsert = LSZ_String_editMinCostRecursion(strSource, countSrc,
				strDestination, countDst - 1) + LSZ_COST_STRINSERT,
			costSubstitute = LSZ_String_editMinCostRecursion(strSource, countSrc - 1,
				strDestination, countDst - 1) + LSZ_COST_STRSUBSTITUTE;
			return costDelete < costInsert ? costDelete
						: (costInsert < costSubstitute ? costInsert : costSubstitute);
		}
	}
}

//动态规划求解两串的最小编辑代价
//参数
//strSource：源串
//countSrc：源串的长度
//strDestination：目标串
//countDst：目标串的长度
//costEdit：编辑代价记录表，为方便代码编写，其为二维指针，
//			costEdit[i][j]表示长度为i的strSource编辑到长度
//			为j的strDestination所用的最小代价
int LSZ_String_editMinCostDynamic(char strSource[],
									int countSrc,
									char strDestination[],
									int countDst,
									int *costEditFix[])
{
	int indexSrc, indexDst;
	int costDelete, costInsert, costSubstitute;

	for(indexSrc = 0; indexSrc <= countSrc; indexSrc++){
		costEditFix[indexSrc][0] = indexSrc * LSZ_COST_STRDELETE;
	} //记录所有目标串为0的是的编辑代价
	for(indexDst = 0; indexDst <= countDst; indexDst++){
		costEditFix[0][indexDst] = indexDst * LSZ_COST_STRINSERT;
	} //记录所有源串为0的是的编辑代价
	for(indexDst = 1; indexDst <= countDst; indexDst++){
		for(indexSrc = 1; indexSrc <= countSrc; indexSrc++){
			if(strSource[indexSrc] == strDestination[indexDst]){
				costEditFix[indexSrc][indexDst] =
					costEditFix[indexSrc - 1][indexDst - 1] + LSZ_COST_STRIDLE;
			}
			else{
				costDelete = costEditFix[indexSrc - 1][indexDst] + LSZ_COST_STRDELETE;
				costInsert = costEditFix[indexSrc][indexDst - 1] + LSZ_COST_STRINSERT;
				costSubstitute = costEditFix[indexSrc - 1][indexDst - 1] + LSZ_COST_STRSUBSTITUTE;
				costEditFix[indexSrc][indexDst] = costDelete < costInsert ? costDelete
					: (costInsert < costSubstitute ? costInsert : costSubstitute);

			}
		}
	}
	return costEditFix[countSrc][countDst];
}
