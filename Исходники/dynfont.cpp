BOOL hook_getprocaddress()
{
    HMODULE vim;
    PIMAGE_IMPORT_DESCRIPTOR impdesc;
    PIMAGE_IMPORT_DESCRIPTOR kernel32;
    PIMAGE_THUNK_DATA lookuptbl;
    PIMAGE_THUNK_DATA addrtbl;
    MEMORY_BASIC_INFORMATION bufinfo;
    BOOL succeeded;
    DWORD oldprotect;
    DWORD retsize;
    int i;

    vim = GetModuleHandle(NULL);

    impdesc = (PIMAGE_IMPORT_DESCRIPTOR)ImageDirectoryEntryToData((HMODULE)vim, TRUE, IMAGE_DIRECTORY_ENTRY_IMPORT, &retsize);
    if (retsize == 0) return FALSE;
    OutputDebugString("dynfont: importdir found");

    kernel32 = NULL;
    for (i = 0; impdesc[i].Characteristics != 0; ++i) {
        LPCSTR libname = (LPCSTR)((char*)vim + impdesc[i].Name);
        OutputDebugString(libname);
        if (lstrcmpi(libname, "KERNEL32.DLL") == 0) {
            kernel32 = &impdesc[i];
            break;
        }
    }
    if (kernel32 == NULL) return FALSE;
    OutputDebugString("dynfont: kernel32 found.");

    lookuptbl = (PIMAGE_THUNK_DATA)((char*)vim + kernel32->OriginalFirstThunk);
    addrtbl = (PIMAGE_THUNK_DATA)((char*)vim + kernel32->FirstThunk);
    for (; lookuptbl->u1.Function != 0; ++lookuptbl, ++addrtbl) {
        if (!IMAGE_SNAP_BY_ORDINAL(lookuptbl->u1.Ordinal)) {
           PIMAGE_IMPORT_BY_NAME impfun = (PIMAGE_IMPORT_BY_NAME)((char*)vim + lookuptbl->u1.AddressOfData);
            if (strcmp((LPCSTR)impfun->Name, "GetProcAddress") == 0) {
                break;
            }
        }
    }
    if (lookuptbl->u1.Function == 0) return FALSE;
    OutputDebugString("dynfont: getprocaddr found.");

    orig_GetProcAddress = (GETPROCADDRESS_PROTO)addrtbl->u1.Function;
    retsize = VirtualQuery((LPCVOID)&addrtbl->u1.Function, &bufinfo, sizeof(bufinfo));
    if (retsize == 0) return FALSE;
    succeeded = VirtualProtect(bufinfo.BaseAddress, bufinfo.RegionSize, PAGE_READWRITE, &oldprotect);
    if (succeeded == FALSE) return FALSE;
    addrtbl->u1.Function = (DWORD_PTR)oncall_GetProcAddress;
    VirtualProtect(bufinfo.BaseAddress, bufinfo.RegionSize, bufinfo.Protect, &oldprotect);
    OutputDebugString("dynfont: hooked.");
    return TRUE; 
}