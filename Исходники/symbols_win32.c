static int find_pe_symbol_by_name(Context * ctx, int frame, ContextAddress ip, char * name, Symbol * sym) {
    HANDLE process = get_context_handle(ctx->parent == NULL ? ctx : ctx->parent);
    ULONG64 buffer[(sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR) + sizeof(ULONG64) - 1) / sizeof(ULONG64)];
    SYMBOL_INFO * info = (SYMBOL_INFO *)buffer;
    IMAGEHLP_STACK_FRAME stack_frame;
    DWORD err;

    if (set_pe_context(ctx, frame, ip, process, &stack_frame) < 0) return -1;

    memset(info, 0, sizeof(SYMBOL_INFO));
    info->SizeOfStruct = sizeof(SYMBOL_INFO);
    info->MaxNameLen = MAX_SYM_NAME;

    if (find_cache_symbol(ctx, frame, stack_frame.InstructionOffset, name, sym)) return errno ? -1 : 0;

    /* TODO: SymFromName() searches only main executable, need to search DLLs too */
    if (SymFromName(process, name, info) && info->Tag != SymTagPublicSymbol) {
        syminfo2symbol(ctx, frame, info, sym);
        add_cache_symbol(ctx, stack_frame.InstructionOffset, name, sym, 0);
        return 0;
    }
    if (stack_frame.InstructionOffset != 0) {
        DWORD64 module = SymGetModuleBase64(process, stack_frame.InstructionOffset);
        if (module != 0 && SymGetTypeFromName(process, module, name, info)) {
            syminfo2symbol(ctx, frame, info, sym);
            add_cache_symbol(ctx, stack_frame.InstructionOffset, name, sym, 0);
            return 0;
        }
    }
    set_win32_errno(err = GetLastError());
    if (err == 0 || err == ERROR_MOD_NOT_FOUND) {
        add_cache_symbol(ctx, stack_frame.InstructionOffset, name, NULL, ERR_SYM_NOT_FOUND);
        errno = ERR_SYM_NOT_FOUND;
    }
    return -1;
}