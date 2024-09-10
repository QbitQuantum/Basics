static void *get_proc_address(void *process, DWORD pid, const char *func)
{
    void *ret = 0;

    MODULEENTRY32 entry;
    entry.dwSize = sizeof(entry);
    void *list = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);

    for (int k = Module32First(list, &entry); k; k = Module32Next(list, &entry))
    {
        IMAGE_DOS_HEADER dos;
        IMAGE_NT_HEADERS nt;
        IMAGE_EXPORT_DIRECTORY expdir;

        uint32_t exportaddr;
        uint8_t *base = entry.modBaseAddr;

        if (stricmp("kernel32.dll", entry.szModule))
            continue;

        SIZE_T tmp;
        ReadProcessMemory(process, base, &dos, sizeof(dos), &tmp);
        ReadProcessMemory(process, base + dos.e_lfanew, &nt, sizeof(nt), &tmp);

        exportaddr = nt.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
        if (!exportaddr)
            continue;

        ReadProcessMemory(process, base + exportaddr, &expdir, sizeof(expdir), &tmp);

        for (int i = 0; i < (int)expdir.NumberOfNames; ++i)
        {
            uint32_t nameaddr;
            /* Look for our function name in the list of names */
            ReadProcessMemory(process, base + expdir.AddressOfNames
                                            + i * sizeof(DWORD),
                              &nameaddr, sizeof(nameaddr), &tmp);
            char buf[1024];
            size_t buflen = strlen(func) + 1;
            ReadProcessMemory(process, base + nameaddr, buf, buflen, &tmp);

            if (strcmp(buf, func))
                continue;

            /* If we found a function with this name, return its address */
            uint16_t j;
            ReadProcessMemory(process, base + expdir.AddressOfNameOrdinals
                                            + i * sizeof(WORD),
                              &j, sizeof(j), &tmp);

            uint32_t funcaddr;
            ReadProcessMemory(process, base + expdir.AddressOfFunctions
                                            + j * sizeof(DWORD),
                              &funcaddr, sizeof(funcaddr), &tmp);

            ret = base + funcaddr;
            goto _finished;
        }
    }

_finished:
    CloseHandle(list);
    return ret;
}