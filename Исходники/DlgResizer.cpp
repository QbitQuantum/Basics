void CDlgResizer::DoResize(int width, int height)
{
    UpdateGripPos();
    if (m_controls.empty())
        return;

    InvalidateRect(m_hDlg, NULL, true);

    HDWP hdwp = BeginDeferWindowPos((int)m_controls.size());
    for (size_t i=0; i<m_controls.size(); ++i)
    {
        RECT newpos = m_controls[i].origSize;
        switch (m_controls[i].resizeType)
        {
        case RESIZER_TOPLEFT:
            break;  // do nothing - the original position is fine
        case RESIZER_TOPRIGHT:
            newpos.left += (width - m_dlgRect.right);
            newpos.right += (width - m_dlgRect.right);
            break;
        case RESIZER_TOPLEFTRIGHT:
            newpos.right += (width - m_dlgRect.right);
            break;
        case RESIZER_TOPLEFTBOTTOMRIGHT:
            newpos.right += (width - m_dlgRect.right);
            newpos.bottom += (height - m_dlgRect.bottom);
            break;
        case RESIZER_BOTTOMLEFT:
            newpos.top += (height - m_dlgRect.bottom);
            newpos.bottom += (height - m_dlgRect.bottom);
            break;
        case RESIZER_BOTTOMRIGHT:
            newpos.top += (height - m_dlgRect.bottom);
            newpos.bottom += (height - m_dlgRect.bottom);
            newpos.left += (width - m_dlgRect.right);
            newpos.right += (width - m_dlgRect.right);
            break;
        case RESIZER_BOTTOMLEFTRIGHT:
            newpos.top += (height - m_dlgRect.bottom);
            newpos.bottom += (height - m_dlgRect.bottom);
            newpos.right += (width - m_dlgRect.right);
            break;
        }
        hdwp = DeferWindowPos(hdwp, m_controls[i].hWnd, NULL, newpos.left, newpos.top,
            newpos.right-newpos.left, newpos.bottom-newpos.top,
            SWP_NOZORDER);
    }
    EndDeferWindowPos(hdwp);
    UpdateGripPos();
}