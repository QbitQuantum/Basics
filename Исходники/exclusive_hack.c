static void internal_api_load(void)
{
    HMODULE ntdll = GetModuleHandleW(L"ntdll.dll");
    if (!ntdll)
        return;
    pNtQueryMutant = (void*)GetProcAddress(ntdll, "NtQueryMutant");
    if (!pNtQueryMutant)
        return;
    excl_mode_mutex = OpenMutexW(MUTANT_QUERY_STATE, FALSE,
                                 L"Local\\__DDrawExclMode__");
    if (!excl_mode_mutex)
        return;

    internal_api_loaded = true;
}