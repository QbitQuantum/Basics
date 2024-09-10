void CColorWnd::Init()
{
    int x, y;
    float H, L;
    CDC dcMem;
    CPaintDC dc(this);
    CBrush brush;
    CRect rect;
    if (colorGradiant.m_hObject != NULL)
        colorGradiant.DeleteObject();        // get rid of old bitmap

    dcMem.CreateCompatibleDC(&dc);
    GetClientRect(clientRect);
    clientSize = clientRect.Size();
    colorGradiant.CreateCompatibleBitmap(&dc, clientSize.cx, clientSize.cy);
    ASSERT(colorGradiant.m_hObject != NULL);

    CBitmap* pOldBitmap = dcMem.SelectObject(&colorGradiant);

    for (y = 0; y < clientSize.cy; y++)
        for (x = 0; x < clientSize.cx; x++) {
            H = ((float)x) * 360 / (clientSize.cx - 1);
            L = ((float)(clientSize.cy - 1) - y) / (clientSize.cy - 1);
            rect.SetRect(x, y, x + 1, y + 1);
            brush.CreateSolidBrush(HLS_To_RGB(H, L, 1));
            dcMem.FillRect(&rect, &brush);
            brush.DeleteObject();
        }
    dcMem.SelectObject(pOldBitmap);
    dcMem.DeleteDC();
}