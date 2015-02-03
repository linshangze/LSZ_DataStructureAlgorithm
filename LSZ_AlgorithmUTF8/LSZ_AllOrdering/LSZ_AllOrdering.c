/*********************************************************************
 * File Name: LSZ_AllOrdering.c
 * Author: linshangze
 * Mail: linshangze163@163.com 
 * Created Time: 2014-01-14-12:51:57 HKT
 ********************************************************************/

//////////////////////////////////////////////////////////////////////
//问题：
//  实现一字符数组全排列输出。
//
//分析：
//  一，{1}的全排列为：
//    1
//  二，{1,2}的全排列为：
//    1,2
//    2,1
//  三，{1,2,3}的全排列为：
//    1,2,3
//    1,3,2
//    2,1,3
//    2,3,1
//    3,1,2
//    3,2,1
//  规律：所有的元素的全排列等于依次用每个元素作为序列首，后面跟剩下
//  元素的全排列。
//
//算法描述：
//  设有元素数组e[n]，共有n个元素，其全排列表示AllOrdering(e[0,...,n-1])。
//  一，当只有一个元素时，全排列的方式只有一种，
//    AllOrdering(e[0])={e[0]};
//  二，当有两个或以上的元素时，
//    AllOrdering(e[0,n-1])={
//      e[0]AllOrdering(e[1,2,...,n-1]),
//      e[1]AllOrdering(e[0,2,...,n-1])
//      ...
//      e[n-1]AllOrdering(e[0,1,...,n-1]);
//    }
//  这是一个递归定义。
//
//////////////////////////////////////////////////////////////////////

int LSZ_AllOrdering(char elements[],
					int begin,
					int end)
{
	int i;
	char temp;

	if(begin == end){
		printf("%s\n", elements);
	}
	else{
		for(i = begin; i <= end; i++){
			//交换。 想不明白，异或运算不支持自己和自己（地址相同）交换。
//			elements[begin] ^= elements[i];
//			elements[i] ^= elements[begin];
//			elements[begin] ^= elements[i];
			temp = elements[i];
			elements[i] = elements[begin];
			elements[begin] = temp;
			LSZ_AllOrdering(elements, begin + 1, end);
			//交换回来，保证不会出现重复排序。
			temp = elements[i];
			elements[i] = elements[begin];
			elements[begin] = temp;
		}
	}
	return 0;
}

//end of file

