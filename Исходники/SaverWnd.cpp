BOOL CSaverWnd::OnPaint()
{
    PAINTSTRUCT ps ;
    BeginPaint(m_hWnd, &ps) ;
    
    RECT rc ;
    ::GetClientRect(m_hWnd, &rc) ;
    FillRect(ps.hdc, &rc, (HBRUSH)(COLOR_WINDOW+1)) ;
    FrameRect(ps.hdc, &rc, (HBRUSH)GetStockObject(GRAY_BRUSH)) ;
    RECT rc2 ;
    int height ;
    rc2 = rc ;
    height = DrawText(ps.hdc, "Kaspersky", -1, &rc, DT_WORDBREAK | DT_CENTER | DT_CALCRECT) ;
    rc = rc2 ;

    rc2.top = (rc.bottom + rc.top - height) / 2 ;

    DrawText(ps.hdc, "Kaspersky", -1, &rc2, DT_WORDBREAK | DT_CENTER ) ;

    ExcludeClipRect(ps.hdc, rc.left, rc.top, rc.right, rc.bottom) ;
    ScreenToClient(m_hWnd, (POINT*)&rc.left) ;
    ScreenToClient(m_hWnd, (POINT*)&rc.right) ;
    FillRect(ps.hdc, &rc, (HBRUSH)GetStockObject(GRAY_BRUSH)) ;
    
    EndPaint(m_hWnd, &ps) ;

    return TRUE ;
}