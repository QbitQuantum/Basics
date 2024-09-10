void CVectorCtl::CreateBackground ()
{
    if (!m_bBmpCreated)
        return; //  No image yet
    if (!m_bBackgroundBitmapUsed)   // No background used - fill with gradient color
    {
        double r = GetRValue (m_clrBackgroundStart),
               g = GetGValue (m_clrBackgroundStart),
               b = GetBValue (m_clrBackgroundStart),
               rd = double (GetRValue (m_clrBackgroundEnd) - r) / double (m_iHeight),
               gd = double (GetGValue (m_clrBackgroundEnd) - g) / double (m_iHeight),
               bd = double (GetBValue (m_clrBackgroundEnd) - b) / double (m_iHeight);
        for (int j=0; j<m_iHeight; j++)
        {
            for (int i=0; i<m_iWidth; i++)
                m_dcMem.SetPixelV (i,j, RGB (BYTE(r),BYTE(g),BYTE(b)));
            r+=rd;
            g+=gd;
            b+=bd;
        }
        Redraw (TRUE);
        return;
    }
    // Bitmap used : tile it in back
    CDC DCtmp;
    BITMAP tmpBitmap;

    m_bmpBack.GetBitmap (&tmpBitmap);
    int iTmpWidth = tmpBitmap.bmWidth,
        iTmpHeight = tmpBitmap.bmHeight;

    DCtmp.CreateCompatibleDC (&m_dcMem);
    m_pOldBitmap = DCtmp.SelectObject (&m_bmpBack);

    for (int i=0; i<m_iWidth; i++)
        for (int j=0; j<m_iHeight; j++)
            m_dcMem.SetPixelV (i,j, DCtmp.GetPixel (i % iTmpWidth, j % iTmpHeight));
    DCtmp.SelectObject (m_pOldBitmap);
    Redraw (TRUE);
}