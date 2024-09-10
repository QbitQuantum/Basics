int main(int argc, char** argv)
{
    HANDLE lib;
    HANDLE event;
    ULONG_PTR hThread;
    int reloaded = 0;

    USE_USER32();

#ifdef USE_DYNAMO
    dynamorio_app_init();
    dynamorio_app_start();
#endif

#ifdef LINUX
    /* though win32/ */
    intercept_signal(SIGSEGV, signal_handler);
#else
    /* note that can't normally if we have a debugger attached this
     * will not get this executed */
    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER) our_top_handler);
#endif

    event = CreateEvent(NULL, TRUE, FALSE, NULL);
    hThread = _beginthreadex(NULL, 0, run_func, event, 0, NULL);

    /* need to run as long as necessary to hit the required faults */
    while (transitions < NUM_TRANSITIONS) {
        lib = LoadLibrary("win32.reload-race.dll.dll");
        if (lib == NULL) {
            print("error loading library\n");
            break;
        } else {
            reloaded++;
#if VERBOSE
    print("reloaded %d times %d\n", reloaded);
#endif
            import1 = (funptr)
                GetProcAddress(lib, (LPCSTR)"import_me1");
            import2 = (funptr)
                GetProcAddress(lib, (LPCSTR)"import_me2");
            /* may want to explicitly sleep here but that may be slower */
            if (reloaded % 2 == 0)
                YIELD();
            FreeLibrary(lib);
            if (reloaded % 3 == 0)
                YIELD();
        }
    }

    SetEvent(event);
    WaitForSingleObject((HANDLE)hThread, INFINITE);
    print("main loop done\n");
    check_mem_usage();
#if VERBOSE
    print("reloaded %d times %d\n", reloaded);
#endif


#ifdef USE_DYNAMO
    dynamorio_app_stop();
    dynamorio_app_exit();
#endif
    return 0;
}