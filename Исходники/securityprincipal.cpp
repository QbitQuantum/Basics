INT32 QCALLTYPE COMPrincipal::ImpersonateLoggedOnUser(HANDLE hToken)
{
    QCALL_CONTRACT;

    HRESULT hr = S_OK;

    BEGIN_QCALL;

#ifdef FEATURE_INCLUDE_ALL_INTERFACES
        IHostSecurityManager *pSM = CorHost2::GetHostSecurityManager();
        if (pSM) {
            BEGIN_SO_TOLERANT_CODE_CALLING_HOST(GetThread());
            hr = pSM->ImpersonateLoggedOnUser(hToken);
            END_SO_TOLERANT_CODE_CALLING_HOST;
        }
        else 
#endif // FEATURE_INCLUDE_ALL_INTERFACES
        {
            if (!::ImpersonateLoggedOnUser(hToken))
                hr = HRESULT_FROM_GetLastError();
        }

    STRESS_LOG2(LF_SECURITY, LL_INFO100, "COMPrincipal::ImpersonateLoggedOnUser called with hTokenSAFE = %d. Returning 0x%x\n",hToken,hr);

    END_QCALL;

    return hr;
}