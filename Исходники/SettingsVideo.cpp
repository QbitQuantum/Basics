void SettingsVideo::ApplySettings()
{
    UINT adapterID = (UINT)SendMessage(GetDlgItem(hwnd, IDC_DEVICE), CB_GETCURSEL, 0, 0);
    if (adapterID == CB_ERR)
        adapterID = 0;

    GlobalConfig->SetInt(TEXT("Video"), TEXT("Adapter"), adapterID);

    int curSel = (int)SendMessage(GetDlgItem(hwnd, IDC_MONITOR), CB_GETCURSEL, 0, 0);
    if(curSel != CB_ERR)
        AppConfig->SetInt(TEXT("Video"), TEXT("Monitor"), curSel);

    int iVal = GetEditText(GetDlgItem(hwnd, IDC_SIZEX)).ToInt();
    if(iVal >=  128)
        AppConfig->SetInt(TEXT("Video"), TEXT("BaseWidth"), iVal);

    iVal = GetEditText(GetDlgItem(hwnd, IDC_SIZEY)).ToInt();
    if(iVal >= 128)
        AppConfig->SetInt(TEXT("Video"), TEXT("BaseHeight"), iVal);

    BOOL bDisableAero = SendMessage(GetDlgItem(hwnd, IDC_DISABLEAERO), BM_GETCHECK, 0, 0) == BST_CHECKED ? TRUE : FALSE;
    AppConfig->SetInt(TEXT("Video"), TEXT("DisableAero"), bDisableAero);

    BOOL bFailed;
    int fps = (int)SendMessage(GetDlgItem(hwnd, IDC_FPS), UDM_GETPOS32, 0, (LPARAM)&bFailed);
    AppConfig->SetInt(TEXT("Video"), TEXT("FPS"), (bFailed) ? 30 : fps);

    curSel = (int)SendMessage(GetDlgItem(hwnd, IDC_DOWNSCALE), CB_GETCURSEL, 0, 0);
    if(curSel != CB_ERR)
        AppConfig->SetFloat(TEXT("Video"), TEXT("Downscale"), downscaleMultipliers[curSel]);

    curSel = (int)SendMessage(GetDlgItem(hwnd, IDC_FILTER), CB_GETCURSEL, 0, 0);
    if(curSel == CB_ERR) curSel = 0;
    AppConfig->SetInt(TEXT("Video"), TEXT("Filter"), curSel);

    int gammaVal = (int)SendMessage(GetDlgItem(hwnd, IDC_GAMMA), TBM_GETPOS, 0, 0);
    AppConfig->SetInt(TEXT("Video"), TEXT("Gamma"), gammaVal);

    //------------------------------------

    if(!App->bRunning)
        App->ResizeWindow(false);
    
    if(OSGetVersion() < 8)
    {
        if (bDisableAero)
        {
            Log(TEXT("Settings::Video: Disabling Aero"));
            DwmEnableComposition(DWM_EC_DISABLECOMPOSITION);
        }
        else
        {
            Log(TEXT("Settings::Video: Enabling Aero"));
            DwmEnableComposition(DWM_EC_ENABLECOMPOSITION);
        }
    }
}