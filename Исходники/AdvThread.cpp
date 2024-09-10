bool CAdvThread::setAffinity()
{
#ifdef Q_OS_LINUX
    if(threadHandle != 0)
    {
        int j;
        for (j = 0; j < coreQuantity; j++)
            if(affinityData.coreMask & (1<<j))
                CPU_SET(j, &cpuset);
        pthread_setaffinity_np(threadHandle, sizeof(cpu_set_t), &cpuset);
    }
#else
    if(threadHandle != 0)
    {
        DWORD_PTR res = SetThreadAffinityMask(threadHandle, affinityData.coreMask);
        if (0 == res)
        {
         // failure
        }
    }
#endif

     affinityData.coreChanged = 0;
}