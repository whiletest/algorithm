#include "algorithm.h"
#include <string.h>

enum {RED, BLACK};

#define RB_INIT(n) do {\
    (n)->lchild = NULL;\
    (n)->rchild = NULL;\
    (n)->color = RED;\
} while (0)

#define RB_IS_RED(n)\
    ((n) != NULL && (n)->color == RED)

#define RB_IS_BLACK(n)\
	((n) == NULL || (n)->color == BLACK)
    
#define RB_GP(n)\
    ((n)->parent->parent)
    
#define RB_SITUATION_1(n, u) do {\
    RB_GP(n)->color = RED;\
    (n)->parent->color = BLACK;\
    (u)->color = BLACK;\
    (n) = RB_GP(n);\
} while (0)

#define RB_SITUATION_2(n) do {\
    (n) = (n)->parent;\
} while (0)

#define RB_SITUATION_3(n) do {\
    (n)->parent->color = BLACK;\
    RB_GP(n)->color = RED;\
} while (0)

static void left_rotate(rb_tree_st **root, rb_tree_st *node)
{
    rb_tree_st *rc = node->rchild;
    node->rchild = rc->lchild;
    
    if (rc->lchild) {
        rc->lchild->parent = node;
    }
    
    rc->parent = node->parent;
    
    if (node->parent == NULL) {
        *root = rc;
    } else if (node->parent->lchild == node) {
        node->parent->lchild = rc;
    } else {
        node->parent->rchild = rc;
    }
    
    rc->lchild = node;
    node->parent = rc;
}

static void right_rotate(rb_tree_st **root, rb_tree_st *node)
{
    rb_tree_st *lc = node->lchild;
    node->lchild = lc->rchild;
    
    if (lc->rchild) {
        lc->rchild->parent = node;
    }
    
    lc->parent = node->parent;
    
    if (node->parent == NULL) {
        *root = lc;
    } else if (node->parent->rchild == node) {
        node->parent->rchild = lc;
    } else {
        node->parent->lchild = lc;
    }
    
    lc->rchild = node;
    node->parent = lc;
}

static void insert_fixup(rb_tree_st **root, rb_tree_st *node)
{
    rb_tree_st *uncle;
    
    while (RB_IS_RED(node->parent)) {
        if (node->parent == RB_GP(node)->lchild) {
            uncle = RB_GP(node)->rchild;
            if (RB_IS_RED(uncle)) {
                RB_SITUATION_1(node, uncle);
            } else if (node == node->parent->rchild) {
                RB_SITUATION_2(node);
                left_rotate(root, node);
            } else {
                RB_SITUATION_3(node);
                right_rotate(root, RB_GP(node));
            }
        } else {
            uncle = RB_GP(node)->lchild;
            if (RB_IS_RED(uncle)) {
                RB_SITUATION_1(node, uncle);
            }  else if (node == node->parent->lchild) {
                RB_SITUATION_2(node);
                right_rotate(root, node);
            } else {
                RB_SITUATION_3(node);
                left_rotate(root, RB_GP(node));
            }
        }
    }
    
    (*root)->color = BLACK;
}

int rb_tree_insert(rb_tree_st **root, rb_tree_st *node, rb_cmp_func cmp)
{
    int ret;
    rb_tree_st *prev = NULL;
    rb_tree_st *cur = *root;
    
    while (cur) {
        prev = cur;
        
        ret = cmp(cur, node);
        if (ret == 0) {
            return -1;
        }
        
        if (ret < 0) {
            cur = cur->rchild;
        } else {
            cur = cur->lchild;
        }
    }
    
    RB_INIT(node);
    node->parent = prev;
    
    if (prev == NULL) {
        *root = node;
    } else if (ret < 0) {
        prev->rchild = node;
    } else {
        prev->lchild = node;
    }
    
    insert_fixup(root, node);
    return 0;
}

int rb_tree_walk(rb_tree_st *root, rb_walk_func walk, void *udata)
{    
    if (root == NULL) {
        return 0;
    }
    
    ASSERT_RET(int, rb_tree_walk(root->lchild, walk, udata), 0);
    ASSERT_RET(int, walk(root, udata), 0);
    return rb_tree_walk(root->rchild, walk, udata);
}

int rb_tree_height(rb_tree_st *root)
{
    int lh, rh;
    
    if (root == NULL) {
        return 0;
    }
    
    lh = rb_tree_height(root->lchild) + 1;
    rh = rb_tree_height(root->rchild) + 1;
    
    return (lh > rh ? lh : rh);
}

static rb_tree_st *rb_tree_min(rb_tree_st *root)
{
    while (root->lchild) {
        root = root->lchild;
    }
    
    return root;
}

static rb_tree_st *rb_tree_max(rb_tree_st *root)
{
    while (root->rchild) {
        root = root->rchild;
    }
    
    return root;
}

static rb_tree_st *rb_tree_successor(rb_tree_st *node)
{
    rb_tree_st *p;
    
    if (node->rchild) {
        return rb_tree_min(node->rchild);
    }
    
    p = node->parent;
    while (p && node == p->rchild) {
        node = p;
        p = p->parent;
    }
    
    return p;
}

static void rb_tree_transplant(rb_tree_st **root, rb_tree_st *dn, rb_tree_st *sn)
{
    if (dn->parent == NULL) {
        *root = sn;
    } else if (dn->parent->lchild == dn) {
        dn->parent->lchild = sn;
    } else {
        dn->parent->rchild = sn;
    }
    
    if (sn) {
        sn->parent = dn->parent;
    }
}

static void delete_fixup(rb_tree_st **root, rb_tree_st *node)
{
	rb_tree_st *w;

	while (node != *root && RB_IS_BLACK(node)) {
		if (node == node->parent->lchild) {
			w = node->parent->rchild;
			if (RB_IS_RED(w)) {
				w->color = BLACK;
				node->parent->color = RED;
				left_rotate(root, node->parent);
			}

			if (RB_IS_BLACK(w->lchild) && RB_IS_BLACK(w->rchild)) {
				w->color = RED;
				node = node->parent;
			} else if (RB_IS_BLACK(w->rchild)) {
				w->lchild->color = BLACK;
				w->color = RED;
				right_rotate(root, w);
				w = node->parent->rchild;
			}
		}
	}

	node->color = BLACK;
}

void rb_tree_delete(rb_tree_st **root, rb_tree_st *node)
{
    rb_tree_st *x, *y;
	int y_ori_is_black;

	y = node;
	y_ori_is_black = RB_IS_BLACK(y);
    
    if (node->lchild == NULL) {
		x = node->rchild;
        rb_tree_transplant(root, node, node->rchild);
    } else if (node->rchild == NULL) {
        x = node->lchild;
		rb_tree_transplant(root, node, node->lchild);
    } else {
        y = rb_tree_successor(node);
        y_ori_is_black = RB_IS_BLACK(y);
		x = y->rchild;

		if (y->parent == node) {
			x->parent = y;	
		} else {
			rb_tree_transplant(root, y, y->rchild);
			y->rchild = node->rchild;
			y->rchild->parent = y;
		}

		rb_tree_transplant(root, node, y);
		y->lchild = node->lchild;
		y->lchild->parent = y;
		y->color = node->color;
    }
    
	if (y_ori_is_black) {
//		delete_fixup(root, x);
	}
}





//////////////////////////////////////////////////////////////////////////
//单元测试代码
/*
#include <stdio.h>
*/
XTEST(rb_tree,)