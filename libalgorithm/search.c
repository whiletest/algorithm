#include "algorithm.h"

int bsearch(void *arr, int low, int high, bs_cmp_func cmp, void *key)
{
	int relat, mid;

	if (low > high) {
		return -1;
	}

	mid = (high - low) / 2 + low; //·ÀÖ¹Òç³ö

	relat = cmp(arr, mid, key);
	if (relat == 0) {
		return mid;
	}

	if (relat < 0) {
		return bsearch(arr, mid+1, high, cmp, key);
	}

	return bsearch(arr, low, mid-1, cmp, key);
}


//////////////////////////////////////////////////////////////////////////
//²âÊÔ´úÂë
/*
typedef struct {
	int key;
	int udata;
}test_qs_st;

int tqs_cmp(void *arr, int i, void *key)
{
	test_qs_st *tqs = (test_qs_st*)arr;
	int ud = (int)key;

	return (tqs[i].key - ud);
}

int wh;

test_qs_st tqs1[11] = {{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0},{9,0},{10,0},{11,0}};
wh = bsearch(tqs1, 0, 10, tqs_cmp, (void*)2);
printf("%d\n", wh);
*/
