    SEA_EXPORT const char* resolve_pointer(const char* szModulePath, uint64_t addr)
    {
        static std::string res;
        res.clear();
        static HANDLE hCurProc = GetCurrentProcess();
        DWORD dwOptions = SymSetOptions((SymGetOptions() | SYMOPT_LOAD_LINES | SYMOPT_UNDNAME | SYMOPT_INCLUDE_32BIT_MODULES | SYMOPT_ALLOW_ABSOLUTE_SYMBOLS) & ~SYMOPT_DEFERRED_LOADS);
        static BOOL bInitialize = SymInitialize(hCurProc, NULL, TRUE);
        if (!bInitialize) return nullptr;
        static std::map<std::string, uint64_t> modules;
        uint64_t module = 0;
        if (modules.count(szModulePath))
        {
            module = modules[szModulePath];
        }
        else
        {
            module = SymLoadModule64(hCurProc, NULL, szModulePath, NULL, 0x800000, 0);
            modules[szModulePath] = module;
        }
        if (!module) return nullptr;
        IMAGEHLP_LINE64 line = { sizeof(IMAGEHLP_LINE64) };
        DWORD dwDisplacement = 0;
        SymGetLineFromAddr64(hCurProc, module + addr, &dwDisplacement, &line);
        if (line.FileName)
        {
            res += std::string(line.FileName) + "(" + std::to_string(line.LineNumber) + ")\n";
        }

        char buff[sizeof(SYMBOL_INFO) + 1024] = {};
        SYMBOL_INFO * symbol = (SYMBOL_INFO*)buff;
        symbol->MaxNameLen = 255;
        symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
        SymFromAddr(hCurProc, module + addr, nullptr, symbol);
        res += symbol->Name;
        return res.c_str();
    }