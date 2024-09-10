void __unregister_hs_exception_handler( void )
{
    if (__hs_handle != NULL)
    {
        // Should the return value be checked? we're terminating anyway. 
        RemoveVectoredExceptionHandler(__hs_handle);
        __hs_handle = NULL;
    }
    else
    {
        errorBelch("__unregister_hs_exception_handler() called without having called __register_hs_exception_handler() first.");
    }
}