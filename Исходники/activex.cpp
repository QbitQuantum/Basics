    //*************************IOleInPlaceSiteEx***********************
    HRESULT STDMETHODCALLTYPE OnInPlaceActivateEx(BOOL * pfNoRedraw, DWORD)
    {
#ifdef __WXWINCE__
        IRunnableObject* runnable = NULL;
        HRESULT hr = QueryInterface(
            IID_IRunnableObject, (void**)(& runnable));
        if (SUCCEEDED(hr))
        {
            runnable->LockRunning(TRUE, FALSE);
        }
#else
        OleLockRunning(m_window->m_ActiveX, TRUE, FALSE);
#endif
        if (pfNoRedraw)
            (*pfNoRedraw) = FALSE;
        return S_OK;
    }