/*  alloc.h

    memory management functions and variables.

*/

/*
 *      C/C++ Run Time Library - Version 28.0
 *
 *      Copyright (c) 2000, 2021 by Embarcadero Technologies, Inc.
 *      All Rights Reserved.
 *
 */


/* $Revision: 33819 $ */

#if !defined(__ALLOC_H)
#define __ALLOC_H

#include <_stddef.h>

#if !defined(RC_INVOKED)

#if defined(__STDC__)
#pragma warn -nak
#endif

#endif  /* !RC_INVOKED */

#ifdef __cplusplus
namespace std {
#endif

#if !defined(__STDC__)
struct heapinfo
{
  void *    ptr;
  void *    ptr2;
  unsigned  size;
  int       in_use;
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

void *   _RTLENTRY _EXPFUNC calloc(_SIZE_T __nitems, _SIZE_T __size);
void     _RTLENTRY _EXPFUNC free(void * __block);
void *   _RTLENTRY _EXPFUNC malloc(_SIZE_T  __size);
void *   _RTLENTRY _EXPFUNC realloc(void * __block, _SIZE_T __size);

#if !defined(_WIN64)
int      _RTLENTRY _EXPFUNC heapcheck(void);
int      _RTLENTRY _EXPFUNC heapfillfree(unsigned int __fillvalue);
int      _RTLENTRY _EXPFUNC heapcheckfree(unsigned int __fillvalue);
int      _RTLENTRY _EXPFUNC heapchecknode(void *__node);
int      _RTLENTRY _EXPFUNC heapwalk(struct heapinfo *__hi);
#endif

void *   _RTLENTRY _EXPFUNC _aligned_malloc(_SIZE_T __size, _SIZE_T __alignment);
void     _RTLENTRY _EXPFUNC _aligned_free(void * __block);

#ifdef __cplusplus
}
#endif

/* Values returned by heap??? and _heap??? functions */

#define _HEAPEMPTY      1
#define _HEAPOK         2
#define _FREEENTRY      3
#define _USEDENTRY      4
#define _HEAPEND        5
#define _HEAPCORRUPT    -1
#define _BADNODE        -2
#define _BADVALUE       -3
#define _HEAPBADBEGIN   -4
#define _HEAPBADNODE    -5
#define _HEAPBADPTR     -6

#if !defined(RC_INVOKED)

#if defined(__STDC__)
#pragma warn .nak
#endif

#endif  /* !RC_INVOKED */

#ifdef __cplusplus
} // std
#endif

#endif  /* __ALLOC_H */


#if defined(__cplusplus) && !defined(__USING_CNAME__) && !defined(__ALLOC_H_USING_LIST)
#define __ALLOC_H_USING_LIST
    using std::calloc;
    using std::free;
    using std::malloc;
    using std::realloc;
#if !defined(__STDC__)
    using std::heapinfo;
#endif
#if !defined(_WIN64)
    using std::heapcheck;
    using std::heapfillfree;
    using std::heapcheckfree;
    using std::heapchecknode;
    using std::heapwalk;
#endif
    using std::_aligned_malloc;
    using std::_aligned_free;
#endif /* __USING_CNAME__ */
