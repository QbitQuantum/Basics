// =========================================================================
BOOL CALLBACK dlgAbout_HandleMsg_WM_INITDIALOG(HWND hDlg)
{
    LPWSTR strVersion;
    SHINITDLGINFO shidi;
    WCHAR betaNumber[5];  // Needs to be long enough to hold the beta number
    DWORD driverVersion;
    WCHAR driverVersionStr[256]; // 256 pretty arbitary; just needs to be big
                                 // enough to store the formatted version
                                 // string
    SDUI18N_LANGUAGEW translationDetails;

    DEBUGOUTGUI(DEBUGLEV_ENTER, (TEXT("dlgAbout_HandleMsg_WM_INITDIALOG\n")));

    shidi.dwMask = SHIDIM_FLAGS;
    shidi.dwFlags = (
                     SHIDIF_DONEBUTTON | 
                     SHIDIF_SIPDOWN | 
                     SHIDIF_SIZEDLGFULLSCREEN
                    );
    shidi.hDlg = hDlg;
    SHInitDialog(&shidi);

    G_dlgAbout_MenuBar = SetupMenu_Simple(hDlg, IDR_MENU_NULL);
    G_URLBrush = CreateSolidBrush(RGB(255, 0, 255));

    SDUi18n_TranslateWindow(hDlg);
    SDUi18n_TranslateCommandBar(G_dlgAbout_MenuBar);

    // App title...
    SDUTextSetBold(hDlg, IDC_APP_TITLE, TRUE);
    SetStaticText(hDlg, IDC_APP_TITLE, APP_TITLE);

    // Meeeee!
    SetStaticText(hDlg, IDC_APP_AUTHORCREDIT, APP_AUTHOR_CREDIT);

    // Translator credit...
    SetControlVisible(hDlg, IDC_APP_TRANSLATORCREDIT, FALSE);
    if (!(SDUi18nIsLanguageCodeEnglishW(G_Options->LanguageCode)))
        {
        if (SDUi18n_GetTranslationDetailsW(
                                    G_Options->LanguageCode,
                                    &translationDetails
                                    ))
            {
            SetStaticText(
                          hDlg, 
                          IDC_APP_TRANSLATORCREDIT,
                          SDUParamSubstituteW(
                             _("%1 translation by %2"),
                             TEXT("%s"), translationDetails.LanguageName,
                             TEXT("%s"), translationDetails.TranslatorName,
                             NULL
                             )
                         );

            SetControlVisible(hDlg, IDC_APP_TRANSLATORCREDIT, TRUE);
            }
        }

    // App version...
    if (SDUGetVersionInfoShortFmtAlloc(
                                  NULL,
                                  &strVersion
                                 ))
        {
        SetStaticText(hDlg, IDC_APP_VERSION, strVersion);
        free(strVersion);
        }		

    if (APP_BETA_BUILD > 0)
        {
        _itow(APP_BETA_BUILD, betaNumber, 10);
        AppendStaticText_ResizeToText(hDlg, IDC_APP_VERSION, TEXT(" "));
        AppendStaticText_ResizeToText(hDlg, IDC_APP_VERSION, _("BETA"));
        AppendStaticText_ResizeToText(hDlg, IDC_APP_VERSION, TEXT(" "));
        AppendStaticText_ResizeToText(hDlg, IDC_APP_VERSION, betaNumber);
        }

    // Driver version...
    SetStaticText(
                  hDlg, 
                  IDC_DRIVER_VERSION, 
                  _("<unknown>")
                 );
    if (driver_VersionID(&driverVersion))
        {
        if (_snwprintf(
                       driverVersionStr, 
                       //(sizeof(driverVersionStr) * sizeof(driverVersionStr[0])),
                       (sizeof(driverVersionStr) / sizeof(driverVersionStr[0])),
                       TEXT("v%d.%0.2d.%0.4d"), 
                       (driverVersion & 0xFF000000) / 0x00FF0000,
                       (driverVersion & 0x00FF0000) / 0x0000FF00,
                       (driverVersion & 0x0000FFFF)
                      ) >= 0)
            {
            SetStaticText(hDlg, IDC_DRIVER_VERSION, driverVersionStr);
            }
        }

    _dlgAbout_AlignControls(hDlg);

    // Tappable URL...
    SetStaticText(hDlg, IDC_STATIC_URL, APP_URL);
    SDUTextSetUnderline(hDlg, IDC_STATIC_URL, TRUE);

    DEBUGOUTGUI(DEBUGLEV_EXIT, (TEXT("dlgAbout_HandleMsg_WM_INITDIALOG\n")));
    return TRUE;
}