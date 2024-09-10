static void real_init(void) {
#ifdef VS_TARGET_OS_WINDOWS
    // portable
    const std::wstring pythonDllName = L"python37.dll";
    HMODULE module;
    GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCWSTR)&real_init, &module);
    std::vector<wchar_t> pathBuf(65536);
    GetModuleFileNameW(module, pathBuf.data(), (DWORD)pathBuf.size());
    std::wstring dllPath = pathBuf.data();
    dllPath.resize(dllPath.find_last_of('\\') + 1);
    std::wstring portableFilePath = dllPath + L"portable.vs";
    FILE *portableFile = _wfopen(portableFilePath.c_str(), L"rb");
    bool isPortable = !!portableFile;
    if (portableFile)
        fclose(portableFile);

    HMODULE pythonDll = nullptr;

    if (isPortable) {
        std::wstring pyPath = dllPath + L"\\" + pythonDllName;
        pythonDll = LoadLibraryExW(pyPath.c_str(), nullptr, LOAD_LIBRARY_SEARCH_DEFAULT_DIRS | LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR);
    } else {
        DWORD dwType = REG_SZ;
        HKEY hKey = 0;

        wchar_t value[1024];
        DWORD valueLength = 1000;
        if (RegOpenKeyW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\VapourSynth", &hKey) != ERROR_SUCCESS)
            return;
        LSTATUS status = RegQueryValueExW(hKey, L"PythonPath", nullptr, &dwType, (LPBYTE)&value, &valueLength);
        RegCloseKey(hKey);
        if (status != ERROR_SUCCESS)
            return;

        std::wstring pyPath = value;
        pyPath += L"\\" + pythonDllName;

        pythonDll = LoadLibraryExW(pyPath.c_str(), nullptr, LOAD_LIBRARY_SEARCH_DEFAULT_DIRS | LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR);
    }
    if (!pythonDll)
        return;
#endif
    int preInitialized = Py_IsInitialized();
    if (!preInitialized)
        Py_InitializeEx(0);
    s = PyGILState_Ensure();
    if (import_vapoursynth())
        return;
    if (vpy_initVSScript())
        return;
    ts = PyEval_SaveThread();
    initialized = true;
}