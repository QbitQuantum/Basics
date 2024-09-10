void AppToolBar::CreateToolBars()
{
    CMDIFrameWnd* pMainFrame = acedGetAcadFrame();
    pMainFrame->LockWindowUpdate();

    // 获取主菜单组
    IAcadMenuGroup* mnuGrp = NULL;
    if ( !GetAcadMenuGroup( &mnuGrp ) )
        return ;

    //得到所有菜单组
    HRESULT hr = S_OK;
    IAcadToolbars* acToolbars = NULL;
    hr = mnuGrp->get_Toolbars( &acToolbars );

    CString appFileName = acedGetAppName(); //取出完整的应用程序名称，含路径
    TCHAR dir[_MAX_DIR], drive[_MAX_DRIVE], path[_MAX_PATH];
    _tsplitpath( appFileName, drive, dir, NULL, NULL );
    _tmakepath( path, drive, dir, NULL, NULL );

    VARIANT index;
    VariantInit( &index );
    V_VT( &index ) = VT_I4;

    TCHAR MenuName[256];
    int delta = 30; // 工具栏间距
    int top = 200, left = 200;
    for ( int i = 0; i < m_menuCount; i++ )
    {
        IAcadToolbar* acToolbar = NULL;
        _tcscpy( MenuName, m_TopMenuNames[i] );
        hr = acToolbars->Add( MenuName, &acToolbar );

        acToolbar->put_Visible( true );
        acToolbar->Dock( acToolbarFloating );
        acToolbar->Float( top + i * delta, left, 1 );

        CCADToolButtonArray* Menus = m_menus[i];
        COleVariant flyOutButton;
        for ( int j = 0; j < Menus->GetSize(); j++ )
        {
            // 添加按钮
            V_I4( &index ) = ( long )j;
            CADToolButton* btn = Menus->GetAt( j );
            IAcadToolbarItem* acToolbarItem = NULL;

            if( _tcscmp( _T( "--" ), btn->name ) == 0 )
            {
                hr = acToolbar->AddSeparator( index, &acToolbarItem );
            }
            else
            {
                hr = acToolbar->AddToolbarButton( index, btn->name, btn->help, btn->order, flyOutButton, &acToolbarItem );

                CString bmpFile;
                bmpFile.Format( _T( "%s%s\\%s" ), path, BMP_DIR, btn->bmp );


                TCHAR szBmpFile[256];
                _tcscpy( szBmpFile, bmpFile );

                //acutPrintf(_T("\n路径:%s"), szBmpFile);
                hr = acToolbarItem->SetBitmaps( szBmpFile, szBmpFile );
            }
        }
        //acToolbarItem->Release();
        acToolbar->Release();
    }

    acToolbars->Release();
    mnuGrp->Release();
    pMainFrame->UnlockWindowUpdate();

    stcMyToolBarNames.Copy( m_TopMenuNames ); //将工具栏名称存入静态数组中，卸载时使用
}