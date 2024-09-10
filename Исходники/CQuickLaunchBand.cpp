/*++
* @name FinalConstruct
*
* Creates an instance of CISFBand, and initializes its Shell Folder Band for enumeration.
*
* @return The error code.
*
*--*/
    HRESULT CQuickLaunchBand::FinalConstruct()
    {
        HRESULT hr = RSHELL_CISFBand_CreateInstance(IID_PPV_ARG(IUnknown, &m_punkISFB));
        if (FAILED_UNEXPECTEDLY(hr))
            return hr;

        CComPtr<IShellFolderBand> pISFB;
        hr = m_punkISFB->QueryInterface(IID_PPV_ARG(IShellFolderBand, &pISFB));
        if (FAILED_UNEXPECTEDLY(hr))
            return hr;

        CComPtr<IShellFolder> pISF;
        hr = SHGetDesktopFolder(&pISF);
        if (FAILED_UNEXPECTEDLY(hr))
            return hr;

        CComHeapPtr<ITEMIDLIST> pidl(PidlBrowse(m_hWndBro, CSIDL_DESKTOP));
        if (pidl == NULL)
            return E_FAIL;
        pISFB->InitializeSFB(pISF, pidl);
        
        return hr;
    }