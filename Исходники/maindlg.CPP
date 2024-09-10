/***********************************************************************
* OnInitDialog
* 
* Initialize member variables of handlers
* Initialize WMP OCX
***********************************************************************/
LRESULT CMainDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    ::InitCommonControls();
    AtlAxWinInit();
    
    // dialog items
    m_hLibTree = GetDlgItem(IDC_TREE);
    m_hDetailList = GetDlgItem(IDC_DETAILLIST);
    
    // Create a WMP OCX
    CreateWmpOcx();
    
    // Fill in combo box for media type
    HWND    hMediaTypeList = GetDlgItem(IDC_MEDIATYPELIST);
    SendMessage(hMediaTypeList, CB_ADDSTRING, 0, (LPARAM)L"Music");
    SendMessage(hMediaTypeList, CB_ADDSTRING, 0, (LPARAM)L"Pictures");
    SendMessage(hMediaTypeList, CB_ADDSTRING, 0, (LPARAM)L"Video");
    SendMessage(hMediaTypeList, CB_ADDSTRING, 0, (LPARAM)L"Playlists");
    SendMessage(hMediaTypeList, CB_ADDSTRING, 0, (LPARAM)L"Other Media");
    SendMessage(hMediaTypeList, CB_SETCURSEL, 0, (LPARAM)m_mtCurMediaType);
    
    // Use IWMPLibraryServices to enumerate the libries and fill in combo box
    HRESULT                         hr = E_POINTER;
    LONG                            lLibCount = 0;
    HWND                            hLibList = GetDlgItem(IDC_LIBLIST);
    CComPtr<IWMPLibraryServices>    spLibSvc;
    
    if(m_spPlayer != NULL)
    {
        hr = m_spPlayer->QueryInterface(&spLibSvc);
    }
    if(SUCCEEDED(hr) && spLibSvc)
    {
        hr = spLibSvc->getCountByType(wmpltAll, &lLibCount);
    }
    if(SUCCEEDED(hr))
    {
        for(LONG i = 0; i < lLibCount; i++)
        {
            CComPtr<IWMPLibrary>    spLib;
            CComBSTR                bstrLibName;
            
            hr = spLibSvc->getLibraryByType(wmpltAll, i , &spLib);
            if(SUCCEEDED(hr) && spLib)
            {
                hr = spLib->get_name(&bstrLibName);
            }
            if(SUCCEEDED(hr))
            {
                SendMessage(hLibList, CB_ADDSTRING, 0, (LPARAM)bstrLibName.m_str);
            }
        }
    }
    SendMessage(hLibList, CB_SETCURSEL, 0, 0);
    
    // Set WordWheel text to Search...
    SetDlgItemText(IDC_WORDWHEEL, L"Search...");
    
    // Set m_spMC to correct mediaCollection of currently selected library
    UpdateCurMC();

    // Now we try to build the tree
    BuildLibTree();
    
    return 0;
}