int uMemUnlock(void *addr, size_t size, sys_call_error_fun fun)
{
#ifdef _WIN32
    if (VirtualUnlock(addr, size) == 0)
    {
       sys_call_error("VirtualUnlock");
       return -1;
    }
    else return 0;
#else
    int res = munlock(addr, size);
    if (res == -1) 
       sys_call_error("munlock");
    return res;
#endif
}