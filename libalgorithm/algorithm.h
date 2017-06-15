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
	　　const typeof( ((type*)0)->member ) *__mptr=(ptr);\
	  　　(type*)( (char*)__mptr - offsetof(type,member) );})
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

typedef int	 (*cmp_func)(void *arr, int i, int j);
typedef void (*swap_func)(void *arr, int i, int j);

#define SWAP(arr, i, j, type) do {\
	type *uarr = (type*)arr;\
	type tmp = uarr[j];\
	uarr[j] = uarr[i];\
	uarr[i] = tmp;\
} while (0)

//////////////////////////////////////////////////////////////////////////
//快速排序
API void quiksort(void *arr, int low, int high, cmp_func cmp, swap_func swap);


//////////////////////////////////////////////////////////////////////////
//无限制树形结构(一个根节点可能存在任意多的子节点)
//使用左孩子右兄弟结构表示
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
API void utree_insert(utree_st **parent, utree_st *node);
//
API void utree_delete(utree_st *node, utree_cb del, void *udata);


//////////////////////////////////////////////////////////////////////////
//堆排序
API void heapsort(void *arr, int len, cmp_func cmp, swap_func swap);

//////////////////////////////////////////////////////////////////////////
//优先队列
/*********************************************************************************
  *Func:	pquequed
  *Desc:	将一段已经在数组中的元素构造为优先队列	
  *Param:	pque,待构造的数据段首地址  
  *Param:	pqlen,有效数据的长度
  *Param:	cmp,自定义的比较函数
  *Param:	swap,自定义的数据交换函数
  *Return:  
  *Others:  功能等效于多次调用enpqueue函数
**********************************************************************************/
API void pquequed(void *pque, int pqlen, cmp_func cmp, swap_func swap);
/*********************************************************************************
  *Func:
  *Desc:	
  *Input:	
  *Output:  
  *Return:  
  *Others:  
**********************************************************************************/
API void enpqueue(void *pque, int *pqlen, cmp_func cmp, swap_func swap);
/*********************************************************************************
  *Func:
  *Desc:	
  *Input:	
  *Output:  
  *Return:  
  *Others:  
**********************************************************************************/
API int depqueue(void *pque, int *pqlen, cmp_func cmp, swap_func swap);

#endif
