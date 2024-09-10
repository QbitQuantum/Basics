BOOL AeroAutoSubclass(HWND hWnd, DWORD dwFlags, DWORD dwReserved)
{
    if(!hWnd || !IsWindow(hWnd) || 0L!=dwReserved)  
    {
        SetLastError(ERROR_INVALID_PARAMETER);        
        return FALSE;
    }

    UINT uiRedrawMsg = RegisterWindowMessage(REDRAWSTRING);
    if(!uiRedrawMsg)
        return FALSE; // use the RegisterWindowMessage last error

    CDwmApiImpl *pDwm = NULL;
    CUxThemeAeroImpl *pUxTheme = NULL;
    PAERO_SUBCLASS_WND_DATA pWndData = NULL;
    DWORD dwLastError = ERROR_SUCCESS;
    MARGINS marGlassInset = {0,0,0,302};
    HRESULT hRes = S_OK;
    bool bBufferedPaintInitialized = false;
    ERROR_PARENT_AERO_SUBCLASS_WND_DATA errParentAeroData;
    ZeroMemory(&errParentAeroData, sizeof(errParentAeroData));
    errParentAeroData.m_dwFlags = dwFlags;
    errParentAeroData.m_hWndParent = hWnd;

    try
    {
        pDwm = new CDwmApiImpl;
    }
    catch (...)
    {
        dwLastError = ERROR_NOT_ENOUGH_MEMORY;
    }

    if(ERROR_SUCCESS!=dwLastError)
        goto CLEANUP;

    try
    {
        pUxTheme = new CUxThemeAeroImpl;
    }
    catch (...)
    {
        dwLastError = ERROR_NOT_ENOUGH_MEMORY;
    }

    if(ERROR_SUCCESS!=dwLastError)
        goto CLEANUP;

    pWndData = (PAERO_SUBCLASS_WND_DATA)LocalAlloc(LPTR, sizeof(AERO_SUBCLASS_WND_DATA));
    if(!pWndData)
    {
        dwLastError = GetLastError();
        goto CLEANUP;
    }

    if(!pDwm->Initialize())
    {
        dwLastError = GetLastError();
        goto CLEANUP;
    }

    if(!pUxTheme->Initialize())
    {
        dwLastError = GetLastError();
        goto CLEANUP;
    }

    if(pDwm->IsDwmCompositionEnabled() && !(dwFlags&ASC_NO_FRAME_EXTENSION))
    {
        /// 
        /// we do not evaluate the return value of pDwm->DwmExtendFrameIntoClientArea, because
        /// if composition is turned off in the tiny little race condition after the previous call
        /// to IsDwmCompositionEnabled and before the following call to DwmExtendFrameIntoClientArea,
        /// we would see DwmExtendFrameIntoClientArea fail. However, if composition is turned on again 
        /// aterwards, the UI can display composition again without problems:
        /// 
        pDwm->DwmExtendFrameIntoClientArea(hWnd, &marGlassInset);
    }

    hRes = pUxTheme->BufferedPaintInit();
    if(FAILED(hRes))
    {
        dwLastError = hRes;
        goto CLEANUP;
    }
    bBufferedPaintInitialized = true;

    if(!SetProp(hWnd, WINDOW_DATA_STRING, pWndData))
    {
        dwLastError = hRes;
        goto CLEANUP;
    }

    errParentAeroData.m_pdwError = &dwLastError;
    errParentAeroData.m_pWndParentAeroData = pWndData;
    pWndData->m_pDwmApiImpl = pDwm;
    pWndData->m_pUxTheme = pUxTheme;
    pWndData->m_uiRedrawMsg = uiRedrawMsg;

    if(dwFlags&ASC_NO_FRAME_EXTENSION)
        pWndData->m_dwFlags |= WD_NO_FRAME_EXTEND;

    if(!EnumChildWindows(hWnd, SubclassChildWindows, (LPARAM)&errParentAeroData))
    {
        if(ERROR_SUCCESS==dwLastError)
            dwLastError = GetLastError();
        goto CLEANUP;
    }
    
    
    if(ERROR_SUCCESS!=dwLastError)
        goto CLEANUP;


    pWndData->m_oldWndProc = (WNDPROC) SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR) WndProcc);
    if(!pWndData->m_oldWndProc)
    {
        dwLastError = GetLastError();
        goto CLEANUP;
    }




CLEANUP:

    if(ERROR_SUCCESS!=dwLastError)
    {
        RemoveProp(hWnd, WINDOW_DATA_STRING); // don't care if this fails


        if(pDwm)
            delete pDwm;
        if(pUxTheme)
        {
            if(bBufferedPaintInitialized)
                pUxTheme->BufferedPaintUnInit();
                
            delete pUxTheme;
        }
        if(pWndData)
            VERIFY(!LocalFree(pWndData));

        SetLastError(dwLastError);
        return FALSE;
    }

    return TRUE;
}