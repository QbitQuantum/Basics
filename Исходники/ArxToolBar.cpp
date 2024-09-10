void ArxToolBar::CreateToolBars( const TCHAR* bmpDir )
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

    // 如果bmpDir路径没有反斜杠(\)，则添加一个反斜杠
    CString path( bmpDir );
    // 取最后一个字符
    if( path.Right( 1 ) != _T( "\\" ) )
    {
        path.Format( _T( "%s\\" ), bmpDir );
    }

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

                TCHAR szBmpFile[256];
                _stprintf( szBmpFile, _T( "%s%s" ), path, btn->bmp );
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

    //stcMyToolBarNames.Copy(m_TopMenuNames); //将工具栏名称存入静态数组中，卸载时使用
}