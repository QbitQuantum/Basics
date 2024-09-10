BOOL COptionTreeItemImage::GetBitmapFromImageList(CDC *pDC, HICON hIcon, CBitmap &bmp)
{
    // Declare varaibles
    CDC dc;
    CBrush brush;

    dc.CreateCompatibleDC(pDC);
    bmp.CreateCompatibleBitmap(pDC, m_sImageSizes.cx, m_sImageSizes.cy);
    CBitmap* pOldBmp = dc.SelectObject(&bmp);
    brush.CreateSolidBrush(GetSysColor(COLOR_MENU));
    ::DrawIconEx(dc.GetSafeHdc(), 0, 0, hIcon, m_sImageSizes.cx, m_sImageSizes.cy, 0, (HBRUSH)brush,DI_NORMAL);

    // Restore
    dc.SelectObject(pOldBmp);

    // Delete
    if (brush.GetSafeHandle() != NULL)
    {
        brush.DeleteObject();
    }
    if (dc.GetSafeHdc() != NULL)
    {
        dc.DeleteDC();
    }

    // The icon is not longer needed
    DestroyIcon(hIcon);

    return TRUE;
}