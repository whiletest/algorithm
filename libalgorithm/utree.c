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
	utree_st *p;

	if (cmp(root, udata) == 0) {
		return root;
	}

	return utree_search_tmp(root->child, cmp, udata);
}

void utree_insert(utree_st *parent, utree_st *node)
{
	utree_st *old_child = parent->child;
	if (old_child) {
		old_child->lsibling = node;
	}

	parent->child = node;
	node->parent = parent;
	node->sibling = old_child;
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
