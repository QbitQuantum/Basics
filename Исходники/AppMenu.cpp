void AppMenu::CreateMenus()
{
    CMDIFrameWnd* pMainFrame = acedGetAcadFrame();
    pMainFrame->LockWindowUpdate();

    //得到菜单栏上面的最后一个菜单
    CString sName;
    if( !GetLastMenuFromMenubar( sName ) )
        return;

    sName.Replace( _T( "&" ), _T( "" ) ); //debug

    IAcadMenuGroup* mnuGrp = NULL;
    if ( !GetAcadMenuGroup( &mnuGrp, sName ) )
        return ;

    //得到所有菜单组
    IAcadPopupMenus*   mnus = NULL;
    IAcadPopupMenu*   mnu = NULL;
    IAcadPopupMenuItem*  mnuitem = NULL;
    HRESULT hr = S_OK;
    hr = mnuGrp->get_Menus( &mnus );
    long cnt = 0l;
    hr = mnus->get_Count( &cnt );
    int i = 0;
    int j = 0;
    int k = 0;
    VARIANT index;
    VariantInit( &index );
    V_VT( &index ) = VT_I4;
    CArray<IAcadPopupMenu*, IAcadPopupMenu*> MnuAdrs;

    long lIndex = 0;
    TCHAR MenuName[256];
    for ( i = 0; i < m_menuCount; i++ )
    {
        CString tmpMenu = m_TopMenuNames[i];
        tmpMenu.Replace( _T( "&" ), _T( "" ) );
        if( IsMenuExist( mnu, lIndex, tmpMenu, mnus ) ) //处理二次加载
        {
            V_I4( &index ) = lIndex;
        }
        else
        {
            //			MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, (LPTSTR)(LPCTSTR)m_TopMenuNames[i], -1, MenuName, 256);
            _tcscpy( MenuName, m_TopMenuNames[i] );
            mnus->Add( MenuName, &mnu );
            V_I4( &index ) = cnt++;
        }

        MnuAdrs.Add( mnu );
        mnu->InsertInMenuBar( index );
    }

    IAcadPopupMenu* MenuItem = NULL;
    int subMenuNum = 0;
    CCADMenuArray* Menus;
    TCHAR szSubMenu[256];
    TCHAR szSubMenuMacro[256];
    CString MenusName;
    CString Menusorder;
    for ( j = 0; j < m_menuCount; j++ )
    {
        Menus = m_menus.GetAt( j );
        subMenuNum = Menus->GetSize();
        for ( k = 0; k < subMenuNum; k++ )
        {
            mnu = MnuAdrs.GetAt( j );
            if ( !_tcscmp( _T( "--" ), Menus->GetAt( k )->name ) )
            {
                V_I4( &index ) = k;
                mnu->AddSeparator( index, &mnuitem );
            }
            else
            {
                V_I4( &index ) = k;
                MenusName = Menus->GetAt( k )->name;
                Menusorder = Menus->GetAt( k )->order;
                _tcscpy( szSubMenu, MenusName );
                _tcscpy( szSubMenuMacro, Menusorder );
                //MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, (LPTSTR)(LPCTSTR)MenusName, -1, szSubMenu, 256);
                //MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, (LPTSTR)(LPCTSTR)Menusorder, -1, szSubMenuMacro, 256);
                if ( _tcscspn( Menus->GetAt( k )->name, _T( "*" ) ) < ( size_t )MenusName.GetLength() )
                {
                    MenusName.TrimLeft( _T( '*' ) );
                    //					MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, (LPTSTR)(LPCTSTR)MenusName, -1, szSubMenu, 256);
                    _tcscpy( szSubMenu, MenusName );
                    hr = mnu->AddSubMenu( index, szSubMenu, &MenuItem );
                }
                else if ( _tcscspn( Menus->GetAt( k )->name, _T( "$" ) ) < ( size_t )MenusName.GetLength() )
                {
                    MenusName.TrimLeft( _T( '$' ) );
                    if( MenusName.Compare( _T( "--" ) ) == 0 ) //添加子菜单的分隔符
                    {
                        hr = MenuItem->AddSeparator( index, &mnuitem );
                    }
                    else
                    {
                        //MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, (LPTSTR)(LPCTSTR)MenusName, -1, szSubMenu, 256);
                        _tcscpy( szSubMenu, MenusName );
                        hr = MenuItem->AddMenuItem( index, szSubMenu, szSubMenuMacro, &mnuitem );
                    }
                }
                else
                {
                    hr = mnu->AddMenuItem( index, szSubMenu, szSubMenuMacro, &mnuitem );
                }
            }
        }
    }

    for ( i = 0; i < MnuAdrs.GetSize(); i++ )
    {
        MnuAdrs[i]->Release();
    }
    mnuitem->Release();
    mnus->Release();
    mnuGrp->Release();
    pMainFrame->UnlockWindowUpdate();

    stcMyTopMenuNames.Copy( m_TopMenuNames ); //将顶级菜单名存入静态数组中，卸载时使用

    //return ;
}