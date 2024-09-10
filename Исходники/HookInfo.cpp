HRESULT CNktHookInfoImpl::CurrentProcess(__deref_out INktProcess **ppProc)
{
    CNktSimpleLockNonReentrant cLock(&nLock);
    TNktComPtr<INktProcess> cIProc;
    HRESULT hRes;

    if (ppProc == NULL)
        return ::SetupErrorInfoAndReturn(IID_INktHookInfo, E_POINTER);
    *ppProc = NULL;
    if (nValid == 0)
        return ::SetupErrorInfoAndReturn(IID_INktHookInfo, E_FAIL);
    //get outer interface
    hRes = GetComLinkHelper<CNktProcessImpl,INktProcess,CNktDvProcess>(&cIProc, cProc, InterfaceItemGetCookies());
    //done (don't create dummy interface on error)
    *ppProc = cIProc.Detach();
    return ::SetupErrorInfoAndReturn(IID_INktHookInfo, hRes);
}