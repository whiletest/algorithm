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

typedef struct {
	int key;
	utree_st utree;
}test_utree_st;

#define test_utree_init(t, val) do {\
	t.key = val;\
	utree_init(&t.utree);\
} while (0)

int cmp(utree_st *n, void *udata)
{
	test_utree_st *t;
	
	t = utree_entry(n, test_utree_st, utree);
	return (t->key - (int)udata);
}

#define test_utree_insert(root, t, key) do {\
	utree_st *p = utree_search(&root.utree, cmp, (void*)key);\
	if (p) {\
		utree_insert(p, &t.utree);\
	}\
} while (0)

int print(utree_st *n, void *udata)
{
	test_utree_st *t;
	
	t = utree_entry(n, test_utree_st, utree);
	printf("%d ", t->key);
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{/*
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

	int arr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14};
	test_utree_st t[14];

	for (int i = 0; i < 14; i++)
		test_utree_init(t[i], i);
	
	test_utree_insert(t[0], t[3], 0);
	test_utree_insert(t[0], t[2], 0);
	test_utree_insert(t[0], t[1], 0);

	test_utree_insert(t[0], t[5], 1);
	test_utree_insert(t[0], t[4], 1);

	test_utree_insert(t[0], t[9], 2);
	test_utree_insert(t[0], t[8], 2);
	test_utree_insert(t[0], t[7], 2);
	test_utree_insert(t[0], t[6], 2);

	test_utree_insert(t[0], t[10], 3);

	test_utree_insert(t[0], t[11], 5);

	test_utree_insert(t[0], t[13], 8);
	test_utree_insert(t[0], t[12], 8);

	utree_walk(&t[0].utree, print, NULL);
	printf("\n");

	utree_walk(&t[8].utree, print, NULL);
	printf("\n");

	utree_st *n = utree_search(&t[0].utree, cmp, (void*)0);
	utree_delete(n, NULL, NULL);
	utree_walk(&t[0].utree, print, NULL);


	getchar();
	return 0;
}

