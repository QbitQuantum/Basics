static INT_PTR
AppearancePage_OnInit(HWND hwndDlg)
{
    INT iListIndex;
    HWND hwndTheme;
    GLOBALS *g;
    RECT rcPreview;
    HDC hdcScreen;
    PTHEME pTheme;

    g = (GLOBALS*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(GLOBALS));
    if (g == NULL)
        return FALSE;

    SetWindowLongPtr(hwndDlg, DWLP_USER, (LONG_PTR)g);

    g->bInitializing = TRUE;

    if (!LoadCurrentScheme(&g->Scheme))
        return FALSE;

    g->pThemes = LoadThemes();
    if (g->pThemes)
    {
        BOOL bLoadedTheme = FALSE;

        if (g_GlobalData.pwszAction && 
            g_GlobalData.pwszFile && 
            wcscmp(g_GlobalData.pwszAction, L"OpenMSTheme") == 0)
        {
            bLoadedTheme = FindOrAppendTheme(g->pThemes, 
                                             g_GlobalData.pwszFile,
                                             NULL,
                                             NULL,
                                             &g->ActiveTheme);
        }

        if (bLoadedTheme)
        {
            g->bThemeChanged = TRUE;
            g->bSchemeChanged = TRUE;

            PostMessageW(GetParent(hwndDlg), PSM_CHANGED, (WPARAM)hwndDlg, 0);

            AppearancePage_LoadSelectedScheme(hwndDlg, g);
        }
        else
        {
            if (!GetActiveTheme(g->pThemes, &g->ActiveTheme))
            {
                g->ActiveTheme.ThemeActive = FALSE;
            }
        }

        /*
         * Keep a copy of the selected classic theme in order to select this
         * when user selects the classic theme (and not a horrible random theme )
         */
        if (!GetActiveClassicTheme(g->pThemes, &g->ClassicTheme))
        {
            g->ClassicTheme.Theme = g->pThemes;
            g->ClassicTheme.Color = g->pThemes->ColoursList;
            g->ClassicTheme.Size = g->ClassicTheme.Color->ChildStyle;
        }

        if (g->ActiveTheme.ThemeActive == FALSE)
            g->ActiveTheme = g->ClassicTheme;

        GetClientRect(GetDlgItem(hwndDlg, IDC_APPEARANCE_PREVIEW), &rcPreview);

        hdcScreen = GetDC(NULL);
        g->hbmpThemePreview = CreateCompatibleBitmap(hdcScreen, rcPreview.right, rcPreview.bottom);
        g->hdcThemePreview = CreateCompatibleDC(hdcScreen);
        SelectObject(g->hdcThemePreview, g->hbmpThemePreview);
        ReleaseDC(NULL, hdcScreen);

        hwndTheme = GetDlgItem(hwndDlg, IDC_APPEARANCE_VISUAL_STYLE);

        for (pTheme = g->pThemes; pTheme; pTheme = pTheme->NextTheme)
        {
            iListIndex = SendMessage(hwndTheme, CB_ADDSTRING, 0, (LPARAM)pTheme->DisplayName);
            SendMessage(hwndTheme, CB_SETITEMDATA, iListIndex, (LPARAM)pTheme);
            if (pTheme == g->ActiveTheme.Theme)
            {
                SendMessage(hwndTheme, CB_SETCURSEL, (WPARAM)iListIndex, 0);
            }
        }

        if (g->ActiveTheme.Theme)
        {
            AppearancePage_ShowColorSchemes(hwndDlg, g);
            AppearancePage_ShowSizes(hwndDlg, g);
            AppearancePage_UpdateThemePreview(hwndDlg, g);
        }
    }
    g->bInitializing = FALSE;

    return FALSE;
}