HRESULT
ServerRemoteCodeGen(
    /* [in] */ handle_t binding,
    /* [in] */ intptr_t scriptContextInfoAddress,
    /* [in] */ __RPC__in CodeGenWorkItemIDL *workItemData,
    /* [out] */ __RPC__out JITOutputIDL *jitData)
{
    AUTO_NESTED_HANDLED_EXCEPTION_TYPE(static_cast<ExceptionType>(ExceptionType_OutOfMemory | ExceptionType_StackOverflow));
    LARGE_INTEGER start_time = { 0 };
    if (PHASE_TRACE1(Js::BackEndPhase))
    {
        QueryPerformanceCounter(&start_time);
    }
    memset(jitData, 0, sizeof(JITOutputIDL));

    ServerScriptContext * scriptContextInfo = (ServerScriptContext*)DecodePointer((void*)scriptContextInfoAddress);

    if (scriptContextInfo == nullptr)
    {
        Assert(false);
        return RPC_S_INVALID_ARG;
    }

    if (!ServerContextManager::IsScriptContextAlive(scriptContextInfo))
    {
        Assert(false);
        return E_ACCESSDENIED;
    }

    AutoReleaseContext<ServerScriptContext> autoScriptContext(scriptContextInfo);

    return ServerCallWrapper(scriptContextInfo, [&]() ->HRESULT
    {
        scriptContextInfo->UpdateGlobalObjectThisAddr(workItemData->globalThisAddr);
        ServerThreadContext * threadContextInfo = scriptContextInfo->GetThreadContext();

        NoRecoverMemoryJitArenaAllocator jitArena(L"JITArena", threadContextInfo->GetPageAllocator(), Js::Throw::OutOfMemory);
        JITTimeWorkItem * jitWorkItem = Anew(&jitArena, JITTimeWorkItem, workItemData);

        if (PHASE_VERBOSE_TRACE_RAW(Js::BackEndPhase, jitWorkItem->GetJITTimeInfo()->GetSourceContextId(), jitWorkItem->GetJITTimeInfo()->GetLocalFunctionId()))
        {
            LARGE_INTEGER freq;
            LARGE_INTEGER end_time;
            QueryPerformanceCounter(&end_time);
            QueryPerformanceFrequency(&freq);

            Output::Print(
                L"BackendMarshalIn - function: %s time:%8.6f mSec\r\n",
                jitWorkItem->GetJITFunctionBody()->GetDisplayName(),
                (((double)((end_time.QuadPart - workItemData->startTime)* (double)1000.0 / (double)freq.QuadPart))) / (1));
            Output::Flush();
        }

        auto profiler = scriptContextInfo->GetCodeGenProfiler();
#ifdef PROFILE_EXEC
        if (profiler && !profiler->IsInitialized())
        {
            profiler->Initialize(threadContextInfo->GetPageAllocator(), nullptr);
        }
#endif
        if (jitWorkItem->GetWorkItemData()->xProcNumberPageSegment)
        {
            jitData->numberPageSegments = (XProcNumberPageSegment*)midl_user_allocate(sizeof(XProcNumberPageSegment));
            if (!jitData->numberPageSegments)
            {
                return E_OUTOFMEMORY;
            }
            __analysis_assume(jitData->numberPageSegments);

            memcpy_s(jitData->numberPageSegments, sizeof(XProcNumberPageSegment), jitWorkItem->GetWorkItemData()->xProcNumberPageSegment, sizeof(XProcNumberPageSegment));
        }

        Func::Codegen(
            &jitArena,
            jitWorkItem,
            threadContextInfo,
            scriptContextInfo,
            jitData,
            nullptr,
            nullptr,
            jitWorkItem->GetPolymorphicInlineCacheInfo(),
            threadContextInfo->GetCodeGenAllocators(),
#if !FLOATVAR
            nullptr, // number allocator
#endif
            profiler,
            true);


#ifdef PROFILE_EXEC
        if (profiler && profiler->IsInitialized())
        {
            profiler->ProfilePrint(Js::Configuration::Global.flags.Profile.GetFirstPhase());
        }
#endif

        if (PHASE_VERBOSE_TRACE_RAW(Js::BackEndPhase, jitWorkItem->GetJITTimeInfo()->GetSourceContextId(), jitWorkItem->GetJITTimeInfo()->GetLocalFunctionId()))
        {
            LARGE_INTEGER freq;
            LARGE_INTEGER end_time;
            QueryPerformanceCounter(&end_time);
            QueryPerformanceFrequency(&freq);

            Output::Print(
                L"EndBackEndInner - function: %s time:%8.6f mSec\r\n",
                jitWorkItem->GetJITFunctionBody()->GetDisplayName(),
                (((double)((end_time.QuadPart - start_time.QuadPart)* (double)1000.0 / (double)freq.QuadPart))) / (1));
            Output::Flush();

        }
        LARGE_INTEGER out_time = { 0 };
        if (PHASE_TRACE1(Js::BackEndPhase))
        {
            QueryPerformanceCounter(&out_time);
            jitData->startTime = out_time.QuadPart;
        }

        return S_OK;
    });
}