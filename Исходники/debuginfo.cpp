    virtual void NotifyFunctionEmitted(const Function &F, void *Code,
                                       size_t Size, const EmittedFunctionDetails &Details)
    {
#if defined(_OS_WINDOWS_) && defined(_CPU_X86_64_)
        assert(!jl_in_stackwalk);
        jl_in_stackwalk = 1;
        uintptr_t catchjmp = (uintptr_t)Code+Size;
        *(uint8_t*)(catchjmp+0) = 0x48;
        *(uint8_t*)(catchjmp+1) = 0xb8; // mov RAX, QWORD PTR [...]
        *(uint64_t*)(catchjmp+2) = (uint64_t)&_seh_exception_handler;
        *(uint8_t*)(catchjmp+10) = 0xff;
        *(uint8_t*)(catchjmp+11) = 0xe0; // jmp RAX
        PRUNTIME_FUNCTION tbl = (PRUNTIME_FUNCTION)((catchjmp+12+3)&~(uintptr_t)3);
        uint8_t *UnwindData = (uint8_t*)((((uintptr_t)&tbl[1])+3)&~(uintptr_t)3);
        RUNTIME_FUNCTION fn = {0,(DWORD)Size+13,(DWORD)(intptr_t)(UnwindData-(uint8_t*)Code)};
        tbl[0] = fn;
        UnwindData[0] = 0x09; // version info, UNW_FLAG_EHANDLER
        UnwindData[1] = 4;    // size of prolog (bytes)
        UnwindData[2] = 2;    // count of unwind codes (slots)
        UnwindData[3] = 0x05; // frame register (rbp) = rsp
        UnwindData[4] = 4;    // second instruction
        UnwindData[5] = 0x03; // mov RBP, RSP
        UnwindData[6] = 1;    // first instruction
        UnwindData[7] = 0x50; // push RBP
        *(DWORD*)&UnwindData[8] = (DWORD)(catchjmp-(intptr_t)Code);
        DWORD mod_size = (DWORD)(size_t)(&UnwindData[8]-(uint8_t*)Code);
        if (!SymLoadModuleEx(GetCurrentProcess(), NULL, NULL, NULL, (DWORD64)Code, mod_size, NULL, SLMFLAG_VIRTUAL)) {
            static int warned = 0;
            if (!warned) {
                JL_PRINTF(JL_STDERR, "WARNING: failed to insert function info for backtrace\n");
                warned = 1;
            }
        }
        else {
            if (!SymAddSymbol(GetCurrentProcess(), (ULONG64)Code, F.getName().data(), (DWORD64)Code, mod_size, 0)) {
                JL_PRINTF(JL_STDERR, "WARNING: failed to insert function name into debug info\n");
            }
            if (!RtlAddFunctionTable(tbl,1,(DWORD64)Code)) {
                JL_PRINTF(JL_STDERR, "WARNING: failed to insert function stack unwind info\n");
            }
        }
        jl_in_stackwalk = 0;

        FuncInfo tmp = {&F, Size, std::string(), std::string(), tbl, Details.LineStarts};
#else
        FuncInfo tmp = {&F, Size, std::string(F.getName().data()), std::string(), Details.LineStarts};
#endif
        info[(size_t)(Code)] = tmp;
    }