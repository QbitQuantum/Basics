bool __cdecl __vcrt_initialize()
{
    #if defined CRTDLL
    __isa_available_init();
    #endif

    init_memcpy_functions();

    __vcrt_initialize_pure_virtual_call_handler();
    __vcrt_initialize_winapi_thunks();

    if (!__vcrt_initialize_locks())
    {
        return false;
    }

    if (!__vcrt_initialize_ptd())
    {
        __vcrt_uninitialize_locks();
        return false;
    }

    return true;
}