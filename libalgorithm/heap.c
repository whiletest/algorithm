#include "algorithm.h"

#define N2I(i)		((i) - 1)		//节点位置转换为下标位置
#define I2N(i)		((i) + 1)		//下标位置转换为节点位置
#define PARENT(i)	((i)/2)			//双亲节点，i为节点位置
#define LEFT(i)		(2*(i))			//左孩子节点，i为节点位置
#define RIGHT(i)	(2*(i) + 1)		//右孩子节点，i为节点位置
#define MAX(arr, i, j, cmp)\
	((cmp(arr, i, j) > 0)?(i):(j))	//i,j为下标位置

static void heapify(void *arr, int len, int i, cmp_func cmp, swap_func swap)
{
	int largest = i;

	if (LEFT(i) <= len) {
		largest = I2N(MAX(arr, N2I(i), N2I(LEFT(i)), cmp));
	}

	if (RIGHT(i) <= len) {
		largest = I2N(MAX(arr, N2I(largest), N2I(RIGHT(i)), cmp));
	}

	if (largest != i) {
		swap(arr, N2I(i), N2I(largest));
		heapify(arr, len, largest, cmp, swap);
	}
}

static void build_heap(void *arr, int len, cmp_func cmp, swap_func swap)
{
	int i;
	
	for (i = len/2; i > 0; i--) {
		heapify(arr, len, i, cmp, swap);
	}
}

void heapsort(void *arr, int len, cmp_func cmp, swap_func swap)
{
	int i;

	build_heap(arr, len, cmp, swap);

	for (i = len; i > 1; i--) {
		swap(arr, N2I(1), N2I(i));
		heapify(arr, i - 1, 1, cmp, swap);
	}
}

void pquequed(void *pque, int pqlen, cmp_func cmp, swap_func swap)
{
	build_heap(pque, pqlen, cmp, swap);
}

void enpqueue(void *pque, int *pqlen, cmp_func cmp, swap_func swap)
{
	int i;
	
	i = ++*pqlen;

	while (i > 1 && cmp(pque, N2I(PARENT(i)), N2I(i)) < 0) {
		swap(pque, N2I(PARENT(i)), N2I(i));
		i = PARENT(i);
	}
}

int depqueue(void *pque, int *pqlen, cmp_func cmp, swap_func swap)
{
	int len = *pqlen;

	if (len < 1) {
		return -1;
	}

	if (len > 1) {
		swap(pque, N2I(1), N2I(len));
		heapify(pque, len-1, 1, cmp, swap);
	}

	return (--*pqlen);
}

//////////////////////////////////////////////////////////////////////////
//对排序测试代码
/*
typedef struct {
	int key;
	int udata;
}test_qs_st;

int tqs_cmp(void *arr, int i, int j)
{
	test_qs_st *tqs = (test_qs_st*)arr;

	if (i == j || tqs[i].key == tqs[j].key)
		return 0;
	return (tqs[i].key > tqs[j].key?-1:1);
}

void tqs_swap(void *arr, int i, int j)
{
	if (i != j) {
		SWAP(arr, i, j, test_qs_st);
	}
}

void print(test_qs_st *tqs, int len)
{
	int i;
	for (i = 0; i < len; i++) {
		printf("%d ", tqs[i].key);
	}
}

test_qs_st tqs[10] = {{10,0},{9,0},{8,0},{7,0},{6,0},{5,0},{4,0},{3,0},{2,0},{1,0}};
heapsort(tqs, 10, tqs_cmp, tqs_swap);
print(tqs, 10);
printf("\n");

test_qs_st tqs1[11] = {{13,0},{19,0},{5,0},{12,0},{8,0},{7,0},{4,0},{21,0},{2,0},{6,0},{11,0}};
heapsort(tqs1, 11, tqs_cmp, tqs_swap);
print(tqs1, 11);

int i;
int pqlen = 3;
test_qs_st tqs2[11] = {{13,0},{19,0},{5,0},{12,0},{8,0},{7,0},{4,0},{21,0},{2,0},{6,0},{11,0}};

pquequed(tqs2, pqlen, tqs_cmp, tqs_swap);
for (i = 0; i< 5; i++)
enpqueue(tqs2, &pqlen, tqs_cmp, tqs_swap);
while (pqlen > 0) {
i = depqueue(tqs2, &pqlen, tqs_cmp, tqs_swap);
printf("%d ", tqs2[i].key);
}
*/
