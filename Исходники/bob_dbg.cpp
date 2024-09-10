void log_branch(_In_ PVOID address, _In_ DWORD pid, _In_ DWORD thread_id)
{
    if (!((DWORD_PTR)address >= k32_base && (DWORD_PTR)address < k32_max))
    {
        return;
    }


    // exception address read
    PDEBUGGEE dbge = NULL;
    for (int i = 0; i < sizeof(_debuggees) / sizeof(DEBUGGEE); ++i)
    {
        if (_debuggees[i]._pid == pid)
        {
            dbge = &_debuggees[i];
        }
    }
    if (NULL == dbge) return;

    SIZE_T bytes_read = 0;
    unsigned char buf[4] = { 0 };
    ReadProcessMemory(dbge->_proc_handle,
                      address,
                      buf,
                      sizeof(buf),
                      &bytes_read);

    if (0xE8 == buf[0])
    {
        log("call at 0x%08x", address);
    }

    // single step 을 활성화

    ch_param param = { 0 };
    param.hthread = OpenThread(THREAD_ALL_ACCESS, FALSE, thread_id);
    if (NULL != param.hthread)
    {
        param.context.ContextFlags = CONTEXT_ALL;
        if (TRUE != GetThreadContext(param.hthread, &param.context))
        {
            _ASSERTE(!"oops!");
            return;
        }
        set_single_step(&param);
    }
}