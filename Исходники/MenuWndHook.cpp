void CMenuWndHook::OnPrint(HDC dc)
{
    if(m_strSkinName.IsEmpty()) return;
    ISkinObj *pSkin=GETSKIN(m_strSkinName);
    if(!pSkin) return;
    SSkinImgFrame *pBorderSkin=static_cast<SSkinImgFrame*>(pSkin);
    if(!pBorderSkin) return;

    CRect rcClient;
    GetClientRect(m_hWnd,&rcClient);
    ClientToScreen(m_hWnd,(LPPOINT)&rcClient);
    ClientToScreen(m_hWnd,((LPPOINT)&rcClient)+1);
    CRect rcWnd;
    GetWindowRect(m_hWnd, &rcWnd);
    rcClient.OffsetRect(-rcWnd.TopLeft());
    
    int nSave = ::SaveDC(dc);
    ::ExcludeClipRect(dc,rcClient.left,rcClient.top,rcClient.right,rcClient.bottom);
    rcWnd.MoveToXY(0,0);
    
    CAutoRefPtr<IRenderTarget> pRT;
    GETRENDERFACTORY->CreateRenderTarget(&pRT,rcWnd.Width(),rcWnd.Height());
    pBorderSkin->Draw(pRT,rcWnd,0);
    HDC hmemdc=pRT->GetDC(0);
    ::BitBlt(dc,0,0,rcWnd.Width(),rcWnd.Height(),hmemdc,0,0,SRCCOPY);
    pRT->ReleaseDC(hmemdc);
    ::RestoreDC(dc,nSave);
}