FRR_TYPE ReplaceFunctionW(const wchar_t *dllName, const char *funcName, FUNCPTR newFunc, UINT opcodesNumber, FUNCPTR* origFunc)
{
    // Cache the results of the last search for the module
    // Assume that there was no DLL unload between 
    static wchar_t cachedName[MAX_PATH+1];
    static HMODULE cachedHM = 0;

    if (!dllName || !*dllName)
        return FRR_NODLL;

    if (!cachedHM || wcsncmp(dllName, cachedName, MAX_PATH) != 0)
    {
        // Find the module handle for the input dll
        HMODULE hModule = GetModuleHandleW(dllName);
        if (hModule == 0)
        {
            // Couldn't find the module with the input name
            cachedHM = 0;
            return FRR_NODLL;
        }

        cachedHM = hModule;
        wcsncpy(cachedName, dllName, MAX_PATH);
    }

    FARPROC inpFunc = GetProcAddress(cachedHM, funcName);
    if (inpFunc == 0)
    {
        // Function was not found
        return FRR_NOFUNC;
    }

    if (!InsertTrampoline((void*)inpFunc, (void*)newFunc, opcodesNumber, origFunc)){
        // Failed to insert the trampoline to the target address
        return FRR_FAILED;
    }

    return FRR_OK;
}