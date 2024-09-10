// ----------------------------------------------------------------------------
// Function:
//      CSwapPropPage::AddPages
//
// Description:
//      Implementation of IShellPropSheetExt::AddPages. Adds one or more pages
//      to a property sheet that the Shell displays for a file object.
//
// Parameters:
//      lpfnAddPage - [in] Address of a function that the property sheet
//                    handler calls to add a page to the property sheet. The
//                    function takes a property sheet handle returned by the
//                    CreatePropertySheetPage function and the lParam parameter
//                    passed to the AddPages method. 
//      lParam - [in] Parameter to pass to the function specified by the
//               lpfnAddPage method.
//
// Return values:
//      Returns S_OK if successful. If the method fails, an OLE-defined error
//      code is returned
// ----------------------------------------------------------------------------
_Use_decl_annotations_
HRESULT STDMETHODCALLTYPE CSwapPropPage::AddPages
(
    LPFNADDPROPSHEETPAGE    lpfnAddPage,    // See PrSht.h
    LPARAM                  lParam          // Used by caller, don't modify
)
{
    HRESULT                 hr = S_OK;
    PROPSHEETPAGE           psp;
    HPROPSHEETPAGE          hPage1 = NULL;
    AudioFXExtensionParams* pAudioFXParams = (AudioFXExtensionParams*)lParam;
#pragma warning(push)
#pragma warning(disable: 28197)
    AudioFXExtensionParams* pAudioFXParamsCopy = new AudioFXExtensionParams;
#pragma warning(pop)

    if (pAudioFXParamsCopy == NULL)
    {
        return E_OUTOFMEMORY;
    }

    // Make a copy of the params
    CopyMemory(pAudioFXParamsCopy, pAudioFXParams, sizeof(AudioFXExtensionParams));
    SAFE_ADDREF(pAudioFXParamsCopy->pFxProperties);

    // Initialize property page params and create page
    psp.dwSize        = sizeof(psp);
    psp.dwFlags       = PSP_USEREFPARENT | PSP_USECALLBACK;
    psp.hInstance     = _AtlBaseModule.GetModuleInstance();
    psp.hIcon         = 0;
    psp.pcRefParent   = (UINT*)&m_dwRef;
    psp.lParam        = (LPARAM)pAudioFXParamsCopy;
    psp.pszTemplate   = MAKEINTRESOURCE(IDD_SWAP_PROP_PAGE);
    psp.pfnDlgProc    = (DLGPROC)DialogProcPage1;
    psp.pfnCallback   = PropSheetPageProc;

    // Create the property sheet page and add the page
    hPage1 = CreatePropertySheetPage(&psp);
    if (hPage1)
    {
        if (!lpfnAddPage(hPage1, pAudioFXParams->AddPageParam))
        {
            hr = E_FAIL;
            delete pAudioFXParamsCopy;
            DestroyPropertySheetPage(hPage1);
        }
        else
        {
            // Add ref for page
            this->AddRef();
        }
    }
    else
    {
        delete pAudioFXParamsCopy;
        hr = E_OUTOFMEMORY;
    }

    return(hr);
}