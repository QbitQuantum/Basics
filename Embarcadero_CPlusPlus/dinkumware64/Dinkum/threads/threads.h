/* threads.h -- header for threads library */
#ifndef _THREADS_THREADS_H
#define _THREADS_THREADS_H
#include <Dinkum/threads/xthreads.h>


_C_LIB_DECL
enum {	/* return codes */
	thrd_success = _Thrd_success,
	thrd_nomem = _Thrd_nomem,
	thrd_timedout = _Thrd_timedout,
	thrd_busy = _Thrd_busy,
	thrd_error = _Thrd_error
	};

	/* threads */
typedef _Thrd_t thrd_t;
typedef _Thrd_start_t thrd_start_t;

 #if _HAS_STRICT_LINKAGE
 #ifdef __cplusplus
extern "C++" {	// C++ linkage
typedef int (*_Thrd_start_cpp_t)(void *);

inline int thrd_create(thrd_t *_Thrd, _Thrd_start_cpp_t _Fp, void *_Arg)
	{	/* create thread */
	return (_Thrd_create(_Thrd, (thrd_start_t)_Fp, _Arg));
	}
}	// extern "C++"

 #else /* defined(__cplusplus) */
#define thrd_create(thr, fun, arg)	_Thrd_create(thr, fun, arg)
 #endif /* defined(__cplusplus) */

 #else /* _HAS_STRICT_LINKAGE */
#define thrd_create(thr, fun, arg)	_Thrd_create(thr, fun, arg)
 #endif /* _HAS_STRICT_LINKAGE */

#define thrd_detach(thr)		_Thrd_detach(thr)
#define thrd_exit(code)			_Thrd_exit(code)
#define thrd_join(thr, res)		_Thrd_join(thr, res)
#define thrd_sleep(tm, pleft)			_Thrd_sleep(tm, pleft)
#define thrd_yield				_Thrd_yield
#define thrd_equal(thr0, thr1)	_Thrd_equal(thr0, thr1)
#define thrd_current			_Thrd_current

	/* mutexes */
typedef _Mtx_imp_t mtx_t;
enum {	/* mutex types */
	mtx_plain = _Mtx_plain,
	mtx_try = _Mtx_try,
	mtx_timed = _Mtx_timed,
	mtx_recursive = _Mtx_recursive
	};

#define mtx_init(mtx, typ)		_Mtx_init(mtx, typ)
#define mtx_destroy(mtx)		_Mtx_destroy(_THR_NOINDIR(mtx))
#define mtx_current_owns(mtx)	_Mtx_current_owns(_THR_NOINDIR(mtx))
#define mtx_lock(mtx)			_Mtx_lock(_THR_NOINDIR(mtx))
#define mtx_trylock(mtx)		_Mtx_trylock(_THR_NOINDIR(mtx))
#define mtx_timedlock(mtx, tm)	_Mtx_timedlock(_THR_NOINDIR(mtx), tm)
#define mtx_unlock(mtx)			_Mtx_unlock(_THR_NOINDIR(mtx))

	/* condition variables */
typedef _Cnd_t cnd_t;

#define cnd_init(cnd)			_Cnd_init(cnd)
#define cnd_destroy(cnd)		_Cnd_destroy(_THR_NOINDIR(cnd))
#define cnd_timedwait(cnd, mtx, tm) \
	_Cnd_timedwait(_THR_NOINDIR(cnd), _THR_NOINDIR(mtx), tm)
#define cnd_wait(cnd, mtx) \
	_Cnd_wait(_THR_NOINDIR(cnd), _THR_NOINDIR(mtx))
#define cnd_broadcast(cnd)		_Cnd_broadcast(_THR_NOINDIR(cnd))
#define cnd_broadcast_at_thread_exit(cnd, mtx) \
	_Cnd_register_at_thread_exit(_THR_NOINDIR(cnd), _THR_NOINDIR(mtx), 0)
#define cnd_signal(cnd)			_Cnd_signal(_THR_NOINDIR(cnd))

	/* thread specific storage */
typedef _Tss_t tss_t;
typedef _Tss_dtor_t tss_dtor_t;
#define TSS_DTOR_ITERATIONS	_TSS_DTOR_ITERATIONS

#define tss_create(key, dtor)	_Tss_create(key, dtor)
#define tss_delete(key)			_Tss_delete(key)
#define tss_set(key, value)		_Tss_set(key, value)
#define tss_get(key)			_Tss_get(key)

	/* once functions */
#define ONCE_FLAG_INIT			_ONCE_FLAG_INIT
typedef _Once_flag				once_flag;
typedef _Once_callback_t		once_callback_t;
#define call_once(flg, once)	_Call_once(flg, once)

	/* utility functions */
#define thread_abort	_Thread_abort

_END_C_LIB_DECL
#endif	/* _THREADS_THREADS_H */

/*
 * This file is derived from software bearing the following
 * restrictions:
 *
 * (c) Copyright William E. Kempf 2001
 *
 * Permission to use, copy, modify, distribute and sell this
 * software and its documentation for any purpose is hereby
 * granted without fee, provided that the above copyright
 * notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting
 * documentation. William E. Kempf makes no representations
 * about the suitability of this software for any purpose.
 * It is provided "as is" without express or implied warranty.
 */

/*
 * Copyright (c) by P.J. Plauger. All rights reserved.
 * Consult your license regarding permissions and restrictions.
V8.03a/17:1422 */
