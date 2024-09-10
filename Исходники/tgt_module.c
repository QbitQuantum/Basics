enum dbg_start tgt_module_load(const char* name, BOOL keep)
{
    DWORD opts = SymGetOptions();
    HANDLE hDummy = (HANDLE)0x87654321;
    enum dbg_start ret = start_ok;
    WCHAR* nameW;
    unsigned len;

    SymSetOptions((opts & ~(SYMOPT_UNDNAME|SYMOPT_DEFERRED_LOADS)) |
                  SYMOPT_LOAD_LINES | SYMOPT_AUTO_PUBLICS | 0x40000000);
    if (!dbg_init(hDummy, NULL, FALSE))
        return start_error_init;
    len = MultiByteToWideChar(CP_ACP, 0, name, -1, NULL, 0);
    nameW = HeapAlloc(GetProcessHeap(), 0, len * sizeof(WCHAR));
    if (!nameW)
    {
        ret = start_error_init;
        keep = FALSE;
    }
    else
    {
        len = MultiByteToWideChar(CP_ACP, 0, name, -1, nameW, len);
        if (!dbg_load_module(hDummy, NULL, nameW, 0, 0))
        {
            ret = start_error_init;
            keep = FALSE;
        }
        HeapFree(GetProcessHeap(), 0, nameW);
    }

    if (keep)
    {
        dbg_printf("Non supported mode... errors may occur\n"
                   "Use at your own risks\n");
        SymSetOptions(SymGetOptions() | 0x40000000);
        dbg_curr_process = dbg_add_process(&be_process_module_io, 1, hDummy);
        dbg_curr_pid = 1;
        dbg_curr_thread = dbg_add_thread(dbg_curr_process, 2, NULL, NULL);

        /* FIXME: missing thread creation, fetching frames, restoring dbghelp's options... */
    }
    else
    {
        SymCleanup(hDummy);
        SymSetOptions(opts);
    }

    return ret;
}