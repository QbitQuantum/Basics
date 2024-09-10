LRESULT CSEShellView::OnNotify( LPNMHDR pNmhdr )
{
    TRACE_FUNCTION();
    if( pNmhdr )
    {
        if( pNmhdr->code == NM_DBLCLK )
        {
            int iIndex = ListView_GetNextItem( m_hWnd, -1, LVNI_FOCUSED );
            if (iIndex == -1)
            {
                return S_OK;
            }
            LV_ITEM item = {0};
            item.iItem = iIndex;
            item.iSubItem = 0;
            item.mask = LVIF_PARAM;
            ListView_GetItem( m_hWnd, &item );
            if ( item.lParam )
            {               
                LPITEMIDLIST pItem = m_pidlManager.Copy( ITEMLISTPTR(item.lParam) );
                if( m_pidlManager.GetItemType( pItem ) == CPidlManager::FOLDER )
                {
                    LOG(_T("%s 打开文件夹 %s"), __TFUNCTION__, m_pidlManager.GetItemName( pItem ) );
                    //打开文件夹
                    m_pShellBrowser->BrowseObject( pItem , SBSP_DEFBROWSER | SBSP_RELATIVE );
                }
                else
                {   
                    TCHAR szPath[MAX_PATH] = {0};
                    DWORD dwLen = MAX_PATH;
                    LPITEMIDLIST pFullItem = m_pidlManager.Concatenate(m_pFolder->GetRootPath(), pItem );
                    m_pidlManager.GetFullName( pFullItem, szPath, &dwLen );
                    m_pidlManager.ReplaceRoot( szPath );
                    m_pidlManager.Delete( pFullItem );
                    //打开文件
                    LONG ret = (LONG)(LONG_PTR)ShellExecute(NULL, _T("open"),  szPath, NULL, NULL, SW_SHOWNORMAL);
                    if ( ret > 32 )
                    {
                        return TRUE;
                    }
                    switch ( ret )
                    {
                    case ERROR_BAD_FORMAT:
                        {
                            ::MessageBox( NULL, _T("文件已损坏"), _T("提示"), MB_OK );
                        }
                        break;
                    case SE_ERR_ASSOCINCOMPLETE:
                    case SE_ERR_NOASSOC:
                        {
                            TCHAR szRunParam[MAX_PATH<<1] = {0};
                            _sntprintf( szRunParam, MAX_PATH<<1, _T("shell32.dll,OpenAs_RunDLL \"%s\""), szPath );
                            ShellExecute(NULL, NULL, _T("rundll32.exe "), szRunParam, NULL, SW_SHOW); 
                        }
                        break;
                    default:
                        {
                        }
                    }
                }
                m_pidlManager.Delete( pItem );
                pItem = NULL;
            }
        }
        else if( pNmhdr->code == NM_RCLICK )
        {
            LPITEMIDLIST* ppIdl = NULL;
            int nSelCount = ListView_GetSelectedCount(m_hWnd);
            if ( nSelCount > 0 )
            {
                ppIdl = (LPITEMIDLIST*)_Module.m_Allocator.Alloc( sizeof(LPITEMIDLIST)*nSelCount );
                int iIndex = ListView_GetNextItem( m_hWnd, -1, LVIS_SELECTED );
                LV_ITEM item = {0};
                item.iSubItem = 0;
                item.mask = LVIF_PARAM;
                int _i = 0;
                while( iIndex >= 0 
                    && _i < nSelCount )
                {    
                    item.iItem = iIndex;
                    ListView_GetItem( m_hWnd, &item );
                    ppIdl[_i] = m_pidlManager.Copy( ITEMLISTPTR(item.lParam) );
                    ++_i;
                    iIndex = ListView_GetNextItem( m_hWnd, -1, LVIS_SELECTED );
                }
            }
            LPCONTEXTMENU pMenu = NULL;
            HRESULT hr = E_FAIL;
            hr = m_pFolder->GetUIObjectOf( m_hWnd, nSelCount, \
                (LPCITEMIDLIST*)ppIdl, IID_IContextMenu, NULL, (void**)&pMenu );
            if ( FAILED(hr)
                || !pMenu)
            {
                LOG(_T("IID_IContextMenu Failed"));
                if ( nSelCount > 0 )
                {
                    for ( int _i = 0; _i < nSelCount; ++_i )
                    {
                        m_pidlManager.Delete( ppIdl[_i] );
                    }
                    _Module.m_Allocator.Free( ppIdl );
                }
                return S_OK;
            }
            HMENU hMenu = ::CreatePopupMenu();
            if ( !hMenu )
            {
                if ( nSelCount > 0 )
                {
                    for ( int _i = 0; _i < nSelCount; ++_i )
                    {
                        m_pidlManager.Delete( ppIdl[_i] );
                    }
                    _Module.m_Allocator.Free( ppIdl );
                }
                return S_OK;
            }
            hr = pMenu->QueryContextMenu( hMenu, 0, 10, 32767, CMF_NORMAL | CMF_EXPLORE );
            if ( FAILED(hr) )
            {
                if ( nSelCount > 0 )
                {
                    for ( int _i = 0; _i < nSelCount; ++_i )
                    {
                        m_pidlManager.Delete( ppIdl[_i] );
                    }
                    _Module.m_Allocator.Free( ppIdl );
                }
                DestroyMenu( hMenu );
                return hr;
            }
            POINT point = {0};
            GetCursorPos( &point );
            UINT command = (UINT)TrackPopupMenu ( hMenu, TPM_RETURNCMD | TPM_LEFTALIGN, point.x, point.y, 0, m_hWnd, NULL );
            CMINVOKECOMMANDINFO cmi = {0};
            cmi.cbSize = sizeof (CMINVOKECOMMANDINFO);
            cmi.lpVerb = (LPSTR) MAKEINTRESOURCE (command-10);
            cmi.nShow = SW_SHOWNORMAL;
            pMenu->InvokeCommand( &cmi );
            pMenu->Release();
            if ( nSelCount > 0 )
            {
                for ( int _i = 0; _i < nSelCount; ++_i )
                {
                    m_pidlManager.Delete( ppIdl[_i] );
                }
                _Module.m_Allocator.Free( ppIdl );
            }
            DestroyMenu( hMenu );
        }
    }
    TRACE_RETURN S_OK;
}