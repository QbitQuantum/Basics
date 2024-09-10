void FNI_InflateObject(JNIEnv *env, jobject wrapped_obj) {
  struct oobj *obj = FNI_UNWRAP_MASKED(wrapped_obj);
  FLEX_MUTEX_LOCK(&global_inflate_mutex);
  /* be careful in case someone inflates this guy while our back is turned */
  if (!FNI_IS_INFLATED(wrapped_obj)) {
    /* all data in inflated_oobj is managed manually, so we can use malloc */
    struct inflated_oobj *infl = 
#if defined(WITH_TRANSACTIONS) && defined(BDW_CONSERVATIVE_GC)
#ifdef WITH_GC_STATS
      GC_malloc_uncollectable_stats
#else
      GC_malloc_uncollectable /* transactions stores version info here */
#endif
#else
	malloc
#endif
      (sizeof(*infl));
#if (!defined(WITH_TRANSACTIONS)) || (!defined(BDW_CONSERVATIVE_GC))
    INCREMENT_MEM_STATS(sizeof(*infl));
#endif
    /* initialize infl */
    memset(infl, 0, sizeof(*infl));
#ifndef WITH_HASHLOCK_SHRINK
    infl->hashcode = HASHCODE_MASK(obj->hashunion.hashcode);
#endif /* !WITH_HASHLOCK_SHRINK */
#if WITH_HEAVY_THREADS || WITH_PTH_THREADS || WITH_USER_THREADS
# ifdef ERROR_CHECKING_LOCKS
    /* error checking locks are slower, but catch more bugs (maybe) */
    { pthread_mutexattr_t attr; pthread_mutexattr_init(&attr);
      pthread_mutexattr_setkind_np(&attr, PTHREAD_MUTEX_ERRORCHECK_NP);
      pthread_mutex_init(&(infl->mutex), &attr);
      pthread_mutexattr_destroy(&attr);
    }
# else /* !ERROR_CHECKING_LOCKS */
    pthread_mutex_init(&(infl->mutex), NULL);
# endif /* ERROR_CHECKING_LOCKS || !ERROR_CHECKING_LOCKS */
    pthread_cond_init(&(infl->cond), NULL);
    pthread_rwlock_init(&(infl->jni_data_lock), NULL);
#endif
#ifndef WITH_HASHLOCK_SHRINK
#ifndef WITH_DYNAMIC_WB
    obj->hashunion.inflated = infl;
#else /* WITH_DYNAMIC_WB */
    obj->hashunion.inflated = (struct inflated_oobj *) 
	((ptroff_t) infl | (obj->hashunion.hashcode & 2));
#endif /* WITH_DYNAMIC_WB */
#else /* WITH_HASHLOCK_SHRINK */
    infl_table_set(INFL_LOCK, obj, infl, NULL);
#endif /* WITH_HASHLOCK_SHRINK */
    assert(FNI_IS_INFLATED(wrapped_obj));
#ifdef WITH_PRECISE_GC 
#if defined(WITH_REALTIME_JAVA) && defined(WITH_NOHEAP_SUPPORT)
    /* Can't inflate a heap reference in a NoHeapRealtimeThread */
    assert((!(((ptroff_t)FNI_UNWRAP(wrapped_obj))&1))||
	   (!((struct FNI_Thread_State*)env)->noheap));
    if (((ptroff_t)FNI_UNWRAP(wrapped_obj))&1)  /* register only if in heap */
#endif
      precise_register_inflated_obj(obj, 
#ifdef WITH_REALTIME_JAVA
				    (void (*)(jobject_unwrapped, ptroff_t))
#endif
				    deflate_object);
#elif defined(BDW_CONSERVATIVE_GC)
    /* register finalizer to deallocate inflated_oobj on gc */
    if (GC_base(obj)!=NULL) {// skip if this is not a heap-allocated object
        GC_register_finalizer_no_order(GC_base(obj), deflate_object,
			      (GC_PTR) ((void*)obj-(void*)GC_base(obj)),
			      &(infl->old_finalizer),
			      &(infl->old_client_data));
    } 
#endif
#ifdef WITH_REALTIME_JAVA
# ifdef BDW_CONSERVATIVE_GC /* XXX this test may be reversed? see v1.29 XXX */
    if (GC_base(obj)!=NULL) /* skip if this is not a heap-allocated object */
# endif /* BDW_CONSERVATIVE_GC */
    RTJ_register_finalizer(wrapped_obj, deflate_object); 
#endif
  }
  FLEX_MUTEX_UNLOCK(&global_inflate_mutex);
}