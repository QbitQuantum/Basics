static BOOL fill_sym_lvalue(const SYMBOL_INFO* sym, ULONG_PTR base,
                            struct dbg_lvalue* lvalue, char* buffer, size_t sz)
{
    if (buffer) buffer[0] = '\0';
    if (sym->Flags & SYMFLAG_REGISTER)
    {
        DWORD_PTR* pval;

        if (!memory_get_register(sym->Register, &pval, buffer, sz))
            return FALSE;
        lvalue->cookie = DLV_HOST;
        lvalue->addr.Offset = (DWORD_PTR)pval;
    }
    else if (sym->Flags & SYMFLAG_REGREL)
    {
        DWORD_PTR* pval;
        size_t  l;

        *buffer++ = '['; sz--;
        if (!memory_get_register(sym->Register, &pval, buffer, sz))
            return FALSE;
        l = strlen(buffer);
        sz -= l;
        buffer += l;
        lvalue->cookie = DLV_TARGET;
        lvalue->addr.Offset = (ULONG64)*pval + sym->Address;
        if ((LONG_PTR)sym->Address >= 0)
            snprintf(buffer, sz, "+%ld]", (ULONG_PTR)sym->Address);
        else
            snprintf(buffer, sz, "-%ld]", -(LONG_PTR)sym->Address);
    }
    else if (sym->Flags & SYMFLAG_VALUEPRESENT)
    {
        struct dbg_type type;
        VARIANT         v;

        type.module = sym->ModBase;
        type.id = sym->info;

        if (!types_get_info(&type, TI_GET_VALUE, &v))
        {
            if (buffer) snprintf(buffer, sz, "Couldn't get full value information for %s", sym->Name);
            return FALSE;
        }
        else if (v.n1.n2.vt & VT_BYREF)
        {
            /* FIXME: this won't work for pointers or arrays, as we don't always
             * know, if the value to be dereferenced lies in debuggee or
             * debugger address space.
             */
            if (sym->Tag == SymTagPointerType || sym->Tag == SymTagArrayType)
            {
                if (buffer) snprintf(buffer, sz, "Couldn't dereference pointer for const value for %s", sym->Name);
                return FALSE;
            }
            /* this is likely Wine's dbghelp which passes const values by reference
             * (object is managed by dbghelp, hence in debugger address space)
             */
            lvalue->cookie = DLV_HOST;
            lvalue->addr.Offset = (DWORD_PTR)sym->Value;
        }
        else
        {
            DWORD* pdw = (DWORD*)lexeme_alloc_size(sizeof(*pdw));
            lvalue->cookie = DLV_HOST;
            lvalue->addr.Offset = (DWORD_PTR)pdw;
            *pdw = sym->Value;
        }
    }
    else if (sym->Flags & SYMFLAG_LOCAL)
    {
        lvalue->cookie = DLV_TARGET;
        lvalue->addr.Offset = base + sym->Address;
    }
    else if (sym->Flags & SYMFLAG_TLSREL)
    {
        PROCESS_BASIC_INFORMATION pbi;
        THREAD_BASIC_INFORMATION  tbi;
        DWORD_PTR                 addr;
        PEB                       peb;
        PEB_LDR_DATA              ldr_data;
        PLIST_ENTRY               head, current;
        LDR_MODULE                ldr_module;
        unsigned                  tlsindex = -1;

        if (NtQueryInformationProcess(dbg_curr_process->handle, ProcessBasicInformation,
                                      &pbi, sizeof(pbi), NULL) ||
            NtQueryInformationThread(dbg_curr_thread->handle, ThreadBasicInformation,
                                     &tbi, sizeof(tbi), NULL))
        {
        tls_error:
            if (buffer) snprintf(buffer, sz, "Cannot read TLS address\n");
            return FALSE;
        }
        addr = (DWORD_PTR)&(((TEB*)tbi.TebBaseAddress)->ThreadLocalStoragePointer);
        if (!dbg_read_memory((void*)addr, &addr, sizeof(addr)) ||
            !dbg_read_memory(pbi.PebBaseAddress, &peb, sizeof(peb)) ||
            !dbg_read_memory(peb.LdrData, &ldr_data, sizeof(ldr_data)))
            goto tls_error;
        current = ldr_data.InLoadOrderModuleList.Flink;
        head = &((PEB_LDR_DATA*)peb.LdrData)->InLoadOrderModuleList;
        do
        {
            if (!dbg_read_memory(CONTAINING_RECORD(current, LDR_MODULE, InLoadOrderModuleList),
                                 &ldr_module, sizeof(ldr_module))) goto tls_error;
            if ((DWORD_PTR)ldr_module.BaseAddress == sym->ModBase)
            {
                tlsindex = ldr_module.TlsIndex;
                break;
            }
            current = ldr_module.InLoadOrderModuleList.Flink;
        } while (current != head);

        addr += tlsindex * sizeof(DWORD_PTR);
        if (!dbg_read_memory((void*)addr, &addr, sizeof(addr))) goto tls_error;
        lvalue->cookie = DLV_TARGET;
        lvalue->addr.Offset = addr + sym->Address;
    }
    else
    {
        lvalue->cookie = DLV_TARGET;
        lvalue->addr.Offset = sym->Address;
    }
    lvalue->addr.Mode = AddrModeFlat;
    lvalue->type.module = sym->ModBase;
    lvalue->type.id = sym->TypeIndex;

    return TRUE;
}