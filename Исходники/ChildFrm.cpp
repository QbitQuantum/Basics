BOOL CChildFrame::OpenCompositeDocument(LPCTSTR lpszFileName) 
{ 
    USES_CONVERSION; 

    CWaitCursor wait; 

    HRESULT hResult = E_FAIL; 
    IStorage * ptrRootStg = NULL; // root storage 
    HWND hWnd = (HWND)m_hWnd; 

    hResult = ::StgIsStorageFile( T2COLE(m_szFileName) ); 
    if( S_OK != hResult ) 
    { 
        TCHAR szFmt[MAX_PATH] = { 0 }; 
        AtlLoadString(IDS_OPEN_ARCHIVE_ERROR, szFmt, _countof(szFmt)); 

        TCHAR szOut[MAX_PATH*2] = { 0 }; 
        wnsprintf(szOut, _countof(szOut), szFmt, lpszFileName); 

        AtlMessageBox(m_hWnd, szOut, IDS_ERROR, MB_OK|MB_ICONSTOP); 
        return FALSE; 
    }

    // open the Compound document 
    hResult = ::StgOpenStorage( T2COLE(m_szFileName), NULL, 
        STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 
        0, 0, &ptrRootStg ); 
    if( FAILED(hResult) )
    { 
        TCHAR szFmt[MAX_PATH] = { 0 }; 
        AtlLoadString(IDS_OPEN_FILE_ERROR, szFmt, _countof(szFmt)); 

        TCHAR szError[MAX_PATH] = { 0 }; 

        TCHAR szOut[MAX_PATH*2] = { 0 }; 
        wnsprintf(szOut, _countof(szOut), szFmt, 
            lpszFileName, GetErrorString(S_OK, szError, _countof(szError))); 

        AtlMessageBox(m_hWnd, szOut, IDS_ERROR, MB_OK|MB_ICONSTOP); 
        return FALSE;
    } 

    TREE_ITEM_DATA * pRootData = new TREE_ITEM_DATA(ptrRootStg, STGTY_STORAGE); 

    HTREEITEM hRoot = m_wndCatalog.InsertItem ( 
        TVIF_IMAGE|TVIF_TEXT|TVIF_PARAM|TVIF_SELECTEDIMAGE, 
        PathFindFileName(m_szFileName), 
        0, 1, TVIS_EXPANDED, 0, 
        reinterpret_cast<LPARAM>(pRootData), 
        NULL, NULL); 


    std::stack < StgInfo > FolderStack; 
    HTREEITEM htiParent = hRoot; 
    IEnumSTATSTG * ptrEnum = NULL; 

    hResult = ptrRootStg->EnumElements( 0, NULL, 0, &ptrEnum ); 
    if( FAILED(hResult) ) { 
        ptrRootStg->Release(); 
        return 0; 
    } 

    TCHAR szSwap[MAX_PATH] = { 0 }; 

	LARGE_INTEGER nStorageLength;
	nStorageLength.QuadPart = 0;
    STATSTG StatStg = { 0 }; 
    while( S_OK == hResult ) 
    { 
        hResult = ptrEnum->Next( 1, &StatStg, NULL ); 
        if( S_FALSE == hResult ) 
        { 
            ptrRootStg->Release(); 
            ptrEnum->Release(); 

            // m_wndCatalog.Expand(strFolder); 

            if( !FolderStack.empty() ) 
            { 
				TCHAR szCurText[MAX_PATH] = {0};
				m_wndCatalog.GetItemText(htiParent, szCurText, _countof(szCurText));
				CString strTotal;
				strTotal.Format(TEXT("%s(%ld)"), szCurText, nStorageLength);
				m_wndCatalog.SetItemText(htiParent, strTotal);

				ptrRootStg  = FolderStack.top().pStg; 
                ptrEnum     = FolderStack.top().pEnum; 
                htiParent   = FolderStack.top().hParent; 
                FolderStack.pop(); 

                hResult = S_OK; 
            } 

            continue; 
        } 

        switch(StatStg.type) 
        { 
        case STGTY_STORAGE: // 是存储对象, "文件夹" 
            { 
				//先清零
				nStorageLength.QuadPart = 0;
                IStorage * ptrChildStg = NULL;

                HRESULT hr = ptrRootStg->OpenStorage( StatStg.pwcsName, NULL, 
                    STGM_READWRITE|STGM_SHARE_EXCLUSIVE, 
                    0, 0, &ptrChildStg ); 
                if( SUCCEEDED(hr) ) 
                { 
                    TREE_ITEM_DATA * pData = new TREE_ITEM_DATA(ptrChildStg, StatStg.type); 

                    HTREEITEM hFolder = m_wndCatalog.InsertItem ( 
                        TVIF_IMAGE|TVIF_TEXT|TVIF_PARAM|TVIF_SELECTEDIMAGE, 
                        WCHAR2TCHAR(StatStg.pwcsName, szSwap, _countof(szSwap)), 
                        0, 1, TVIS_EXPANDED, 0, 
                        reinterpret_cast<LPARAM>(pData), 
                        htiParent, NULL); 

                    // 父存储入栈 
                    FolderStack.push( StgInfo(ptrRootStg, ptrEnum, htiParent) );

                    // 子存储替代父存储 
                    ptrRootStg = ptrChildStg; 
                    htiParent = hFolder; 
                    hr = ptrChildStg->EnumElements( 0, NULL, 0, &ptrEnum ); 
                } 
            } 
            break; 
        case STGTY_STREAM:  // 是流, "文件" 
            { 
                CComPtr<IStream> spStream; 
                HRESULT hr = ptrRootStg->OpenStream(StatStg.pwcsName, NULL, 
                    STGM_READWRITE|STGM_SHARE_EXCLUSIVE, 0, &spStream); 
                ATLASSERT(SUCCEEDED(hr)); 
				
				LARGE_INTEGER nSeekPos;
				nSeekPos.QuadPart = 0LL;
				ULARGE_INTEGER nLength = {0};
				hr = spStream->Seek(nSeekPos, STREAM_SEEK_END, &nLength);
				CString strStreamName;
				WCHAR2TCHAR(StatStg.pwcsName, szSwap, _countof(szSwap));
				if (SUCCEEDED(hr))
				{
					nStorageLength.QuadPart += nLength.QuadPart;
					strStreamName.Format(TEXT("%s(%ld)"), szSwap, nLength);
				}
				else
				{
					strStreamName.Format(TEXT("%s(0)"), szSwap);
				}
                TREE_ITEM_DATA * pData = new TREE_ITEM_DATA(spStream, StatStg.type); 
                m_wndCatalog.InsertItem ( 
                    TVIF_IMAGE|TVIF_TEXT|TVIF_PARAM|TVIF_SELECTEDIMAGE, 
                    strStreamName, 
                    2, 2, TVIS_EXPANDED, 0, 
                    reinterpret_cast<LPARAM>(pData), 
                    htiParent, NULL); 
            } 
            break; 
        case STGTY_LOCKBYTES: 
            ATLTRACE(_T("===== STGTY_LOCKBYTES %d ====="), StatStg.type); 
            break; 
        case STGTY_PROPERTY: 
            ATLTRACE(_T("===== STGTY_PROPERTY %d ====="), StatStg.type); 
            break; 
        default: 
            ATLASSERT(!_T("Unknown storage type!!!")); 
            break; 
        } 

        ::CoTaskMemFree( StatStg.pwcsName ); // 释放名称所使用的内存 
    }

    return 0;
}