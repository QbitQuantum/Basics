bool CAggMemoryDC::DrawTransparent(
    HBITMAP hBitmap,
    int x, 
    int y,
    int width,
    int height,
    int bmpWidth,
    int bmpHeight,
    COLORREF color)
{
    ATLASSERT(width>0&&height>0);
    double dx = x;
    double dy = y;
    m_mtx.transform(&dx,&dy);

    CDC dcImage;
    bool bOk=dcImage.CreateCompatibleDC(m_hDC) != NULL;
    HBITMAP oldbmp=dcImage.SelectBitmap(hBitmap);

    // if OS supports non-leaky TransparentBlt use it (also on printer)
    if(s_bTransOk)
    {
#ifndef _WIN32_WCE
        bOk=TransparentBlt(x, y, width, height, dcImage, 0, 0, bmpWidth, bmpHeight, color) != 0;
        if (!bOk) // just in case (e.g. printing), try emulation
            goto tryEmulate;
#endif
    }
    else
    {
tryEmulate:
        CBitmap bmpMono;
        bOk=bmpMono.CreateBitmap(width, height, 1, 1, NULL) != NULL;
        if (!bOk)
            return bOk;

        CDC dcMono;
        // Create dc for the mask
        bOk = dcMono.CreateCompatibleDC(m_hDC) != NULL;
        if (!bOk)
            return bOk;

        // Select the mask bitmap into its dc
        HBITMAP oldBitmapMono = (HBITMAP)::SelectObject(dcMono, bmpMono);

        if(bOk)
        {
            // Build mask based on transparent colour

            COLORREF crOldImg=dcImage.SetBkColor(color);
            bOk=dcMono.StretchBlt(0, 0, width, height, dcImage, 0, 0, bmpWidth, bmpHeight, SRCCOPY) != 0;
            dcImage.SetBkColor(crOldImg);

            // True Mask method - no flicker if destination is not actual display
            if(bOk)
                bOk=StretchBlt(x, y, width, height, dcImage, 0, 0, bmpWidth, bmpHeight, SRCINVERT) != 0;

            if(bOk) 
            {
                // setup the destination for monochrome blit
                COLORREF crOldBack = SetBkColor(RGB(255,255,255));
                COLORREF crOldText = SetTextColor(RGB(0,0,0));

                bOk=BitBlt(x, y, width, height, dcMono, 0, 0, SRCAND) != 0;

                SetBkColor(crOldBack);
                SetTextColor(crOldText);
            }

            if(bOk)
                bOk=StretchBlt(x, y, width, height, dcImage, 0, 0, bmpWidth, bmpHeight, SRCINVERT) != 0;
        }

        dcMono.SelectBitmap(oldBitmapMono);
    }

    dcImage.SelectBitmap(oldbmp);

    return bOk;
}