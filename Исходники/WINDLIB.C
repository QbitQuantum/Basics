BOOL PEXPORT kpc_set_window_background(ATOMID idWindow, HWND hWnd, 
                                       float fRed, float fGreen, float fBlue)
{
    short sRed = 0, sGreen = 0, sBlue = 0;

    if (hWnd == (HWND) -1 || 
        hWnd == KpphWndTraceCB() || hWnd == KpphWndKALCB())
        return FALSE;

    check_and_set_color(&sRed, &fRed);
    check_and_set_color(&sGreen, &fGreen);
    check_and_set_color(&sBlue, &fBlue);

    if (KpsIsASessionWindow(hWnd))
    {
        LISTID idBack = KppMakeList(0);

        KppAppendElem(idBack, KappaMakeInt(sRed));
        KppAppendElem(idBack, KappaMakeInt(sGreen));
        KppAppendElem(idBack, KappaMakeInt(sBlue));
        KppSetSlotValue(idWindow, lpSNs->idTextBackColorSN, idBack, EXPLIST);
    }   
    else
    {
        HBRUSH hOldBrush = GetClassWord(hWnd, GCW_HBRBACKGROUND);
        short sOffset = KpsGetWindowOffset(hWnd);
        
        SetClassWord(hWnd, GCW_HBRBACKGROUND,
                     CreateSolidBrush(RGB(sRed, sGreen, sBlue)));

        if (sOffset == -1)
            return FALSE;
        if (!bWinBackground[sOffset])
            bWinBackground[sOffset] = 1;
        else if (hOldBrush)
            DeleteObject(hOldBrush);
    }    

    InvalidateRect(hWnd, NULL, TRUE);
    UpdateWindow(hWnd);

    return TRUE;
}