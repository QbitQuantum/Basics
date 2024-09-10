BOOL CSplashScreenEx::SetBitmap(UINT nBitmapID,short red,short green,short blue)
{
    BITMAP bm;

    m_bitmap.DeleteObject();
    if (!m_bitmap.LoadBitmap(nBitmapID))
        return FALSE;

    GetObject(m_bitmap.GetSafeHandle(), sizeof(bm), &bm);
    m_nBitmapWidth=bm.bmWidth;
    m_nBitmapHeight=bm.bmHeight;
    m_rcText.SetRect(0,0,bm.bmWidth,bm.bmHeight);

    if (m_dwStyle & CSS_CENTERSCREEN)
    {
        m_nxPos=(GetSystemMetrics(SM_CXFULLSCREEN)-bm.bmWidth)/2;
        m_nyPos=(GetSystemMetrics(SM_CYFULLSCREEN)-bm.bmHeight)/2;
    }
    else if (m_dwStyle & CSS_CENTERAPP)
    {
        CRect rcParentWindow;
        ASSERT(m_pWndParent!=NULL);
        m_pWndParent->GetWindowRect(&rcParentWindow);
        m_nxPos=rcParentWindow.left+(rcParentWindow.right-rcParentWindow.left-bm.bmWidth)/2;
        m_nyPos=rcParentWindow.top+(rcParentWindow.bottom-rcParentWindow.top-bm.bmHeight)/2;
    }

    if (red!=-1 && green!=-1 && blue!=-1)
    {
        m_hRegion=CreateRgnFromBitmap((HBITMAP)m_bitmap.GetSafeHandle(),RGB(red,green,blue));
        SetWindowRgn(m_hRegion, TRUE);
    }

    return TRUE;
}