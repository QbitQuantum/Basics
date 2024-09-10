BOOL CXTThemeManagerStyle::TakeSnapShot(CWnd* pWndOwner)
{
    CWnd *pWndParent = pWndOwner->GetParent();
    if (::IsWindow(pWndParent->GetSafeHwnd()))
    {
        if (m_bmpSnapShot.GetSafeHandle() != NULL)
            m_bmpSnapShot.DeleteObject();

        //convert our coordinates to our parent coordinates.
        CXTPWindowRect rc(pWndOwner);
        pWndParent->ScreenToClient(&rc);

        //copy what's on the parents background at this point
        CDC *pDC = pWndParent->GetDC();

        CDC memDC;
        memDC.CreateCompatibleDC(pDC);
        m_bmpSnapShot.CreateCompatibleBitmap(pDC, rc.Width(), rc.Height());

        CXTPBitmapDC bitmapDC(&memDC, &m_bmpSnapShot);
        memDC.BitBlt(0, 0, rc.Width(), rc.Height(), pDC, rc.left, rc.top, SRCCOPY);

        pWndParent->ReleaseDC(pDC);

        return TRUE;
    }

    return FALSE;
}