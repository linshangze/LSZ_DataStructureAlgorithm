/*********************************************************************
 * File Name: LSZ_ExtremumInSet.c
 * Author: linshangze
 * Mail: linshangze163@163.com 
 * Created Time: 2013-12-30-07:52:12 HKT
 ********************************************************************/

//////////////////////////////////////////////////////////////////////
//用分治法求一个集合中的最小值
//
//问题：
//  假设一个集合s中有n个元素。现在要在集合中找出元素的最小值。
//
//分析：
//  常规方法
//    直接遍历集合中所有元素。每次比较后取得两者中最小值，并且
//    用最小值和下一个元素比较。
//    这个方法共需比较操作次数T(n)=n-1。
//  分治方法（Divide and Conquer）：
//    1）将集合分割成两个集合s1和s2。
//    2）分别求得s1和s2的最小值min1和min2。
//    3）最后合并，min1和min2中的最小值即为集合中元素的最小值。
//    4）对于子集合s1和s2可以用1）～3）的方法求解元素的最小值。
//    比较次数T(n)：
//      1）当n=1时，比较0次。
//      2）当n=2时，比较1次。
//      3）当n>2时，如果n为奇数，比较操作T(n)=2*T((n-1)/2)+1+1次；
//                  如果n为偶数，比较操作T(n)=2*T(n/2)+1次。
//      为方便讨论，假设n是2的k次幂，k>0。
//      T(n)=2*T(n/2)+1
//          =2*(2*T(n/(2*2))+1)+1
//          =(2^2)*T(n/(2^2))+1+2
//          =4*(2*T(n/(2^3))+1)+1+2
//          =(2^3)*T(n/(2^3))+1+2+4
//          ...
//          =(2^(k-1))*T(n/(2^(k-1)))+2^0+...+2^(k-2)
//          =2^(k-1)*T(2)+2^0+...+2^(k-2)
//          =2^0+...+2^(k-1)
//          =(1*(1-2^k))/(1-2)
//          =n-1
//
//  如果是同时求最大和最小值，
//  用常规法是：最大数比较(n-1)+(n-2)=2n-3次；
//  用分治法是：
//      T(n)=2*T(n/2)+2
//          =2*(2*T(n/4)+2)+2
//          =4*T(n/4)+2+4
//          =4*(2*T(n/8)+2)+2+4
//          =8*T(n/8)+2+4+8
//          =...
//          =2^(k-1)*T(n/2^(k-1))+2^1+...+2^(k-1)
//          =2^(k-1)+2^1+...+2^(k-1)
//          =n/2+2(1-2^(k-1))/(1-2)
//          =n/2+n-2
//          =n*3/2-2
//  为什么不是：2n-2？
//   
//  分治方法和常规方法比较（图中*号为比较，假设有7个元素）：
//
//         *
//       /   \
//      *     *
//     / \   / \
//    *  3  *   *            *  *  *  *  *  *
//   / \   / \ / \          / \/ \/ \/ \/ \/ \
//   1 2   4 5 6 7          1  2  3  4  5  6  7
//       分治                        常规
//
//分治求解伪代码1（自顶向下）：
//
//  //求集合set中元素的个数。
//  count(set);
//  //分割集合set为set1和set2。
//  split(set, &set1, &set2);
//  //取两者中的最小值。
//  getMin(x, y);
//  //将集合中元素的最小值保存到min里。
//  getMinimum(set, &min)
//  {
//    if(count(set) == 1){
//      min = set; //set仅剩一个元素
//    }
//    else{
//      //满足count(set1)>0且count(set2)>0。
//      split(set, &set1, &set2);
//      getMinimum(set1, &min1);
//      getMinimum(set2, &min2);
//      min = getMin(min1, min2);
//  }
//
//分治求解伪代码2（自下向上）：
//
//  //求集合set中元素的个数。
//  count(set);
//  //交换两集合。
//  swap(set1, set2);
//  //将元素e加入到集合set中。
//  set.push(e);
//  //将第i个元素从集合set中取出。
//  set.pop(i);
//  //取两者中的最小值。
//  getMin(x, y);
//  //将集合中元素的最小值保存到min里。
//  minimum(set, &min)
//  {
//    set1 = set;
//    while(count(set1) > 1){
//      for(i = 0; count(set1) > 0; i += 2){
//        if(2 <= count(set1)){
//          set2.push(getMin(set1.pop(i), set1.pop(i+1)));
//        }
//        else{
//          set2.push(set1.pop(i));
//        }
//      }
//      swap(set1, set2);
//    }
//    min = set1; //set仅剩一个元素
//  }
//
//代码实现：
//  代码的实现采用自定义比较方法求取元素，求自定义极值。
//  
//////////////////////////////////////////////////////////////////////

/**
 * 函数功能：根据自定义二选一函数用分治算法中从集合找出符合的元素的下标。
 * 返回值：返回筛选出来元素的下标。
 * method：自定义的二选一函数，函数参数有整数集合，下标1，下标2，返回值
 *         为选择的下标1或下标2。
 * set：整形的数组，存放集合元素。
 * indexLow：整形数组中元素下标的最小值。
 * indexHigh：整形数组中元素下标的最大值。
 */
int LSZ_getExtremumInSet(int (*method)(int set0[], int index1, int index2),
							int set[],
							int indexLow,
							int indexHigh)
{
	if(indexLow < indexHigh){ //元素的个数大于1个
		return method(set, 
				LSZ_getExtremumInSet(method, set, indexLow, (indexLow + indexHigh) / 2),
				LSZ_getExtremumInSet(method, set, (indexLow + indexHigh) / 2 + 1, indexHigh));
	}
	else if(indexLow == indexHigh){ //元素的个数等于1个
		return indexLow;
	}
	return -1; //元素的个数等于或小于0个
}
