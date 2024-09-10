int unabto_thread_equal(unabto_thread_t thread1, unabto_thread_t thread2)
{
#ifdef WIN32
    return GetThreadId(thread1) == GetThreadId(thread2);
#else
    return pthread_equal(thread1, thread2);
#endif
}