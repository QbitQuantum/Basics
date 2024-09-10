bool recursive_mutex::scoped_lock::internal_try_acquire( recursive_mutex& m ) {
#if _WIN32||_WIN64
    switch( m.state ) {
      case INITIALIZED:
        break;
      case DESTROYED:
        __TBB_ASSERT(false,"recursive_mutex::scoped_lock: mutex already destroyed");
        break;
      default:
        __TBB_ASSERT(false,"recursive_mutex::scoped_lock: illegal mutex state");
        break;
    }
#endif /* _WIN32||_WIN64 */
    bool result;
#if _WIN32||_WIN64
    result = TryEnterCriticalSection(&m.impl)!=0;
#else
    result = pthread_mutex_trylock(&m.impl)==0;
#endif /* _WIN32||_WIN64 */
    if( result )
        my_mutex = &m;
    return result;
}