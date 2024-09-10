bool app_list::get_app_info(app_info & info, const filters_t & filters, bool x86, bool query_name) {
    HMODULE hmodules[1024]; 
    DWORD needed; 
    HANDLE hprocess = OpenProcess(
        PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, 
        FALSE, info.id); 
    if (hprocess == NULL)
        return false; 

#ifdef _WIN64
    BOOL px86; 
    if ( ! IsWow64Process(hprocess,  & px86)) {
        CloseHandle(hprocess); 
        return false; 
    }
    info.x86 = px86; 
#else
    info.x86 = true; 
#endif

    if (query_name && EnumProcessModulesEx(
        hprocess, hmodules, sizeof(hmodules),  & needed, x86?LIST_MODULES_32BIT:LIST_MODULES_64BIT)) {
        WCHAR name[MAX_PATH] =  {0}; 
        std::wstring exename; 
        if (GetModuleBaseName(hprocess, hmodules[0], name, sizeof(name)/sizeof(WCHAR))) {
            _wcslwr(name); 
            exename = name; 

            // skip filter
            if (filters.empty()) {
                info.name = exename; 
                CloseHandle(hprocess); 
                return true; 
            }

            for (DWORD j = 0; j < (needed / sizeof(HMODULE)); j++) {
                WCHAR name[MAX_PATH] =  {0}; 
                if (GetModuleBaseName(hprocess, hmodules[j], name, sizeof(name)/sizeof(WCHAR))) {
                    _wcslwr(name); 
                    for (filters_t::const_iterator it = filters.begin(); it != filters.end(); it++)
                        if ( * it == name) {
                            info.name = exename; 
                            CloseHandle(hprocess); 
                            return true; 
                        }; 
                }
            }
        }
    }

    CloseHandle(hprocess); 
    return ! query_name; 
}