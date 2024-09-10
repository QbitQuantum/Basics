/**
* \ingroup atomvm
* \b atomvmCtrlRun
*
* This is an atomvm controll function used by a controlling thread
* and must not be called from the atom virtual machine.
*
* After a call to atomvmCtrlInit this function start the atom virtual machine.
* The calling thread will be used to manage interrupts and service calls in
* the virtual machine. This function will not return untill atomvmCtrlClose
* is called.
*
* @param[in] atomvm Handle to the virtual machine created by atomvmCtrlInit.
* @param[in] flags Reserved for later use.
*
* @return None
*/
void
atomvmCtrlRun (HATOMVM atomvm, uint32_t flags)
{
    PATOMVM             patomvm = (PATOMVM) atomvm ;
    HANDLE              wait[3] ;
    uint32_t            res ;
    uint32_t            wait_object ;
    PATOMVM_CALLBACK    service_call ;
#if defined DEBUG || defined _DEBUG
    BOOL                tls_res = 
#endif
        TlsSetValue (g_atomvm_tls_idx, (void*) atomvm) ;


    ATOMVM_ASSERT(tls_res, _T("TlsSetValue failed")) ;

    ResumeThread (patomvm->vm_thread) ;

    wait[0] = patomvm->atomvm_call ;
    wait[1] = patomvm->atomvm_int ;
    wait[2] = patomvm->atomvm_close ;

    for(;;) {

        wait_object = WaitForMultipleObjects (3, wait,FALSE,INFINITE) ;

        if (wait_object == WAIT_OBJECT_0) {

            ATOMVM_ATOMVM_PERF_COUNTER(patomvm, service_call) ;

            service_call = patomvm->service_call ;
            while (!service_call->lock) {
                SwitchToThread () ;
            }

            while ((res = SuspendThread (patomvm->vm_thread)) == (DWORD)-1) ;
            ATOMVM_ASSERT(res == 0 , _T("SuspendThread failed")) ;
#if (_WIN32_WINNT >= 0x0600)
            /*
                This is used for multi processor machines to ensure the thread
                is stopped before executing the next instruction. */
            FlushProcessWriteBuffers ();
#endif
            InterlockedExchange (&service_call->result, service_call->callback (patomvm, service_call)) ;
            InterlockedExchange (&service_call->lock, 0) ;
            ResetEvent (patomvm->atomvm_call) ;
            res = ResumeThread (patomvm->vm_thread) ;
            ATOMVM_ASSERT(res == 1 , _T("ResumeThread failed")) ;
            

        }

        else if (wait_object == WAIT_OBJECT_0 + 1) {

            if (patomvm->current_context->critical_count == 0) {

                while ((res = SuspendThread (patomvm->vm_thread)) == (DWORD)-1) ;
                ATOMVM_ASSERT(res == 0 , _T("SuspendThread failed")) ;
#if (_WIN32_WINNT >= 0x0600)
                /*
                    This is used for multi processor machines to ensure the thread
                    is stopped before executing the next instruction. */
                FlushProcessWriteBuffers ();
#endif
                if (patomvm->current_context->critical_count == 0) {

                    ATOMVM_ATOMVM_PERF_COUNTER(patomvm, int_request) ;

                    patomvm->status_isr++ ;
                    patomvm->isr () ;
                    patomvm->status_isr-- ;

                    res = ResumeThread (patomvm->vm_thread) ;
                    ATOMVM_ASSERT(res == 1 , _T("ResumeThread failed")) ;
                    
                    ResetEvent (patomvm->atomvm_int) ;
                    InterlockedExchange ((volatile uint32_t*)&patomvm->isr, 0) ;
                    SetEvent (patomvm->atomvm_int_complete) ;

                } else {

                    res = ResumeThread (patomvm->vm_thread) ;
                    ATOMVM_ASSERT(res == 1 , _T("ResumeThread failed")) ;
                    SwitchToThread () ;

                }

            } else {

                SwitchToThread () ;

            }

        } else if (wait_object == WAIT_OBJECT_0 + 2) {

            break ;

        } else {

            ATOMVM_ASSERT(res == 1 , _T("WaitForMultipleObjects failed")) ;

        }

    }

}