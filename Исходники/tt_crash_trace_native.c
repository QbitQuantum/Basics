void __addr2sym(IN tt_uintptr_t addr, IN tt_char_t *buf, IN tt_u32_t len)
{
    HANDLE proc;
    tt_u8_t tmp[sizeof(SYMBOL_INFO) + __SYM_SIZE + 1];
    PSYMBOL_INFO sym = (PSYMBOL_INFO)tmp;
    IMAGEHLP_LINEW64 line;
    DWORD64 addr_disp;
    DWORD disp2;
    tt_char_t *fname;

    proc = GetCurrentProcess();

    sym->SizeOfStruct = sizeof(SYMBOL_INFO);
    sym->MaxNameLen = __SYM_SIZE;
    line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);

    if (!SymFromAddr(proc, addr, &addr_disp, sym)) {
        tt_snprintf(buf, len - 1, "%p", addr);
    } else if (!SymGetLineFromAddrW64(proc, addr, &disp2, &line) ||
               ((fname = tt_utf8_create(line.FileName, 0, NULL)) == NULL)) {
        tt_snprintf(buf,
                    len - 1,
                    "%p in %s(+0x%x)",
                    addr,
                    sym->Name,
                    addr_disp);
    } else {
        tt_snprintf(buf,
                    len - 1,
                    "%p in %s() at [%s:%d]",
                    addr,
                    sym->Name,
                    fname,
                    line.LineNumber);
        tt_free(fname);
    }
}