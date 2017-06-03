#include "algorithm.h"

static int partition(void *arr, int low, int high, cmp_func cmp, swap_func swap)
{
	int i, j;
	
	i = low - 1;

	for (j = low; j < high; j++) {
		if (cmp(arr, j, high) <= 0) {
			i++;
			swap(arr, i, j);
		}
	}

	swap(arr, i + 1, high);
	return (i + 1);
}

void quiksort(void *arr, int low, int high, cmp_func cmp, swap_func swap)
{
	if (low < high) {
		int p = partition(arr, low, high, cmp, swap);
		quiksort(arr, low, p - 1, cmp, swap);
		quiksort(arr, p + 1, high, cmp, swap);
	}
}

//////////////////////////////////////////////////////////////////////////
//µ¥Ôª²âÊÔ´úÂë
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
	return (tqs[i].key > tqs[j].key?1:-1);
}

void tqs_swap(void *arr, int i, int j)
{
	SWAP(arr, i, j, test_qs_st);
}

void print(test_qs_st *tqs, int len)
{
	int i;
	for (i = 0; i < len; i++) {
		printf("%d ", tqs[i].key);
	}
}

test_qs_st tqs[10] = {{10,0},{9,0},{8,0},{7,0},{6,0},{5,0},{4,0},{3,0},{2,0},{1,0}};
quiksort(tqs, 0, 9, tqs_cmp, tqs_swap);
print(tqs, 10);
printf("\n");

test_qs_st tqs1[11] = {{13,0},{19,0},{5,0},{12,0},{8,0},{7,0},{4,0},{21,0},{2,0},{6,0},{11,0}};
quiksort(tqs1, 0, 10, tqs_cmp, tqs_swap);
print(tqs1, 11);
*/
