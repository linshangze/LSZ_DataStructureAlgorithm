/*********************************************************************
 * File Name: LSZ_IntegerPartitionCount.c
 * Author: linshangze
 * Mail: linshangze163@163.com 
 * Created Time: 2013-12-30-04:37:45 HKT
 ********************************************************************/

//////////////////////////////////////////////////////////////////////
//正整数的划分数
//
//问题：
//
//  正整数n=n1+...+nk。其中n1>=..>=nk>=1。
//  正整数n的这种划分称为：正整数n的一个划分。
//  求某正整数的所有不同划分个数（称划分数）。
//
//  例如：
//    正整数2的划分数为2，
//    2=2;
//    2=1+1;
//    正整数5的划分数为7，
//    5 = 5;
//    5 = 4+1;
//    5 = 3+2 = 3+1+1;
//    5 = 2+2+1 = 2+1+1+1;
//    5 = 1+1+1+1+1;
//    其中像5=3+2和5=2+3，记为一种划分。
//
//分析：
//
//  正整数n的一个划分记为：
//  n=n1+...+nk，
//  如果max{n1,...,n2}<=m，则称这个划分为正整数n的一个m划分，记为：
//  p(n,m)，
//  记所有符合m划分的个数为：
//  count(P(n,m))。
//
//  讨论：
//  一，当m>n时，
//    由于划分中只包含正整数，所以此时count(p(n,m))=count(p(n,n))。
//  二，当m=n时，
//    如果划分中包含n，即只有一个划分，划分数为1，
//    如果划分中不包含n，那么划分中最大的数只能等于大于n-1，
//    所以此时count(p(n,m))=1+count(p(n,n-1))。
//  三，当m<n时，
//    如果划分中包含m，即n=m+n1+...+nk，其中max{n1,...,nk}<=m，
//      有count1(p(n,m))=count(p(n-m,m))，
//    如果划分中不包含m，即n=n1+...+nk，其中max{n1,...,nk}<=m-1，
//      有count1(p(n,m))=count(p(n,m-1)，
//    所以此时有count(p(n,m))=count(p(n-m,m))+count(p(n,m-1))。
//  四，在n和m的规模不断变小的后，
//    当n=1时，即只有一种划分，划分数为1，
//    当m=1时，也只有一种划分，划分数为1。
// 
//  递推式：
//    integePartitionCount(n, m)={
//      if(n == 1 || m == 1){
//        return 1;
//      }
//      else if(m > n){
//        return integerPartitionCount(n, n);
//      }
//      else if(m == n){
//        return 1 + integerPartitionCount(n, n - 1);
//      }
//      else if(m < n){
//        return integerPartitionCount(n - m, m) +
//        integerPartitionCount(n, m - 1);
//      }
//    }
//
//////////////////////////////////////////////////////////////////////

#include <stdio.h>

/**
 * 输出所有的整数划分。
 *
 * remain：整数还剩多少没被划分。
 * partitionMax：划分成分中的最大值。
 * result：划分结果保存数组，sizeof(result)/sizeof(int)=被划分的整数。
 * index：记录的划分成分个数。
 */
void LSZ_integerPartition(int remain,
							int partitionMax,
							int result[],
							int index)
{
	int partition;
	int i;
	static int count = 0;

	partition = partitionMax > remain ? remain : partitionMax;
	if(remain > 0){ //还没划分完毕。
		while(partition > 0){ //位个划分成分从最大到最小。
			if(remain >= partition){
				result[index] = partition;
				//求下一位划分成分。
				LSZ_integerPartition(remain - partition, partition, result, index + 1);
			}
			partition--; //该位的划分成分太大。
		}
	}
	if(remain == 0){ //没有剩余，可以输出。
		for(i = 0; i < index; i++){
			printf("+%d", result[i]);
		}
		printf(" --- %d\n", ++count);
		if(result[0] == 1){
			count = 0;
		}
	}
}

int LSZ_integerPartitionCount(int destination,
								int partitionMax)
{
	if(destination == 1 || partitionMax == 1){
		return 1;
	}
	else if(partitionMax > destination){
		return LSZ_integerPartitionCount(destination, destination);
	}
	else if(partitionMax == destination){
		return 1 + LSZ_integerPartitionCount(destination, destination - 1);
	}
	else if(partitionMax < destination){
		return LSZ_integerPartitionCount(destination - partitionMax, partitionMax)
			+ LSZ_integerPartitionCount(destination, partitionMax - 1);
	}
}

//end of file

