void apply_emet(HMODULE pHandle, int a2)
{
    // has this point
    if ( setting_heapspray )
        heapspray_apply();
    if ( setting_bottomuprand )
        bottomuprand_apply();
    if ( setting_nullpage )
        nullpage_apply();
    if ( setting_dep )
        enableDEP();
    if ( setting_sehop ){
        getModuleHandleEx(pHandle);
        set_sehop_ceh_handler();
        enable_sehop = 1;
    }
    if ( setting_eaf ){
        hook_eat(L"kernel32.dll");
        hook_eat(L"ntdll.dll");
        HMODULE handle;
        getModuleHandleEx(handle);
        set_ceh_handler();
        HANDLE thread_lock = CreateMutexW(0, 1, 0);
        thread_count = 0;
        ReleaseMutex(thread_lock);
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)StartAddress, 0, 0, 0);
        has_new_thread = true;
        save_current_threadid();
    }
}