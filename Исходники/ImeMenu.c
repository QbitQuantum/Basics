void FillMenuItemInfo(HWND hWnd, HIMC hIMC, LPMENUITEMINFO lpmii, LPMYIMEMENUITEMINFO lpIme, BOOL fRight)
{
    FillMemory((PVOID)lpmii, sizeof(MENUITEMINFO), 0);
    lpmii->cbSize = sizeof(MENUITEMINFO);
    lpmii->fMask = 0;

    // Set fType;
    if (lpIme->fType)
    {
        lpmii->fMask |= MIIM_TYPE;
        lpmii->fType = 0;

        if (lpIme->fType & IMFT_RADIOCHECK)
        {
            lpmii->fType |= MFT_RADIOCHECK;
        }

        if (lpIme->fType & IMFT_SEPARATOR)
        {
            lpmii->fType |= MFT_SEPARATOR;
        }

    }

    lpmii->fMask |= MIIM_ID;
    lpmii->wID = lpIme->wID + IDM_STARTIMEMENU;

    if (lpIme->fType & IMFT_SUBMENU)
    {
        lpmii->fMask |= MIIM_SUBMENU;
        lpmii->hSubMenu = CreateImeMenu(hWnd, hIMC, lpIme, fRight);
    }

    lpmii->fMask |= MIIM_STATE;
    lpmii->fState = lpIme->fState;

    if (lpIme->hbmpChecked &&  lpIme->hbmpUnchecked)
    {
       lpmii->fMask |= MIIM_CHECKMARKS;
       lpmii->hbmpChecked = lpIme->hbmpChecked;
       lpmii->hbmpUnchecked = lpIme->hbmpUnchecked;
    }
    

    lpmii->fMask |= MIIM_DATA;
    lpmii->dwItemData = lpIme->dwItemData;

    if (lpIme->hbmpItem)
    {
       lpmii->fMask |= MIIM_BITMAP;
       lpmii->hbmpItem = lpIme->hbmpItem;
    }


#ifdef USEWAPI
    {
        BOOL bUDC;
        int i;
        char   szTemp[IMEMENUITEM_STRING_SIZE] = {0};

        i = WideCharToMultiByte(CP_ACP,
                                0,
                                lpIme->szString,
                                (int)wcslen(lpIme->szString),
                                szTemp,
                                IMEMENUITEM_STRING_SIZE,
                                (LPSTR)NULL,
                                &bUDC);
        szTemp[i] = '\0';

        if (lstrlen(szTemp))
        {
            lpmii->fMask |= MIIM_STRING;
            StringCchCopyNA((LPSTR)lpIme->szString, ARRAYSIZE(lpIme->szString), szTemp, IMEMENUITEM_STRING_SIZE-1);
            lpmii->dwTypeData = (LPSTR)lpIme->szString;
            lpmii->cch = lstrlen((LPSTR)lpIme->szString);
        }
    }
#else
    if (lstrlen(lpIme->szString))
    {
        lpmii->fMask |= MIIM_STRING;
        lpmii->dwTypeData = lpIme->szString;
        lpmii->cch = lstrlen(lpIme->szString);
    }
#endif

}