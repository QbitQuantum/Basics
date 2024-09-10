int vthread_join(struct vthread* thread, int* quit_code)
{
#if defined(__WIN32__)
    DWORD res = 0;
#else
    int ret = 0;
#endif

    assert(thread);
    assert(quit_code);

#if defined(__WIN32__)
    res = WaitForSingleObjectEx(thread->thread, INFINITE, FALSE);
    if (WAIT_FAILED == res) return -1;
#else
    ret = pthread_join(thread->thread, NULL);
    retE((ret < 0), -1);
#endif
    *quit_code = thread->quit_code;
    return 0;
}