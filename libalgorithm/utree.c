#include "algorithm.h"
#include <string.h>

static void utree_walk_tmp(utree_st *root, utree_cb walk, void *udata)
{
	if (root && walk(root, udata) >= 0) {
		utree_walk_tmp(root->child, walk, udata);
		utree_walk_tmp(root->sibling, walk, udata);
	}
}

void utree_walk(utree_st *root, utree_cb walk, void *udata)
{
	if (walk(root, udata) >= 0) {
		utree_walk_tmp(root->child, walk, udata);
	}
}

static utree_st *utree_search_tmp(utree_st *root, utree_cb cmp, void *udata)
{
	utree_st *p;

	if (!root) {
		return NULL;
	}

	if (cmp(root, udata) == 0) {
		return root;
	} 

	p = utree_search_tmp(root->child, cmp, udata);
	if (p) {
		return p;
	}

	return utree_search_tmp(root->sibling, cmp, udata);
}

utree_st *utree_search(utree_st *root, utree_cb cmp, void *udata)
{
	if (cmp(root, udata) == 0) {
		return root;
	}

	return utree_search_tmp(root->child, cmp, udata);
}

void utree_insert(utree_st **parent, utree_st *node)
{
	if (*parent == NULL) {
		*parent = node;
	} else {
		utree_st *old_child = (*parent)->child;
		if (old_child) {
			old_child->lsibling = node;
		}

		(*parent)->child = node;
		node->parent = *parent;
		node->sibling = old_child;
	}
}

static void utree_del_current(utree_st *node, utree_cb del, void *udata)
{
	utree_st *lsibling, *parent;

	lsibling = node->lsibling;
	parent = node->parent;

	if (node->sibling) {
		node->sibling->lsibling = lsibling;
	}

	if (lsibling) {
		lsibling->sibling = node->sibling;
	} else if (parent) {
		parent->child = node->sibling;
	}

	if (del) {
		del(node, udata);
	}
}

static void utree_del_tmp(utree_st *node, utree_cb del, void *udata)
{
	if (node) {
		utree_del_tmp(node->child, del, udata);
		utree_del_tmp(node->sibling, del, udata);

		utree_del_current(node, del, udata);
	}
}

void utree_delete(utree_st *node, utree_cb del, void *udata)
{
	utree_del_tmp(node->child, del, udata);
	utree_del_current(node, del, udata);
}


//////////////////////////////////////////////////////////////////////////
//µ¥Ôª²âÊÔ´úÂë
//todo...
/*
#include <stdio.h>

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
		utree_insert(&p, &t.utree);\
	}\
} while (0)

int print(utree_st *n, void *udata)
{
	test_utree_st *t;

	t = utree_entry(n, test_utree_st, utree);
	printf("%d ", t->key);
	return 0;
}

void main()
{
	utree_st *root = NULL;
	test_utree_st t[14];
	int i;

	for (i = 0; i < 14; i++)
		test_utree_init(t[i], i);

	utree_insert(&root, &t[0].utree);
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

	utree_walk(root, print, NULL);
	printf("\n");

	utree_walk(&t[8].utree, print, NULL);
	printf("\n");

	utree_st *n = utree_search(root, cmp, (void*)0);
	utree_delete(n, NULL, NULL);
	utree_walk(root, print, NULL);
}
*/
