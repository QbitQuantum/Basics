int ThreadGetPriority(void* Thread)
{
	int v = GetThreadPriority(Thread);
#if defined(TARGET_WINCE)
	v = v - THREAD_PRIORITY_NORMAL;
#else
	v = THREAD_PRIORITY_NORMAL - v;
#endif
    if (v>1)
        return MULTITHREAD_PRIORITY_IDLE;
    if (v==1)
        return MULTITHREAD_PRIORITY_LOW;
    if (v==0)
        return MULTITHREAD_PRIORITY_NORMAL;
    if (v==-1)
        return MULTITHREAD_PRIORITY_USERINPUT;
    return MULTITHREAD_PRIORITY_HIGH;
}