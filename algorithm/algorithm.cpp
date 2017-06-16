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
#include "../libalgorithm/xtest.h"

typedef struct {
	int key;
	rb_tree_st rb_tree;
	int udata;
}rb_test_st;

typedef struct {
	int kseq[64];
	int cur;
}rb_chk_st;

int rb_my_cmp(rb_tree_st *l, rb_tree_st *r)
{
	rb_test_st *lt = rb_entry(l, rb_test_st, rb_tree);
	rb_test_st *rt = rb_entry(r, rb_test_st, rb_tree);

	return (lt->key - rt->key);
}

int xtest_check1(rb_tree_st *n, void *udata)
{
	rb_test_st *t = rb_entry(n, rb_test_st, rb_tree);
	rb_chk_st *chk = (rb_chk_st *)udata;

	EXPECT_EQ(t->key, chk->kseq[chk->cur]);
	chk->cur++;

	return 0;
}

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
	int i;
	rb_tree_st *root = NULL;
	rb_test_st t[10];
	rb_chk_st chk1;

	t[0].key = 1;
	t[1].key = 2;
	t[2].key = 4;

	for (i = 0; i < 3; i++) {
		rb_tree_insert(&root, &t[i].rb_tree, rb_my_cmp);
	}

	EXPECT_EQ(rb_tree_height(root), 2);

	chk1.cur = 0;
	chk1.kseq[0] = 1; chk1.kseq[1] = 2; chk1.kseq[2] = 4;
	rb_tree_walk(root, xtest_check1, (void*)&chk1);

	t[3].key = 5; t[4].key = 7; t[5].key = 8;
	t[6].key = 11; t[7].key = 14; t[8].key = 15;
	for (i = 3; i < 9; i++) {
		rb_tree_insert(&root, &t[i].rb_tree, rb_my_cmp);
	}

	chk1.kseq[3] = 5; chk1.kseq[4] = 7; chk1.kseq[5] = 8;
	chk1.kseq[6] = 11; chk1.kseq[7] = 14; chk1.kseq[8] = 15;
	EXPECT_EQ(rb_tree_height(root), 4);

	chk1.cur = 0;
	rb_tree_walk(root, xtest_check1, (void*)&chk1);

	return 0;
}

