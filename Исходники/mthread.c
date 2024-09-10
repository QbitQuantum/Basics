void __InitMultipleThread( void )
/*******************************/
{
    if( __GetThreadPtr != __MultipleThread ) {
  #if defined( _NETWARE_CLIB )
        {
        /* __ThreadData[ 0 ] is used whenever GetThreadID() returns a pointer
           not in our __ThreadIDs list - ie. whenever it returns NULL, a
           pointer to a thread we didn't create, or an invalid pointer */
            void *ptr;
            ptr = lib_calloc( 1, __ThreadDataSize );
            if( ptr == NULL ) {
                __fatal_runtime_error(
                    "Unable to allocate thread-specific data", 1 );
            }
            __ThreadData[ 0 ].data = ptr;
            __ThreadData[ 0 ].allocated_entry = 1;
            __ThreadData[ 0 ].data->__allocated = 1;
            __ThreadData[ 0 ].data->__randnext = 1;
            __ThreadData[ 0 ].data->__data_size = __ThreadDataSize;
            if( __initthread( ptr ) ) {
                lib_free( ptr );
                __fatal_runtime_error(
                    "Unable to initialize thread-specific data", 1 );
            }
            ptr = lib_calloc( 1, __ThreadDataSize );
            if( ptr == NULL ) {
                __fatal_runtime_error(
                    "Unable to allocate thread-specific data", 1 );
            }
            __FirstThreadData = ptr;
            __FirstThreadData->__allocated = 1;
            __FirstThreadData->__randnext = 1;
            __FirstThreadData->__data_size = __ThreadDataSize;
            __ThreadData[ 1 ].data = __FirstThreadData;
            __ThreadData[ 1 ].allocated_entry = __FirstThreadData->__allocated;
            __ThreadIDs[ 1 ] = GetThreadID();
            if( __initthread( ptr ) ) {
                lib_free( ptr );
                __fatal_runtime_error(
                    "Unable to initialize thread-specific data", 1 );
            }
        }
  #elif defined( _NETWARE_LIBC )
        InitSemaphore.semaphore     = 0;    /* sema4 is mutex in this case */
        InitSemaphore.initialized   = 1;
        //_ThreadExitRtn = &__ThreadExit;   - might need this at some point??
        // Note: __AddThreadData uses the InitSemaphore, _AccessTDList & _ReleaseTDList

        __FirstThreadData->thread_id = GetCurrentThreadId();

        __AddThreadData( __FirstThreadData->thread_id, __FirstThreadData );
        if(0 != NXKeySetValue(__NXSlotID, __FirstThreadData)) {
            __fatal_runtime_error(
                "Unable to initialize thread-specific data", 1 );
        }
  #elif defined( __NT__ )
        InitSemaphore.semaphore = __NTGetCriticalSection();
        InitSemaphore.initialized = 1;
        _ThreadExitRtn = &__ThreadExit;
        // Note: __AddThreadData uses the InitSemaphore, _AccessTDList & _ReleaseTDList
        __AddThreadData( __FirstThreadData->thread_id, __FirstThreadData );
        TlsSetValue( __TlsIndex, __FirstThreadData );
  #elif defined( __QNX__ )
        __qsem_init( &InitSemaphore.semaphore, 1, 1 );
        InitSemaphore.initialized = 1;
        // first thread data already in magic memory
  #elif defined( __LINUX__ )
        // TODO: Init semaphores for Linux
  #elif defined( __RDOS__ )
        InitSemaphore.semaphore = RdosCreateSection();
        InitSemaphore.initialized = 1;
        __AddThreadData( __FirstThreadData->thread_id, __FirstThreadData );
        __tls_set_value( __TlsIndex, __FirstThreadData );
  #elif defined( __RDOSDEV__ )
        RdosInitKernelSection( &InitSemaphore.semaphore );
        InitSemaphore.initialized = 1;
  #elif defined( __OS2__ )
        DosCreateMutexSem( NULL, &InitSemaphore.semaphore, 0, FALSE );
        InitSemaphore.initialized = 1;
        __ThreadData[1].data = __FirstThreadData;
        __ThreadData[1].allocated_entry = __FirstThreadData->__allocated;
  #else
    #error Multiple thread support is not defined for this platform
  #endif

  #if !defined( _M_I86 )
    // Set these up after we have created the InitSemaphore
    #if !defined (_THIN_LIB)
        _AccessFileH      = &__AccessFileH;
        _ReleaseFileH     = &__ReleaseFileH;
        _AccessIOB        = &__AccessIOB;
        _ReleaseIOB       = &__ReleaseIOB;
    #endif
        _AccessTDList     = &__AccessTDList;
        _ReleaseTDList    = &__ReleaseTDList;
        __AccessSema4     = &__AccessSemaphore;
        __ReleaseSema4    = &__ReleaseSemaphore;
        __CloseSema4      = &__CloseSemaphore;
    #if !defined( __NETWARE__ )
        _AccessNHeap  = &__AccessNHeap;
        _AccessFHeap  = &__AccessFHeap;
        _ReleaseNHeap = &__ReleaseNHeap;
        _ReleaseFHeap = &__ReleaseFHeap;
    #endif
    #if defined( __NT__ )
        _AccessFList  = &__AccessFList;
        _ReleaseFList = &__ReleaseFList;
    #endif
  #endif
        __GetThreadPtr  = __MultipleThread;
    }
}