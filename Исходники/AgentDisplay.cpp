void
AgentDisplay::SetCursorMPCode(u16 nMPCode)
{
    u16 n1 = nMPCode / 1000;
    u16 n2 = nMPCode % 1000 / 100;
    u16 n3 = nMPCode % 100 / 10;
    u16 n4 = nMPCode % 10;

    FCB * pFCB = (FCB *)m_pFCB;
    bool bInverseVideo = (MESA_TO_C_UNSPECIFIED(pFCB->m_nInverseVideo) ? true : false);
    DawnView * pView = DawnApp::GetDawnView();
    if (NULL == pView) return;

    // do a bunch of Windows hocus
    u16 nCursorWidth = ::GetSystemMetrics(SM_CXCURSOR);
    u16 nCursorHeight = ::GetSystemMetrics(SM_CYCURSOR);
    u16 nCursorBytes = (nCursorWidth * nCursorHeight) >> 3;
    char bitsXOR[256];
    char bitsAND[256];
    CWindowDC dc(NULL);
    CDC dc1;
    CDC dc2;
    CBitmap bitmapAND;
    CBitmap bitmapXOR;
    CBitmap bitmapMP;
    CBitmap * pBitmapOld1 = NULL;
    CBitmap * pBitmapOld2 = NULL;
    HCURSOR hCursor = NULL;
    u16 nMPCursorWidth = 7 * 2 + 2;
    u16 nMPCursorHeight = 10 * 2;

    do
    {
        if (0 == dc1.CreateCompatibleDC(&dc)) break;
        if (0 == dc2.CreateCompatibleDC(&dc)) break;

        if (0 == bitmapAND.CreateCompatibleBitmap(&dc2, nCursorWidth, nCursorHeight)) break;
        if (0 == bitmapXOR.CreateCompatibleBitmap(&dc2, nCursorWidth, nCursorHeight)) break;
        if (0 == bitmapMP.CreateCompatibleBitmap(&dc1, nMPCursorWidth, nMPCursorHeight)) break;

        // select the mp resource bitmap into dc2
        if (NULL == (pBitmapOld2 = dc2.SelectObject(&m_bitmapMP))) break;

        // put the mp code cursor pattern in dc1
        if (NULL == (pBitmapOld1 = dc1.SelectObject(&bitmapMP))) break;
        // first fill with black, then blit the characters (inversed)
        dc1.FillSolidRect(0, 0, nMPCursorWidth, nMPCursorHeight, RGB(0, 0, 0));
        dc1.BitBlt(0,  0, 7, 10, &dc2, 7 * n1, 0, NOTSRCCOPY);
        dc1.BitBlt(7,  0, 7, 10, &dc2, 7 * n2, 0, NOTSRCCOPY);
        dc1.BitBlt(2, 10, 7, 10, &dc2, 7 * n3, 0, NOTSRCCOPY);
        dc1.BitBlt(9, 10, 7, 10, &dc2, 7 * n4, 0, NOTSRCCOPY);
        
        // clear the resource bitmap out of dc2
        dc2.SelectObject(pBitmapOld2); pBitmapOld2 = NULL;

        // Build the XOR cursor plane
        memset(bitsXOR, 0x00, nCursorBytes);
        if (bInverseVideo)
        {
            if (0 == bitmapXOR.SetBitmapBits(nCursorBytes, bitsXOR)) break;
            if (NULL == (pBitmapOld2 = dc2.SelectObject(&bitmapXOR))) break;
            if (0 == dc2.BitBlt(0, 0, nCursorWidth, nCursorHeight, &dc1, 0, 0, SRCCOPY)) break;
            dc2.SelectObject(pBitmapOld2); pBitmapOld2 = NULL;
            if (0 == bitmapXOR.GetBitmapBits(nCursorBytes, bitsXOR)) break;
        }

        // Build the AND cursor plane
        memset(bitsAND, 0xFF, nCursorBytes);
        if (0 == bitmapAND.SetBitmapBits(nCursorBytes, bitsAND)) break;
        if (NULL == (pBitmapOld2 = dc2.SelectObject(&bitmapAND))) break;
        if (0 == dc2.BitBlt(0, 0, nCursorWidth, nCursorHeight, &dc1, 0, 0, NOTSRCCOPY)) break;
        dc2.SelectObject(pBitmapOld2); pBitmapOld2 = NULL;
        if (0 == bitmapAND.GetBitmapBits(nCursorBytes, bitsAND)) break;

        // finish building the planes, clear the bitmap from dc1 and create the cursor
        dc1.SelectObject(pBitmapOld1); pBitmapOld1 = NULL;
        hCursor = ::CreateCursor(AfxGetInstanceHandle(), 0, 0, nCursorWidth, nCursorHeight, bitsAND, bitsXOR);
    }
    while (false);

    if (hCursor)
    {
        CRect clientRect;
        CPoint cursorPoint;

        pView->GetClientRect(&clientRect);
        ::GetCursorPos(&cursorPoint);

        ::SetClassLong(pView->GetSafeHwnd(), GCL_HCURSOR, (LONG)hCursor);
        if (pView == pView->WindowFromPoint(cursorPoint)) ::SetCursor(hCursor);
        if (m_hCursor) ::DestroyCursor(m_hCursor);
        m_hCursor = hCursor;
    }
    else
    {
        if (NULL != pBitmapOld1) dc1.SelectObject(pBitmapOld1);
        if (NULL != pBitmapOld2) dc2.SelectObject(pBitmapOld2);
    }
}