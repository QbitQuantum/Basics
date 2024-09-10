    void DeActivate()
    {
        if ( ActivationCtxHandle == INVALID_HANDLE_VALUE )
        {
            return ;
        }

        if ( ActivationCtxCookie == 0 )
        {
            // Already Deactivated
            return ;
        }
        ULONG_PTR cookie = ActivationCtxCookie;
        ActivationCtxCookie = 0;
        if ( DeactivateActCtx( 0, cookie ) == FALSE )
        {
            ErrorMessage = L"The C++ module failed to Deactivate WinSXS Activation Context.\n";
            ThrowModuleLoadException(ErrorMessage);
        }
    }