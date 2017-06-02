// algorithm.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "../libalgorithm/algorithm.h"
/*
//最大子组问题
int find_max_cross_subarray(int a[], int *low, int *high)
{
	int mid, i;
	int sum, lsum, rsum, lidx, ridx;

	mid = (*low + *high) / 2;
	
	sum = 0;
	lsum = 0x80000000;
	for (i = mid; i >= *low; i--) {
		sum	+= a[i];
		if (sum > lsum) {
			lsum = sum;
			lidx = i;
		}
	}

	sum = 0;
	rsum = 0x80000000;
	for (i = mid + 1; i <= *high; i++) {
		sum += a[i];
		if (sum > rsum) {
			rsum = sum;
			ridx = i;
		}
	}

	*low = lidx;
	*high = ridx;
	return (lsum + rsum);
}

int find_maximum_subarray(int a[], int *low, int *high)
{
	int mid, llow, lhigh, rlow, rhigh, clow, chigh;
	int rsum, lsum, csum;

	if (*high == *low) {
		return a[*high];
	}

	mid = (*low + *high) / 2;
	
	llow = *low;
	lhigh = mid;
	lsum = find_maximum_subarray(a, &llow, &lhigh);
	printf("left low:%d high:%d sum:%d\n", llow, lhigh, lsum);
	
	rlow = mid + 1;
	rhigh = *high;
	rsum = find_maximum_subarray(a, &rlow, &rhigh);
	printf("right low:%d high:%d sum:%d\n", rlow, rhigh, rsum);

	clow = *low;
	chigh = *high;
	csum = find_max_cross_subarray(a, &clow, &chigh);
	printf("cross low:%d high:%d sum:%d\n", clow, chigh, csum);

	if (lsum >= rsum && lsum >= csum) {
		*low = llow;
		*high = lhigh;
		return lsum;
	}

	if (rsum >= lsum && rsum >= csum) {
		*low = rlow;
		*high = rhigh;
		return rsum;
	}

	*low = clow;
	*high = chigh;
	return csum;
}

void find_maximum_subarray2(int a[], int len)
{
	int i, j, sum;
	int maxsum, maxlow, maxhigh;

	maxlow = maxhigh = 0;
	maxsum = a[0];

	for (j = 1; j < len; j++) {
		sum = 0;
		for (i = j; i >= 0; i--) {
			sum += a[i];
			if (sum > maxsum) {
				maxsum = sum;
				maxlow = i;
				maxhigh = j;
			}
		}
	}

	printf("maximum array from %d to %d, sum:%d\n", maxlow, maxhigh, maxsum);
}

void find_maximum_subarray3(int *arr, int len)  
{  
	int i;
	int low = 0, high = 0, tlow = 0;
	int MaxSum = 0;  
	int CurSum = 0;  

	for(i=0;i<len;i++) {  
		CurSum += arr[i];  
		if(CurSum > MaxSum) {  
			MaxSum = CurSum;
			low = tlow;
			high = i;
		}
		//如果累加和出现小于0的情况，  
		//则和最大的子序列肯定不可能包含前面的元素，  
		//这时将累加和置0，从下个元素重新开始累加  
		if(CurSum < 0) {  
			tlow = i + 1;
			CurSum = 0; 
		}
	}

	printf("maximum array from %d to %d, sum:%d\n", low, high, MaxSum);  
} 
*/

int _tmain(int argc, _TCHAR* argv[])
{
/* 最大子数组测试用例
	int low, high, sum;
	int a[] = {13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7};

	low = 0;
	high = 15;
	sum = find_maximum_subarray(a, &low, &high);
	printf("maximum array from %d to %d, sum:%d\n", low, high, sum);
*/
/*
	int a[] = {13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7};
	find_maximum_subarray2(a, 16);
	find_maximum_subarray3(a, 16);
*/

	getchar();
	return 0;
}

