HICON CMeterIcon::CreateMeterIcon(const int *pBarData)
// the returned icon must be cleaned up using DestroyIcon()
{   // begin CreateMeterIcon
    ICONINFO iiNewIcon= {0};
    iiNewIcon.fIcon = true;	// set that it is an icon

    // create DC's
    HDC hScreenDC = ::GetDC(NULL);
    HDC hIconDC = CreateCompatibleDC(hScreenDC);
    HDC hMaskDC = CreateCompatibleDC(hScreenDC);

    if(hScreenDC == NULL)
    {   // begin error check
        return NULL;
    }// end error check
    if(hIconDC == NULL)
    {   // begin error check
        return NULL;
    }// end error check
    if(hMaskDC == NULL)
    {   // begin error check
        return NULL;
    }// end error check

    // load bitmaps
    iiNewIcon.hbmColor = CreateCompatibleBitmap(hScreenDC,m_sDimensions.cx,m_sDimensions.cy);
    if(iiNewIcon.hbmColor == NULL)
    {   // begin error check
        return NULL;
    }// end error check
    if(!::ReleaseDC(NULL,hScreenDC))	// release this ASAP
    {   // begin DC not released
        return NULL;
    }// end DC not released
    iiNewIcon.hbmMask = CreateCompatibleBitmap(hMaskDC,m_sDimensions.cx,m_sDimensions.cy);
    if(iiNewIcon.hbmMask == NULL)
    {   // begin error check
        return NULL;
    }// end error check
    HGDIOBJ hOldIconDC = ::SelectObject(hIconDC,iiNewIcon.hbmColor);
    if(hOldIconDC == NULL)
    {   // begin error check
        return NULL;
    }// end error check
    HGDIOBJ hOldMaskDC = ::SelectObject(hMaskDC,iiNewIcon.hbmMask);
    if(hOldMaskDC == NULL)
    {   // begin error check
        return NULL;
    }// end error check

    // initilize the bitmaps
    if(!BitBlt(hIconDC,0,0,m_sDimensions.cx,m_sDimensions.cy,NULL,0,0,BLACKNESS))
    {   // begin BitBlt failed
        return NULL;
    }// end BitBlt failed
    if(!BitBlt(hMaskDC,0,0,m_sDimensions.cx,m_sDimensions.cy,NULL,0,0,WHITENESS))
    {   // begin BitBlt failed
        return NULL;
    }// end BitBlt failed


    if(!DrawIconEx(hIconDC,0,0,m_hFrame,m_sDimensions.cx,m_sDimensions.cy,NULL,NULL,/*DI_NORMAL|*/DI_IMAGE))
    {   // begin error check
        return NULL;
    }// end error check
    if(!DrawIconEx(hMaskDC,0,0,m_hFrame,m_sDimensions.cx,m_sDimensions.cy,NULL,NULL,/*DI_NORMAL|*/DI_MASK))
    {   // begin error check
        return NULL;
    }// end error check

    // draw the meters
    for(int i = 0; i < m_nNumBars; i++)
        if(DrawIconMeter(hIconDC,hMaskDC,pBarData[i],i) == false)
            return false;

    // create icon
    ::SelectObject(hIconDC,hOldIconDC);
    ::SelectObject(hMaskDC,hOldMaskDC);
    HICON hNewIcon = CreateIconIndirect(&iiNewIcon);

    // cleanup
    DeleteObject(iiNewIcon.hbmColor);
    DeleteObject(iiNewIcon.hbmMask);
    DeleteDC(hMaskDC);
    DeleteDC(hIconDC);
    return hNewIcon;

}// end CreateMeterIcon