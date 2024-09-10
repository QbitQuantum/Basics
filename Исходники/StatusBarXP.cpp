void CStatusBarXP::OnPaint ()
{
    Default();

    CClientDC cDC (this);
    CPenDC pen (cDC, ::GetSysColor (COLOR_3DSHADOW));
    CRect rcItem;

    cDC.SelectObject (::GetStockObject (NULL_BRUSH));

    for ( int i = 0; i < m_nCount; i++ )
    {
        GetItemRect (i, rcItem);
        cDC.Rectangle (rcItem); 
    }
}