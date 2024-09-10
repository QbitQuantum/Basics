void CButtonXP::DrawItem (LPDRAWITEMSTRUCT pDis)
{
    CBufferDC cDC (pDis->hDC);
    CRect rcItem (pDis->rcItem);
    HFONT hOldFont = (HFONT)cDC.SelectObject ((HFONT)::GetStockObject (DEFAULT_GUI_FONT));
    CPenDC pen (cDC);
    CBrushDC brush (cDC);

    if ( (pDis->itemState & ODS_FOCUS) ||
         LOWORD(::SendMessage (::GetParent (m_hWnd), DM_GETDEFID, 0, 0)) == GetDlgCtrlID() )
    {
        rcItem.DeflateRect (1, 1);
    }
    if ( (pDis->itemState & ODS_DISABLED) ||
         (!m_MouseMgr.MouseOver() && !(pDis->itemState & ODS_SELECTED)) )
    {
        pen.Color (::GetSysColor (COLOR_3DSHADOW));
        brush.Color (HLS_TRANSFORM (::GetSysColor (COLOR_3DFACE), -10, 0));
    }
    else
    {
        COLORREF crBorder = ::GetSysColor (COLOR_HIGHLIGHT);

        pen.Color (crBorder);

        if ( (pDis->itemState & ODS_SELECTED) )
        {
            brush.Color (HLS_TRANSFORM (crBorder, +50, -50));
            cDC.SetTextColor (RGB(240,240,240));
        }
        else
        {
            brush.Color (HLS_TRANSFORM (crBorder, +80, -66));
            cDC.SetTextColor (::GetSysColor (COLOR_BTNTEXT));
        }
    }
    if ( (pDis->itemState & ODS_DISABLED) )
    {
        cDC.SetTextColor (::GetSysColor (COLOR_GRAYTEXT));
    }
    else if ( (pDis->itemState & ODS_SELECTED) )
    {
        cDC.SetTextColor (RGB(240,240,240));
    }
    else if ( m_MouseMgr.MouseOver() )
    {
        cDC.SetTextColor (0);
    }
    else
    {
        cDC.SetTextColor (::GetSysColor (COLOR_BTNTEXT));
    }
    cDC.Rectangle (rcItem);
    cDC.SetBkMode (TRANSPARENT);
    cDC.DrawText (CWindowText (this), rcItem, DT_SINGLELINE|DT_CENTER|DT_VCENTER);

    if ( (pDis->itemState & ODS_FOCUS) )
    {
        rcItem.DeflateRect (3, 3);
        cDC.DrawFocusRect (rcItem);
    }
    cDC.SelectObject (hOldFont);
}