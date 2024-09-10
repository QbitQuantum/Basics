void stackgetcallstack(duint csp, std::vector<CALLSTACKENTRY> & callstackVector, bool cache)
{
    if(cache)
    {
        SHARED_ACQUIRE(LockCallstackCache);
        auto found = CallstackCache.find(csp);
        if(found != CallstackCache.end())
        {
            callstackVector = found->second;
            return;
        }
        callstackVector.clear();
        return;
    }

    // Gather context data
    CONTEXT context;
    memset(&context, 0, sizeof(CONTEXT));

    context.ContextFlags = CONTEXT_CONTROL | CONTEXT_INTEGER;

    if(SuspendThread(hActiveThread) == -1)
        return;

    if(!GetThreadContext(hActiveThread, &context))
        return;

    if(ResumeThread(hActiveThread) == -1)
        return;

    // Set up all frame data
    STACKFRAME64 frame;
    ZeroMemory(&frame, sizeof(STACKFRAME64));

#ifdef _M_IX86
    DWORD machineType = IMAGE_FILE_MACHINE_I386;
    frame.AddrPC.Offset = context.Eip;
    frame.AddrPC.Mode = AddrModeFlat;
    frame.AddrFrame.Offset = context.Ebp;
    frame.AddrFrame.Mode = AddrModeFlat;
    frame.AddrStack.Offset = csp;
    frame.AddrStack.Mode = AddrModeFlat;
#elif _M_X64
    DWORD machineType = IMAGE_FILE_MACHINE_AMD64;
    frame.AddrPC.Offset = context.Rip;
    frame.AddrPC.Mode = AddrModeFlat;
    frame.AddrFrame.Offset = context.Rsp;
    frame.AddrFrame.Mode = AddrModeFlat;
    frame.AddrStack.Offset = csp;
    frame.AddrStack.Mode = AddrModeFlat;
#endif

    const int MaxWalks = 50;
    // Container for each callstack entry (50 pre-allocated entries)
    callstackVector.clear();
    callstackVector.reserve(MaxWalks);

    for(auto i = 0; i < MaxWalks; i++)
    {
        if(!StackWalk64(
                    machineType,
                    fdProcessInfo->hProcess,
                    hActiveThread,
                    &frame,
                    &context,
                    StackReadProcessMemoryProc64,
                    SymFunctionTableAccess64,
                    StackGetModuleBaseProc64,
                    StackTranslateAddressProc64))
        {
            // Maybe it failed, maybe we have finished walking the stack
            break;
        }

        if(frame.AddrPC.Offset != 0)
        {
            // Valid frame
            CALLSTACKENTRY entry;
            memset(&entry, 0, sizeof(CALLSTACKENTRY));

            StackEntryFromFrame(&entry, (duint)frame.AddrFrame.Offset + sizeof(duint), (duint)frame.AddrPC.Offset, (duint)frame.AddrReturn.Offset);
            callstackVector.push_back(entry);
        }
        else
        {
            // Base reached
            break;
        }
    }

    EXCLUSIVE_ACQUIRE(LockCallstackCache);
    if(CallstackCache.size() > MAX_CALLSTACK_CACHE)
        CallstackCache.clear();
    CallstackCache[csp] = callstackVector;
}