int ZCE_LIB::backtrace_stack(ZCE_LOG_PRIORITY dbg_lvl,
                             const char *dbg_info)
{

    //跟踪函数的层数
    const size_t SIZE_OF_BACKTRACE_FUNC = 100;

#if defined(ZCE_OS_LINUX)
    ZCE_LOG(dbg_lvl, "[BACKTRACE]This program compiled by Linux GCC. %s", dbg_info);
    //Windows 下必须是2008或者VISTA之后的SDK才支持，
#elif defined(ZCE_OS_WINDOWS) && ZCE_SUPPORT_WINSVR2008 == 1
    ZCE_LOG(dbg_lvl, "[BACKTRACE]This program compiled by Windows Visual studio .%s", dbg_info);
#else
    ZCE_UNUSED_ARG(SIZE_OF_BACKTRACE_FUNC);
    ZCE_LOG(dbg_lvl, "[BACKTRACE]back_trace_stack don't support this system.%s", dbg_info);
#endif


    //这个方法是提供给Linux 下的GCC使用的
#if defined(ZCE_OS_LINUX)


    void *backtrace_buffer[SIZE_OF_BACKTRACE_FUNC];
    char **symbols_strings;

    int sz_of_stack = ::backtrace(backtrace_buffer, SIZE_OF_BACKTRACE_FUNC);

    //
    symbols_strings = ::backtrace_symbols(backtrace_buffer, sz_of_stack);

    if (symbols_strings == NULL)
    {
        ZCE_LOG(dbg_lvl, "%s", "[BACKTRACE] backtrace_symbols return fail.");
    }

    //打印所有的堆栈信息,有些时候信息无法显示符号表，建议使用
    for (int j = 0; j < sz_of_stack; j++)
    {
        ZCE_LOG(dbg_lvl, "[BACKTRACE] %u, %s.", j + 1, symbols_strings[j]);
    }

    //释放空间
    ::free(symbols_strings);

#elif defined(ZCE_OS_WINDOWS) && ZCE_SUPPORT_WINSVR2008 == 1

    //我还没有时间看完dbghelp所有的东西,目前的代码参考后一个版本居多,目前这个东东必须有pdb文件，
    //http://blog.csdn.net/skies457/article/details/7201185

    // Max length of symbols' name.
    const size_t MAX_NAME_LENGTH = 256;

    // Store register addresses.
    CONTEXT context;
    // Call stack.
    STACKFRAME64 stackframe;
    // Handle to current process & thread.
    HANDLE process, cur_thread;
    // Generally it can be subsitituted with 0xFFFFFFFF & 0xFFFFFFFE.
    // Debugging symbol's information.
    PSYMBOL_INFO symbol;
    // Source information (file name & line number)
    IMAGEHLP_LINE64 source_info;
    // Source line displacement.
    DWORD displacement;

    // Initialize PSYMBOL_INFO structure.
    // Allocate a properly-sized block.
    symbol = (PSYMBOL_INFO)malloc(sizeof(SYMBOL_INFO) + (MAX_NAME_LENGTH) * sizeof(char));
    memset(symbol, 0, sizeof(SYMBOL_INFO) + (MAX_NAME_LENGTH) * sizeof(TCHAR));
    symbol->SizeOfStruct = sizeof(SYMBOL_INFO);  // SizeOfStruct *MUST BE* set to sizeof(SYMBOL_INFO).
    symbol->MaxNameLen = MAX_NAME_LENGTH;

    // Initialize IMAGEHLP_LINE64 structure.
    memset(&source_info, 0, sizeof(IMAGEHLP_LINE64));
    source_info.SizeOfStruct = sizeof(IMAGEHLP_LINE64);

    // Initialize STACKFRAME64 structure.
    RtlCaptureContext(&context);            // Get context.
    memset(&stackframe, 0, sizeof(STACKFRAME64));

    // Fill in register addresses (EIP, ESP, EBP).

    stackframe.AddrPC.Mode = AddrModeFlat;
    stackframe.AddrStack.Mode = AddrModeFlat;
    stackframe.AddrFrame.Mode = AddrModeFlat;

#if defined ZCE_WIN32
    stackframe.AddrPC.Offset = context.Eip;
    stackframe.AddrStack.Offset = context.Esp;
    stackframe.AddrFrame.Offset = context.Ebp;
#elif defined ZCE_WIN64
    stackframe.AddrPC.Offset = context.Rip;
    stackframe.AddrStack.Offset = context.Rsp;
    stackframe.AddrFrame.Offset = context.Rbp;
#else
#endif
    // Get current process & thread.
    process = GetCurrentProcess();
    cur_thread = GetCurrentThread();

    // Initialize dbghelp library.
    if (!SymInitialize(process, NULL, TRUE))
    {
        return -1;
    }

    //这些空间是绝对足够的，我也不做详细的检查了
    const size_t LINE_OUTLEN = 1024;
    char line_out[LINE_OUTLEN];
    int use_len = 0;

    uint32_t k = 0;
    // Enumerate call stack frame.
    while (StackWalk64(IMAGE_FILE_MACHINE_I386,
                       process,
                       cur_thread,
                       &stackframe,
                       &context,
                       NULL,
                       SymFunctionTableAccess64,
                       SymGetModuleBase64,
                       NULL))
    {
        use_len = 0;
        // End reaches.
        if (stackframe.AddrFrame.Offset == 0 || k > SIZE_OF_BACKTRACE_FUNC)
        {
            break;
        }

        // Get symbol.
        if (SymFromAddr(process, stackframe.AddrPC.Offset, NULL, symbol))
        {
            use_len += snprintf(line_out + use_len, LINE_OUTLEN - use_len, " %s", symbol->Name);

        }

        if (SymGetLineFromAddr64(process, stackframe.AddrPC.Offset,
                                 &displacement,
                                 &source_info))
        {
            // Get source information.
            use_len += snprintf(line_out + use_len, LINE_OUTLEN - use_len, "\t[ %s: %d] at addr 0x % 08LX",
                                source_info.FileName,
                                source_info.LineNumber,
                                stackframe.AddrPC.Offset);
        }
        else
        {
            // If err_code == 0x1e7, no symbol was found.
            if (GetLastError() == 0x1E7)
            {
                use_len += snprintf(line_out + use_len, LINE_OUTLEN - use_len, "%s", "\tNo debug symbol loaded for this function.");
            }
        }
        ZCE_LOG(dbg_lvl, "[BACKTRACE] %u, %s.", k + 1, line_out);
        ++k;
    }

    SymCleanup(process);    // Clean up and exit.
    free(symbol);

#endif

    //
    return 0;

}