BOOL WINAPI _CRT_INIT(
        HANDLE  hDllHandle,
        DWORD   dwReason,
        LPVOID  lpreserved
        )
{
        /*
         * If this is a process detach notification, check that there has
         * been a prior (successful) process attachment.
         */
        if ( dwReason == DLL_PROCESS_DETACH ) {
            if ( __proc_attached > 0 )
                __proc_attached--;
            else
                /*
                 * no prior process attach. just return failure.
                 */
                return FALSE;
        }

#ifdef _M_IX86

        /*
         * Set the local copy of the Pentium FDIV adjustment flag
         */

        _adjust_fdiv = * _imp___adjust_fdiv;

#endif  /* _M_IX86 */

        /*
         * do C++ constructors (initializers) specific to this DLL
         */

        if ( dwReason == DLL_PROCESS_ATTACH ) {
            /*
             * There is a possiblity that the module where this object is
             * linked into is a mixed module. In all the cases we gurantee
             * that native initialization will occur before managed
             * initialization.  Also in anycase this code should never be
             * called when some other code is initializing native code,
             * that's why we exit in that case.
             *
             * The case that is illegal is when managed code is executed for
             * the first time in loader lock. But there can be case when dll is
             * loaded in LoadLibrary and CLR could be already loaded in this
             * case it is perfectly OK to execute .cctor.
             */

            void *lock_free=0;
            void *fiberid=((PNT_TIB)NtCurrentTeb())->StackBase;

            int nested=FALSE;
            while((lock_free=InterlockedCompareExchangePointer((volatile PVOID *)&__native_startup_lock, fiberid, 0))!=0)
            {
                if(lock_free==fiberid)
                {
                    nested=TRUE;
                    break;
                }

                /* some other thread is running native startup/shutdown during a cctor/domain unload.
                    Should only happen if this DLL was built using the Everett-compat loader lock fix in vcclrit.h
                */
                /* wait for the other thread to complete init before we return */
                Sleep(1000);
            }

            if (__native_startup_state != __uninitialized)
            {
                _amsg_exit( _RT_CRT_INIT_CONFLICT);
            }
            else
            {
                /*
                * Set the native startup state to initializing.
                */
                __native_startup_state = __initializing;


                /*
                * Invoke C initializers.
                */

#ifndef _SYSCRT
                if (_initterm_e( __xi_a, __xi_z ) != 0)
                    return FALSE;
#else  /* _SYSCRT */
                _initterm((_PVFV *)(void *)__xi_a, (_PVFV *)(void *)__xi_z);
#endif  /* _SYSCRT */
                /*
                * Invoke C++ constructors
                */
                _initterm(__xc_a,__xc_z);

                /*
                * Set the native initialization state to initialized.
                */
                __native_startup_state = __initialized;
            }
            if(!nested)
            {
                /* For X86, the definition of InterlockedExchangePointer wrongly causes warning C4312 */
#pragma warning(push)
#pragma warning(disable:4312)
                InterlockedExchangePointer((volatile PVOID *)&__native_startup_lock,0);
#pragma warning(pop)
            }

            /*
             * If we have any dynamically initialized __declspec(thread)
             * variables, then invoke their initialization for the thread on
             * which the DLL is being loaded, by calling __dyn_tls_init through
             * a callback defined in tlsdyn.obj.  We can't rely on the OS
             * calling __dyn_tls_init with DLL_PROCESS_ATTACH because, on
             * Win2K3 and before, that call happens before the CRT is
             * initialized.
             */
            if (__dyn_tls_init_callback != NULL &&
                _IsNonwritableInCurrentImage((PBYTE)&__dyn_tls_init_callback))
            {
                __dyn_tls_init_callback(hDllHandle, DLL_THREAD_ATTACH,
                                        lpreserved);
            }

            /* Enable buffer count checking if linking against static lib */
            _CrtSetCheckCount(TRUE);

            /*
             * Increment the process attached flag.
             */
            __proc_attached++;

        }
        else if ( dwReason == DLL_PROCESS_DETACH )
        {

            /*
             * Any basic clean-up code that goes here must be
             * duplicated below in _DllMainCRTStartup for the
             * case where the user's DllMain() routine fails on a
             * Process Attach notification. This does not include
             * calling user C++ destructors, etc.
             */

            /*
             * do _onexit/atexit() terminators
             * (if there are any)
             *
             * These terminators MUST be executed in
             * reverse order (LIFO)!
             *
             * NOTE:
             *  This code assumes that __onexitbegin
             *  points to the first valid onexit()
             *  entry and that __onexitend points
             *  past the last valid entry. If
             *  __onexitbegin == __onexitend, the
             *  table is empty and there are no
             *  routines to call.
             */

            void *lock_free=0;
            while((lock_free=InterlockedCompareExchangePointer((volatile PVOID *)&__native_startup_lock, (PVOID)1, 0))!=0)
            {
                /* some other thread is running native startup/shutdown during a cctor/domain unload.
                    Should only happen if this DLL was built using the Everett-compat loader lock fix in vcclrit.h
                */
                /* wait for the other thread to complete init before we return */
                Sleep(1000);
            }

            if(__native_startup_state!=__initialized)
            {
                /* somehow we are in a very bad state running shutdown when we have not started */
                _amsg_exit( _RT_CRT_INIT_CONFLICT);
            }
            else
            {
                _PVFV * onexitbegin = (_PVFV *)_decode_pointer(__onexitbegin);
                if (onexitbegin)
                {
                    _PVFV * onexitend = (_PVFV *)_decode_pointer(__onexitend);
                    while ( --onexitend >= onexitbegin )
                        /*
                        * if current table entry is not
                        * NULL, call thru it.
                        */
                        if ( *onexitend != NULL )
                            (**onexitend)();

                    /*
                    * free the block holding onexit table to
                    * avoid memory leaks.  Also zero the ptr
                    * variables so that they are clearly cleaned up.
                    */

                    _free_crt ( onexitbegin ) ;

                    __onexitbegin = __onexitend = (_PVFV *)_encoded_null();
                }
                __native_startup_state = __uninitialized;
                /* For X86, the definition of InterlockedExchangePointer wrongly causes warning C4312 */
#pragma warning(push)
#pragma warning(disable:4312)
                InterlockedExchangePointer((volatile PVOID *)&__native_startup_lock,0);
#pragma warning(pop)
            }
       }

       return TRUE;
}