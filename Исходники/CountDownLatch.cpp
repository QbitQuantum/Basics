IceUtilInternal::CountDownLatch::CountDownLatch(int count) :
    _count(count)
{
    if(count < 0)
    {
        throw IceUtil::Exception(__FILE__, __LINE__);
    }

#ifdef _WIN32
#   ifndef ICE_OS_WINRT
    _event = CreateEvent(0, TRUE, FALSE, 0);
#   else
    _event = CreateEventExW(0, 0,  CREATE_EVENT_MANUAL_RESET, SEMAPHORE_ALL_ACCESS);
#   endif
    if(_event == 0)
    {
        throw  IceUtil::ThreadSyscallException(__FILE__, __LINE__, GetLastError());
    }
#else
    int rc = pthread_mutex_init(&_mutex, 0);
    if(rc != 0)
    {
        throw IceUtil::ThreadSyscallException(__FILE__, __LINE__, rc);
    }
    
    rc = pthread_cond_init(&_cond, 0);
    if(rc != 0)
    {
        throw IceUtil::ThreadSyscallException(__FILE__, __LINE__, rc);
    }   
#endif
}