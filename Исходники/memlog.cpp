void PlatformDebugSymbols::loadSymbolInfo(mt_uint64 base_address, mt_uint64 len, const char* sympath) {
    LoadedModule ld;
    ld.oldBase = base_address;
    ld.len = len;
    ld.newBase = SymLoadModuleEx(GetCurrentProcess(), 0, sympath, 0, 0, 0, 0, 0);
    loadedModules.push_back(ld);
}