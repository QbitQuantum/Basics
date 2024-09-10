/***********************************************************************
 *           thread_init
 *
 * Setup the initial thread.
 *
 * NOTES: The first allocated TEB on NT is at 0x7ffde000.
 */
HANDLE thread_init(void)
{
    TEB *teb;
    void *addr;
    SIZE_T size, info_size;
    HANDLE exe_file = 0;
    LARGE_INTEGER now;
    NTSTATUS status;
    struct ntdll_thread_data *thread_data;
    static struct debug_info debug_info;  /* debug info for initial thread */

    virtual_init();

    /* reserve space for shared user data */

    addr = (void *)0x7ffe0000;
    size = 0x10000;
    status = NtAllocateVirtualMemory( NtCurrentProcess(), &addr, 0, &size,
                                      MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE );
    if (status)
    {
        MESSAGE( "wine: failed to map the shared user data: %08x\n", status );
        exit(1);
    }
    user_shared_data = addr;

    /* allocate and initialize the PEB */

    addr = NULL;
    size = sizeof(*peb);
    NtAllocateVirtualMemory( NtCurrentProcess(), &addr, 1, &size,
                             MEM_COMMIT | MEM_TOP_DOWN, PAGE_READWRITE );
    peb = addr;

    peb->ProcessParameters  = &params;
    peb->TlsBitmap          = &tls_bitmap;
    peb->TlsExpansionBitmap = &tls_expansion_bitmap;
    peb->FlsBitmap          = &fls_bitmap;
    peb->LdrData            = &ldr;
    params.CurrentDirectory.DosPath.Buffer = current_dir;
    params.CurrentDirectory.DosPath.MaximumLength = sizeof(current_dir);
    params.wShowWindow = 1; /* SW_SHOWNORMAL */
    ldr.Length = sizeof(ldr);
    RtlInitializeBitMap( &tls_bitmap, peb->TlsBitmapBits, sizeof(peb->TlsBitmapBits) * 8 );
    RtlInitializeBitMap( &tls_expansion_bitmap, peb->TlsExpansionBitmapBits,
                         sizeof(peb->TlsExpansionBitmapBits) * 8 );
    RtlInitializeBitMap( &fls_bitmap, peb->FlsBitmapBits, sizeof(peb->FlsBitmapBits) * 8 );
    InitializeListHead( &peb->FlsListHead );
    InitializeListHead( &ldr.InLoadOrderModuleList );
    InitializeListHead( &ldr.InMemoryOrderModuleList );
    InitializeListHead( &ldr.InInitializationOrderModuleList );
#ifdef __APPLE__
    peb->Reserved[0] = get_dyld_image_info_addr();
#endif

    /* allocate and initialize the initial TEB */

    signal_alloc_thread( &teb );
    teb->Peb = peb;
    teb->Tib.StackBase = (void *)~0UL;
    teb->StaticUnicodeString.Buffer = teb->StaticUnicodeBuffer;
    teb->StaticUnicodeString.MaximumLength = sizeof(teb->StaticUnicodeBuffer);

    thread_data = (struct ntdll_thread_data *)teb->SpareBytes1;
    thread_data->request_fd = -1;
    thread_data->reply_fd   = -1;
    thread_data->wait_fd[0] = -1;
    thread_data->wait_fd[1] = -1;
    thread_data->debug_info = &debug_info;
    InsertHeadList( &tls_links, &teb->TlsLinks );

    signal_init_thread( teb );
    virtual_init_threading();

    debug_info.str_pos = debug_info.strings;
    debug_info.out_pos = debug_info.output;
    debug_init();

    /* setup the server connection */
    server_init_process();
    info_size = server_init_thread( peb );

    /* create the process heap */
    if (!(peb->ProcessHeap = RtlCreateHeap( HEAP_GROWABLE, NULL, 0, 0, NULL, NULL )))
    {
        MESSAGE( "wine: failed to create the process heap\n" );
        exit(1);
    }

    /* allocate user parameters */
    if (info_size)
    {
        init_user_process_params( info_size, &exe_file );
    }
    else
    {
        if (isatty(0) || isatty(1) || isatty(2))
            params.ConsoleHandle = (HANDLE)2; /* see kernel32/kernel_private.h */
        if (!isatty(0))
            wine_server_fd_to_handle( 0, GENERIC_READ|SYNCHRONIZE,  OBJ_INHERIT, &params.hStdInput );
        if (!isatty(1))
            wine_server_fd_to_handle( 1, GENERIC_WRITE|SYNCHRONIZE, OBJ_INHERIT, &params.hStdOutput );
        if (!isatty(2))
            wine_server_fd_to_handle( 2, GENERIC_WRITE|SYNCHRONIZE, OBJ_INHERIT, &params.hStdError );
    }

    /* initialize time values in user_shared_data */
    NtQuerySystemTime( &now );
    user_shared_data->SystemTime.LowPart = now.u.LowPart;
    user_shared_data->SystemTime.High1Time = user_shared_data->SystemTime.High2Time = now.u.HighPart;
    user_shared_data->u.TickCountQuad = (now.QuadPart - server_start_time) / 10000;
    user_shared_data->u.TickCount.High2Time = user_shared_data->u.TickCount.High1Time;
    user_shared_data->TickCountLowDeprecated = user_shared_data->u.TickCount.LowPart;
    user_shared_data->TickCountMultiplier = 1 << 24;

    fill_cpu_info();

    NtCreateKeyedEvent( &keyed_event, GENERIC_READ | GENERIC_WRITE, NULL, 0 );

    return exe_file;
}