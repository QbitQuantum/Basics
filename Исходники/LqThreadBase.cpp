void* LqThreadBase::BeginThreadHelper(void* ProcData)
#endif
{
    LqThreadBase* This = (LqThreadBase*)ProcData;

    This->IsStarted = true;
    This->StartThreadLocker.LockWrite();
    
    //
#if defined(LQPLATFORM_WINDOWS)
    pthread_setname_np(This->ThreadId(), This->Name);
#elif defined(LQPLATFORM_LINUX) || defined(LQPLATFORM_ANDROID)
    pthread_setname_np(pthread_self(), This->Name);
#elif defined(LQPLATFORM_FREEBSD)
    pthread_setname_np(pthread_self(), This->Name, nullptr);
#elif defined(LQPLATFORM_APPLE)
    pthread_setname_np(This->Name);
#endif

    if(This->Priority == LQTHREAD_PRIOR_NONE) {
#if defined(LQPLATFORM_WINDOWS)
        This->Priority = __GetPrior(GetThreadPriority(GetCurrentThread()));
#else
        sched_param schedparams;
        pthread_getschedparam(pthread_self(), LqDfltPtr(), &schedparams);
        This->Priority = __GetPrior(schedparams.sched_priority);
#endif
    } else {
#if defined(LQPLATFORM_WINDOWS)
        SetThreadPriority(GetCurrentThread(), __GetRealPrior(This->Priority));
#else
        sched_param schedparams;
        schedparams.sched_priority = __GetRealPrior(This->Priority);
        pthread_setschedparam(pthread_self(), SCHED_OTHER, &schedparams);
#endif
    }


    if(This->AffinMask == 0) {
#if defined(LQPLATFORM_WINDOWS)
        GROUP_AFFINITY ga = {0};
        GetThreadGroupAffinity(GetCurrentThread(), &ga);
        This->AffinMask = ga.Mask;
#elif !defined(LQPLATFORM_ANDROID)
        pthread_getaffinity_np(pthread_self(), sizeof(This->AffinMask), (cpu_set_t*)&This->AffinMask);
#endif
    } else {
#if defined(LQPLATFORM_WINDOWS)
        SetThreadAffinityMask(GetCurrentThread(), This->AffinMask);
#elif !defined(LQPLATFORM_ANDROID)
        pthread_setaffinity_np(pthread_self(), sizeof(This->AffinMask), (const cpu_set_t*)&This->AffinMask);
#endif
    }
    This->StartThreadLocker.UnlockWrite();

    This->EnterHandler(This->UserData); //Call user defined handler

    //Enter main func
    This->BeginThread();


#ifdef LQPLATFORM_WINDOWS
    if(NameThread != nullptr) {
        free(NameThread);
        NameThread = nullptr;
    }
#endif

    This->ExitHandler(This->UserData);

    This->StartThreadLocker.LockWrite();
#ifdef LQPLATFORM_WINDOWS
    CloseHandle((HANDLE)This->ThreadHandler);
#endif
    This->CurThreadId = -((intptr_t)1);
    This->ThreadHandler = 0;
    This->StartThreadLocker.UnlockWrite();
#ifdef LQPLATFORM_WINDOWS
    return 0;
#else
    return NULL;
#endif
}