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

typedef int	 (*cmp_func)(void *arr, int i, int j);
typedef void (*swap_func)(void *arr, int i, int j);

#define SWAP(arr, i, j, type) do {\
	type *uarr = (type*)arr;\
	type tmp = uarr[j];\
	uarr[j] = uarr[i];\
	uarr[i] = tmp;\
} while (0)

//////////////////////////////////////////////////////////////////////////
//��������
API void quiksort(void *arr, int low, int high, cmp_func cmp, swap_func swap);


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
API void utree_insert(utree_st **parent, utree_st *node);
//
API void utree_delete(utree_st *node, utree_cb del, void *udata);


//////////////////////////////////////////////////////////////////////////
//������
API void heapsort(void *arr, int len, cmp_func cmp, swap_func swap);

//////////////////////////////////////////////////////////////////////////
//���ȶ���
/*********************************************************************************
  *Func:	pquequed
  *Desc:	��һ���Ѿ��������е�Ԫ�ع���Ϊ���ȶ���	
  *Param:	pque,����������ݶ��׵�ַ  
  *Param:	pqlen,��Ч���ݵĳ���
  *Param:	cmp,�Զ���ıȽϺ���
  *Param:	swap,�Զ�������ݽ�������
  *Return:  
  *Others:  ���ܵ�Ч�ڶ�ε���enpqueue����
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
