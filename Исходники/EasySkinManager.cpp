void CEasySkinManager::OnSize( UINT nType, int cx, int cy )
{
    CEasySkinDialog::OnSize(nType, cx, cy);

    //移动准备
    HDWP hDwp=BeginDeferWindowPos(64);
    UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;

    if ( m_enWndStyle != en_Wnd_None )
    {
        DeferWindowPos(hDwp,m_btClose,NULL,cx-41,0,0,0,uFlags|SWP_NOSIZE);

        if ( m_enWndStyle != en_Wnd_CloseBox )
        {
            if( m_enWndStyle != en_Wnd_MinimizeBox )
                DeferWindowPos(hDwp,m_btMax,NULL,cx-69,0,0,0,uFlags|SWP_NOSIZE);

            DeferWindowPos(hDwp,m_btMin,NULL,cx-69-(m_enWndStyle==en_Wnd_Normal?28:0),0,0,0,uFlags|SWP_NOSIZE);
        }
    }

    //结束调整
    //LockWindowUpdate();
    EndDeferWindowPos(hDwp);
    //UnlockWindowUpdate();

    //设置圆角
    CRgn rgn;
    rgn.CreateRoundRectRgn(0,0,cx,cy,4,4);
    SetWindowRgn(rgn,FALSE);

    //更新界面
    Invalidate(FALSE);
}