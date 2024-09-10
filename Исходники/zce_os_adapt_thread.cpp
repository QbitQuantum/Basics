//退出一个线程，可以得到返回值
void ZCE_OS::pthread_exit(ZCE_THR_FUNC_RETURN thr_ret)
{
#if defined (ZCE_OS_WINDOWS)
    return _endthreadex(thr_ret);

#elif defined (ZCE_OS_LINUX)
    return ::pthread_exit (thr_ret);
#endif //#if defined (ZCE_OS_LINUX)
}