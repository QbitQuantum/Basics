    StackTrace::StackTrace(_EXCEPTION_POINTERS* exception_pointers)
    {
        // 使用StackWalk64()获得异常堆栈信息.
        count_ = 0;
        // 初始化堆栈查核行程.
        STACKFRAME64 stack_frame;
        memset(&stack_frame, 0, sizeof(stack_frame));
#if defined(_WIN64)
        int machine_type = IMAGE_FILE_MACHINE_AMD64;
        stack_frame.AddrPC.Offset = exception_pointers->ContextRecord->Rip;
        stack_frame.AddrFrame.Offset = exception_pointers->ContextRecord->Rbp;
        stack_frame.AddrStack.Offset = exception_pointers->ContextRecord->Rsp;
#else
        int machine_type = IMAGE_FILE_MACHINE_I386;
        stack_frame.AddrPC.Offset = exception_pointers->ContextRecord->Eip;
        stack_frame.AddrFrame.Offset = exception_pointers->ContextRecord->Ebp;
        stack_frame.AddrStack.Offset = exception_pointers->ContextRecord->Esp;
#endif
        stack_frame.AddrPC.Mode = AddrModeFlat;
        stack_frame.AddrFrame.Mode = AddrModeFlat;
        stack_frame.AddrStack.Mode = AddrModeFlat;
        while(StackWalk64(machine_type,
            GetCurrentProcess(),
            GetCurrentThread(),
            &stack_frame,
            exception_pointers->ContextRecord,
            NULL,
            &SymFunctionTableAccess64,
            &SymGetModuleBase64,
            NULL) && count_<arraysize(trace_))
        {
            trace_[count_++] = reinterpret_cast<void*>(stack_frame.AddrPC.Offset);
        }
    }