/*********************************************************************
 * File Name: LSZ_SortQuick.c
 * Author: linshangze
 * Mail: linshangze163@163.com 
 * Created Time: 2013-12-30-08:15:10 HKT
 ********************************************************************/

#include <stdio.h>

void LSZ_sort_quickSwap(int *e1,
						int *e2)
{
	int e3;
	e3 = *e1;
	*e1 = *e2;
	*e2 = e3;
}

/**
 * begin - end：大于0，即调用这函数时，元素至少两个。
 */
int LSZ_sort_quickPartition(int array[],
							int begin,
							int end)
{
	int low = begin, high = end + 1; //为了下面的操作，high先加1
	int key = array[begin];

	while(1){
		while(++low < end && array[low] < key){ //和第二个数开始比较，key就是第一个数。
			; //循环结束，array[low]>=key。或begin~end-1的元素<key，low=end。high==end+1。
		}
		while(array[--high] > key){
			; //循环结束，array[high]<=key。或begin+1~end元素>key，low=begin+1，high=begin。
		}
		if(low >= high){
			break;
		}
		printf("low=%d,high=%d,array[low]=%d,array[high]=%d,key=%d\n", low, high, array[low], array[high], key);
		//经过这步操作，array[low]=<key，array[high]>=key。
		LSZ_sort_quickSwap(array + low, array + high);
	}
	if(array[low] < key){ //需要调整key。
		//交换前key(begin)<=low<=high。
		//交换后low(begin)<=key<=high。
		array[begin] = array[low];
		array[low] = key;
	}
	printf("return=%d\n", low);
	return low;
}

int partitionCompare(int a[],
						int p,
						int r)
{
	int i = p, j = r + 1;
	int x = a[p];

	while(1){
		while(a[++i] < x && i < r);
		while(a[--j] > x);
		if(i >= j)break;
		printf("low=%d,high=%d,a[low]=%d,a[high]=%d,key=%d\n", i, j, a[i], a[j], x);
		LSZ_sort_quickSwap(a + i, a + j);
	}
	a[p] = a[j];
	a[j] = x;
	printf("return=%d\n", j);
	return j;
}

void LSZ_sort_quick(int array[],
					int begin,
					int end)
{
	int division;
	if(begin < end){ //至少有两个元素。
		//分割数组。
//		division = LSZ_sort_quickPartition(array, begin, end);
		division = partitionCompare(array, begin, end);
		//排序前半部。
		LSZ_sort_quick(array, begin, division - 1);
		//排序后半部。
		LSZ_sort_quick(array, division + 1, end);
	}
}

//end of file

