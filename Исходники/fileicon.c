BOOL _ShellImageListInit(int cxIcon, int cyIcon, int cxSmIcon, int cySmIcon, UINT flags, BOOL fRestore)
{
    int i;
    TCHAR szModule[MAX_PATH];
    HKEY hkeyIcons;

    ASSERTCRITICAL;

    if (himlIcons == NULL) {
        himlIcons = ImageList_Create(cxIcon, cyIcon, ILC_MASK|ILC_SHARED|flags, 0, 32);
    }
    else {
        ImageList_Remove(himlIcons, -1);
        ImageList_SetIconSize(himlIcons, cxIcon, cyIcon);
    }

    if (himlIcons == NULL) {
        return FALSE;
    }

    if (himlIconsSmall == NULL) {
        himlIconsSmall = ImageList_Create(cxSmIcon, cySmIcon, ILC_MASK|ILC_SHARED|flags, 0, 32);
    }
    else {
        ImageList_Remove(himlIconsSmall, -1);
        ImageList_SetIconSize(himlIconsSmall, cxSmIcon, cySmIcon);
    }

    if (himlIconsSmall == NULL) {
        ImageList_Destroy(himlIcons);
        himlIcons = NULL;
        return FALSE;
    }

    // set the bk colors to COLOR_WINDOW since this is what will
    // be used most of the time as the bk for these lists (cabinet, tray)
    // this avoids having to do ROPs when drawing, thus making it fast

    ImageList_SetBkColor(himlIcons, GetSysColor(COLOR_WINDOW));
    ImageList_SetBkColor(himlIconsSmall, GetSysColor(COLOR_WINDOW));

    GetModuleFileName(HINST_THISDLL, szModule, ARRAYSIZE(szModule));

    // WARNING: this code assumes that these icons are the first in
    // our RC file and are in this order and these indexes correspond
    // to the II_ constants in shell.h.

    hkeyIcons =
        SHGetExplorerSubHkey(HKEY_LOCAL_MACHINE, g_szShellIcons, FALSE);

    for (i = 0; i < ARRAYSIZE(c_SystemImageListIndexes); i++) {

        HICON hIcon=NULL;
        HICON hSmallIcon=NULL;
        int iIndex;

        //
        // Load all of the icons with fRestore == TRUE, or only the overlays
        // if fRestore == FALSE.
        //
        if (fRestore || (i >= II_OVERLAYFIRST && i <= II_OVERLAYLAST))
        {
            //
            // check to see if icon is overridden in the registry
            //
            if (hkeyIcons)
            {
                TCHAR val[10];
                TCHAR ach[MAX_PATH];
                DWORD cb=MAX_PATH;
                int iIcon;

                wsprintf(val, g_szD, i);

                ach[0] = 0;
                RegQueryValueEx(hkeyIcons, val, NULL, NULL, (LPBYTE)ach, &cb);

                if (ach[0])
                {
                    HICON hIcons[2] = {0, 0};

                    iIcon = PathParseIconLocation(ach);

                    ExtractIcons(ach, iIcon,
                        MAKELONG(g_cxIcon,g_cxSmIcon),
                        MAKELONG(g_cyIcon,g_cySmIcon),
                        hIcons, NULL, 2, g_lrFlags);

                    hIcon = hIcons[0];
                    hSmallIcon = hIcons[1];

                    if (hIcon)
                    {
                        DebugMsg(DM_TRACE, TEXT("ShellImageListInit: Got default icon #%d from registry: %s,%d"), i, ach, iIcon);
                    }
                }
            }


            if (hIcon == NULL)
            {
                hIcon      = LoadImage(HINST_THISDLL, MAKEINTRESOURCE(c_SystemImageListIndexes[i]), IMAGE_ICON, cxIcon, cyIcon, g_lrFlags);
                hSmallIcon = LoadImage(HINST_THISDLL, MAKEINTRESOURCE(c_SystemImageListIndexes[i]), IMAGE_ICON, cxSmIcon, cySmIcon, g_lrFlags);
            }

            if (hIcon)
            {
                iIndex = SHAddIconsToCache(hIcon, hSmallIcon, szModule, i, 0);
                Assert(iIndex == i);     // assume index

                if (i >= II_OVERLAYFIRST && i <= II_OVERLAYLAST)
                {
                    ImageList_SetOverlayImage(himlIcons,      iIndex, i - II_OVERLAYFIRST + 1);
                    ImageList_SetOverlayImage(himlIconsSmall, iIndex, i - II_OVERLAYFIRST + 1);
                }
            }
        }
    }

    if (hkeyIcons)
        RegCloseKey(hkeyIcons);

    return TRUE;
}