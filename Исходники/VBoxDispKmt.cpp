HRESULT vboxDispKmtCallbacksInit(PVBOXDISPKMT_CALLBACKS pCallbacks)
{
    HRESULT hr = S_OK;

    memset(pCallbacks, 0, sizeof (*pCallbacks));

    pCallbacks->hGdi32 = LoadLibraryW(L"gdi32.dll");
    if (pCallbacks->hGdi32 != NULL)
    {
        bool bSupported = true;
        bool bSupportedWin8 = true;
        pCallbacks->pfnD3DKMTOpenAdapterFromHdc = (PFND3DKMT_OPENADAPTERFROMHDC)GetProcAddress(pCallbacks->hGdi32, "D3DKMTOpenAdapterFromHdc");
        Log((__FUNCTION__"pfnD3DKMTOpenAdapterFromHdc = %p\n", pCallbacks->pfnD3DKMTOpenAdapterFromHdc));
        bSupported &= !!(pCallbacks->pfnD3DKMTOpenAdapterFromHdc);

        pCallbacks->pfnD3DKMTOpenAdapterFromGdiDisplayName = (PFND3DKMT_OPENADAPTERFROMGDIDISPLAYNAME)GetProcAddress(pCallbacks->hGdi32, "D3DKMTOpenAdapterFromGdiDisplayName");
        Log((__FUNCTION__": pfnD3DKMTOpenAdapterFromGdiDisplayName = %p\n", pCallbacks->pfnD3DKMTOpenAdapterFromGdiDisplayName));
        bSupported &= !!(pCallbacks->pfnD3DKMTOpenAdapterFromGdiDisplayName);

        pCallbacks->pfnD3DKMTCloseAdapter = (PFND3DKMT_CLOSEADAPTER)GetProcAddress(pCallbacks->hGdi32, "D3DKMTCloseAdapter");
        Log((__FUNCTION__": pfnD3DKMTCloseAdapter = %p\n", pCallbacks->pfnD3DKMTCloseAdapter));
        bSupported &= !!(pCallbacks->pfnD3DKMTCloseAdapter);

        pCallbacks->pfnD3DKMTEscape = (PFND3DKMT_ESCAPE)GetProcAddress(pCallbacks->hGdi32, "D3DKMTEscape");
        Log((__FUNCTION__": pfnD3DKMTEscape = %p\n", pCallbacks->pfnD3DKMTEscape));
        bSupported &= !!(pCallbacks->pfnD3DKMTEscape);

        pCallbacks->pfnD3DKMTCreateDevice = (PFND3DKMT_CREATEDEVICE)GetProcAddress(pCallbacks->hGdi32, "D3DKMTCreateDevice");
        Log((__FUNCTION__": pfnD3DKMTCreateDevice = %p\n", pCallbacks->pfnD3DKMTCreateDevice));
        bSupported &= !!(pCallbacks->pfnD3DKMTCreateDevice);

        pCallbacks->pfnD3DKMTDestroyDevice = (PFND3DKMT_DESTROYDEVICE)GetProcAddress(pCallbacks->hGdi32, "D3DKMTDestroyDevice");
        Log((__FUNCTION__": pfnD3DKMTDestroyDevice = %p\n", pCallbacks->pfnD3DKMTDestroyDevice));
        bSupported &= !!(pCallbacks->pfnD3DKMTDestroyDevice);

        pCallbacks->pfnD3DKMTCreateContext = (PFND3DKMT_CREATECONTEXT)GetProcAddress(pCallbacks->hGdi32, "D3DKMTCreateContext");
        Log((__FUNCTION__": pfnD3DKMTCreateContext = %p\n", pCallbacks->pfnD3DKMTCreateContext));
        bSupported &= !!(pCallbacks->pfnD3DKMTCreateContext);

        pCallbacks->pfnD3DKMTDestroyContext = (PFND3DKMT_DESTROYCONTEXT)GetProcAddress(pCallbacks->hGdi32, "D3DKMTDestroyContext");
        Log((__FUNCTION__": pfnD3DKMTDestroyContext = %p\n", pCallbacks->pfnD3DKMTDestroyContext));
        bSupported &= !!(pCallbacks->pfnD3DKMTDestroyContext);

        pCallbacks->pfnD3DKMTRender = (PFND3DKMT_RENDER)GetProcAddress(pCallbacks->hGdi32, "D3DKMTRender");
        Log((__FUNCTION__": pfnD3DKMTRender = %p\n", pCallbacks->pfnD3DKMTRender));
        bSupported &= !!(pCallbacks->pfnD3DKMTRender);

        pCallbacks->pfnD3DKMTCreateAllocation = (PFND3DKMT_CREATEALLOCATION)GetProcAddress(pCallbacks->hGdi32, "D3DKMTCreateAllocation");
        Log((__FUNCTION__": pfnD3DKMTCreateAllocation = %p\n", pCallbacks->pfnD3DKMTCreateAllocation));
        bSupported &= !!(pCallbacks->pfnD3DKMTCreateAllocation);

        pCallbacks->pfnD3DKMTDestroyAllocation = (PFND3DKMT_DESTROYALLOCATION)GetProcAddress(pCallbacks->hGdi32, "D3DKMTDestroyAllocation");
        Log((__FUNCTION__": pfnD3DKMTDestroyAllocation = %p\n", pCallbacks->pfnD3DKMTDestroyAllocation));
        bSupported &= !!(pCallbacks->pfnD3DKMTDestroyAllocation);

        pCallbacks->pfnD3DKMTLock = (PFND3DKMT_LOCK)GetProcAddress(pCallbacks->hGdi32, "D3DKMTLock");
        Log((__FUNCTION__": pfnD3DKMTLock = %p\n", pCallbacks->pfnD3DKMTLock));
        bSupported &= !!(pCallbacks->pfnD3DKMTLock);

        pCallbacks->pfnD3DKMTUnlock = (PFND3DKMT_UNLOCK)GetProcAddress(pCallbacks->hGdi32, "D3DKMTUnlock");
        Log((__FUNCTION__": pfnD3DKMTUnlock = %p\n", pCallbacks->pfnD3DKMTUnlock));
        bSupported &= !!(pCallbacks->pfnD3DKMTUnlock);

        pCallbacks->pfnD3DKMTEnumAdapters = (PFND3DKMT_ENUMADAPTERS)GetProcAddress(pCallbacks->hGdi32, "D3DKMTEnumAdapters");
        Log((__FUNCTION__": pfnD3DKMTEnumAdapters = %p\n", pCallbacks->pfnD3DKMTEnumAdapters));
        /* this present starting win8 release preview only, so keep going if it is not available,
         * i.e. do not clear the bSupported on its absence */
        bSupportedWin8 &= !!(pCallbacks->pfnD3DKMTEnumAdapters);
#ifdef DEBUG_misha
        /* just a debug assertion to test it on win8 */
        Assert(pCallbacks->pfnD3DKMTEnumAdapters);
#endif

        pCallbacks->pfnD3DKMTOpenAdapterFromLuid = (PFND3DKMT_OPENADAPTERFROMLUID)GetProcAddress(pCallbacks->hGdi32, "D3DKMTOpenAdapterFromLuid");
        Log((__FUNCTION__": pfnD3DKMTOpenAdapterFromLuid = %p\n", pCallbacks->pfnD3DKMTOpenAdapterFromLuid));
        /* this present starting win8 release preview only, so keep going if it is not available,
         * i.e. do not clear the bSupported on its absence */
        bSupportedWin8 &= !!(pCallbacks->pfnD3DKMTOpenAdapterFromLuid);
#ifdef DEBUG_misha
        /* just a debug assertion to test it on win8 */
        Assert(pCallbacks->pfnD3DKMTOpenAdapterFromLuid);
        Assert(bSupportedWin8);
#endif

        /*Assert(bSupported);*/
        if (bSupported)
        {
            if (bSupportedWin8)
                pCallbacks->enmVersion = VBOXDISPKMT_CALLBACKS_VERSION_WIN8;
            else
                pCallbacks->enmVersion = VBOXDISPKMT_CALLBACKS_VERSION_VISTA_WIN7;
            return S_OK;
        }
        else
        {
            Log((__FUNCTION__": one of pfnD3DKMT function pointers failed to initialize\n"));
            hr = E_NOINTERFACE;
        }

        FreeLibrary(pCallbacks->hGdi32);
    }
    else
    {
        DWORD winEr = GetLastError();
        hr = HRESULT_FROM_WIN32(winEr);
        Assert(0);
        Assert(hr != S_OK);
        Assert(hr != S_FALSE);
        if (hr == S_OK || hr == S_FALSE)
            hr = E_FAIL;
    }

    return hr;
}