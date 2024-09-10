int diag_backtrace(diag_output_t *o, diag_backtrace_param_t *p, diag_context_t *c)
{
    int cur = 0, count;
    STACKFRAME64 stackframe;
    CONTEXT context;
    HANDLE process = GetCurrentProcess();
    HANDLE thread = GetCurrentThread();
    DWORD bytes_written;

    if (c) {
        context = *c->context;
    }
    else {
        RtlCaptureContext(&context);
    }

    if (p->backtrace_count && p->backtrace_count < DIAG_BT_LIMIT) {
        count = p->backtrace_count;
    }
    else {
        count = DIAG_BT_LIMIT;
    }

    memset(&stackframe, 0, sizeof stackframe);
    stackframe.AddrPC.Mode = 
        stackframe.AddrFrame.Mode =
            stackframe.AddrStack.Mode = AddrModeFlat;

#ifdef DIAG_BITS_64
    stackframe.AddrPC.Offset    = context.Rip;
    stackframe.AddrFrame.Offset = context.Rbp;
    stackframe.AddrStack.Offset = context.Rsp;
#else
    stackframe.AddrPC.Offset    = context.Eip;
    stackframe.AddrFrame.Offset = context.Ebp;
    stackframe.AddrStack.Offset = context.Esp;
#endif

    if (!p->symbols_initialized) {
        SymInitialize(process, NULL, TRUE);
    }

    while (StackWalk64(
#ifdef DIAG_BITS_64
                       IMAGE_FILE_MACHINE_AMD64,
#else
                       IMAGE_FILE_MACHINE_I386,
#endif
                       process, thread,
                       &stackframe,
                       &context,
                       NULL,                       /* ReadMemoryRoutine */
                       SymFunctionTableAccess64,   /* FunctionTableAccessRoutine */
                       SymGetModuleBase64,         /* GetModuleBaseRoutine */
                       NULL)                       /* TranslateAddress */
           == TRUE) {
        char symbol_buffer[128] = {0};
        IMAGEHLP_SYMBOL64 *symbol = (IMAGEHLP_SYMBOL64 *)&symbol_buffer;
        DWORD64 ignored;
        const char *function;
        const char *offset;
        char address_buf[20], offset_buf[20];
        char buf[128];
        char *outch = buf;
        char *lastoutch = buf + sizeof buf - 1;

        if (cur + 1 > count) { /* avoid loop on corrupted chain, respect caller's wishes */
            break;
        }
        symbol->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL64);
        symbol->MaxNameLength = sizeof(symbol_buffer) - sizeof(IMAGEHLP_SYMBOL64);
        ignored = 0;
        if (SymGetSymFromAddr64(process, stackframe.AddrPC.Offset, &ignored, symbol) != TRUE) {
            function = NULL;
            offset = NULL;
        }
        else {
            function = symbol->Name;
            add_int(offset_buf, offset_buf + sizeof offset_buf - 1,
                    stackframe.AddrPC.Offset - symbol->Address, 16);
            offset = offset_buf;
        }

        add_int(address_buf, address_buf + sizeof address_buf - 1,
                stackframe.AddrPC.Offset, 16);

        if (function && !strcmp(function, "diag_backtrace")) {
            /* filter outselves out */
            continue;
        }

        cur++; /* gonna keep this frame, so count it */

        output_frame(outch, lastoutch, p->backtrace_fields,
                     NULL, /* no module path */
                     NULL, /* no module */
                     function,
                     offset,
                     address_buf);

        if (o->output_mode == DIAG_CALL_FN) {
            o->output_fn(o->user_data, buf);
        }
        else {
            WriteFile(o->outfile, buf, strlen(buf), &bytes_written, NULL);
            WriteFile(o->outfile, "\r\n", 2, &bytes_written, NULL);
        }
    }

    return 0;
}