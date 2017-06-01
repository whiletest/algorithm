#ifndef __ALGORITHM__
#define __ALGORITHM__

//////////////////////////////////////////////////////////////////////////
//
typedef unsigned int  uint;
/*
#ifndef offsetof
#define offsetof(TYPE,MEMBER) ((size_t)&((TYPE *)0)->MEMBER)
#endif

#ifndef container_of
#define container_of(ptr,type,member) ({\
	����const typeof( ((type*)0)->member ) *__mptr=(ptr);\
	  ����(type*)( (char*)__mptr - offsetof(type,member) );})
#endif
*/

#ifndef container_of
#define container_of(ptr, type, member)\
	((type *)((char *)(ptr) - (unsigned long)(&((type *)0)->member)))
#endif

#ifdef _MSC_VER
#define _API __declspec(dllexport)
#else
#define _API
#endif

#ifdef __cplusplus
#define API extern "C" _API
#else
#define API _API
#endif


//////////////////////////////////////////////////////////////////////////
typedef int (*cmp_func)(void *l, void *r);


//////////////////////////////////////////////////////////////////////////
//���������νṹ(һ�����ڵ���ܴ����������ӽڵ�)
//ʹ���������ֵܽṹ��ʾ
struct utree_st {
	struct utree_st *parent;
	struct utree_st *child;
	struct utree_st *sibling;
	struct utree_st *lsibling; //left sibling
};
typedef struct utree_st utree_st;
typedef int (*utree_cb)(utree_st *node, void *udata);
//
#define utree_init(root) do {\
	(root)->parent = NULL;\
	(root)->child = NULL;\
	(root)->sibling = NULL;\
	(root)->lsibling = NULL;\
} while (0)
//
#define utree_entry(ptr, type, member) container_of(ptr, type, member)
//
API void utree_walk(utree_st *node, utree_cb fun, void *udata);
//
API utree_st *utree_search(utree_st *root, utree_cb fun, void *udata);
//
API void utree_insert(utree_st *parent, utree_st *node);
//
API void utree_delete(utree_st *node, utree_cb del, void *udata);

#endif