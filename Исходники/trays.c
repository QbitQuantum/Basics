//--------------------------------------------------------------------
// Function:    OnActivateDialog
// 
// Description: 
//
// Input:       hwnd  - 
//              
// Modifies:    
//
// Returns:     
//
//--------------------------------------------------------------------
static void OnActivateDialog(HWND hwnd)
{
    int     i;
    TCHAR   szBuffer[64],
            szFormat[32];
    WORD    wLevel;
    HWND    hwndChild;

    for (i = 0; i < MEDIA_TRAY_MAX_NUMBER; i++)
    {
        if (media_tray[i].bInstalled IS TRUE) 
        {
            loadMediaType(hwnd, IDC_MEDIA_TYPE1 + i, media_tray[i].uMediaTypeID);
        }
        else 
        {
            if (hwndChild = GetDlgItem(hwnd, IDC_MEDIA_TYPE1 + i))
                ShowWindow(hwndChild, SW_HIDE);
            if (hwndChild = GetDlgItem(hwnd, IDC_TRAY1_NAME + i))
                ShowWindow(hwndChild, SW_HIDE);
        }
    }

    LoadString(hInstance, IDS_PERCENT, szFormat, SIZEOF_IN_CHAR(szFormat));

    if (hwndChild = GetDlgItem(hwnd, IDC_MEDIA_STATUS1))
    {
        SetBuf(    szBuffer, sizeof(szBuffer), szFormat, (signed short) media_tray[0].uLevel, &wLevel);
        SetWindowWord(hwndChild, GWW_TRAYLEVEL, wLevel);
        SetWindowText(hwndChild, szBuffer);
    }    

    if (hwndChild = GetDlgItem(hwnd, IDC_MEDIA_STATUS2))
    {
        SetBuf(    szBuffer, sizeof(szBuffer), szFormat, (signed short) media_tray[1].uLevel, &wLevel);
        SetWindowWord(hwndChild, GWW_TRAYLEVEL, wLevel);
        SetWindowText(hwndChild, szBuffer);
    }    

    if (hwndChild = GetDlgItem(hwnd, IDC_MEDIA_STATUS3))
    {
        SetBuf(    szBuffer, sizeof(szBuffer), szFormat, (signed short) media_tray[2].uLevel, &wLevel);
        SetWindowWord(hwndChild, GWW_TRAYLEVEL, wLevel);
        SetWindowText(hwndChild, szBuffer);
    }    

    if (hwndChild = GetDlgItem(hwnd, IDC_MEDIA_STATUS4)) 
    {
        if (media_tray[3].bInstalled IS TRUE) 
        {
            SetBuf(    szBuffer, sizeof(szBuffer), szFormat, (signed short) media_tray[3].uLevel, &wLevel);
            SetWindowWord(hwndChild, GWW_TRAYLEVEL, wLevel);
            SetWindowText(hwndChild, szBuffer);
        }    
        else ShowWindow(hwndChild, SW_HIDE);
    }

    if (hwndChild = GetDlgItem(hwnd, IDC_MEDIA_STATUS5)) 
    {
        if (media_tray[4].bInstalled IS TRUE) 
        {
            SetBuf(    szBuffer, sizeof(szBuffer), szFormat, (signed short) media_tray[4].uLevel, &wLevel);
            SetWindowWord(hwndChild, GWW_TRAYLEVEL, wLevel);
            SetWindowText(hwndChild, szBuffer);
        }
        else ShowWindow (hwndChild, SW_HIDE);
    }
}