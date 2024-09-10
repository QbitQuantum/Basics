bool
IceUtilInternal::Semaphore::timedWait(const IceUtil::Time& timeout) const
{
    IceUtil::Int64 msTimeout = timeout.toMilliSeconds();
    if(msTimeout < 0 || msTimeout > 0x7FFFFFFF)
    {
        throw IceUtil::InvalidTimeoutException(__FILE__, __LINE__, timeout);
    } 

    DWORD rc = WaitForSingleObject(_sem, static_cast<DWORD>(msTimeout));
    if(rc != WAIT_TIMEOUT && rc != WAIT_OBJECT_0)
    {
        throw IceUtil::ThreadSyscallException(__FILE__, __LINE__, GetLastError());
    }
    return rc != WAIT_TIMEOUT;
}