// Setup instructions control
void SetupInstructions(
    HINSTANCE hInstance,
    HWND hDlg, 
    int ctrlID, 
    int textID
)
{
    WCHAR msg[10240];  // lplp
    HWND hWndTmp;
    SCROLLINFO scrollInfo;
    WNDPROC wpOrigEditProc;

    hWndTmp = GetDlgItem(hDlg, ctrlID);
    if (hWndTmp == NULL)
        {
        return;
        }

    // Assume scrollbar needed; it that way when the text is set and the 
    // scrollbar's details read, they should be correct, bearing in mind the 
    // scrollbar will take up space that would otherwise be used for text
    SDUSetWndStyle(hWndTmp, TRUE, WS_VSCROLL);

    SDUSetWndStyle(hWndTmp, TRUE, ES_MULTILINE);
    SDUSetWndStyle(hWndTmp, TRUE, ES_AUTOVSCROLL);
    SDUSetWndStyle(hWndTmp, TRUE, ES_WANTRETURN);

    // Set the dialog to the string passed in, translating as needed
    SetDlgItemString(
                     G_hInstance,
                     hDlg,
                     ctrlID,
                     textID
                    );

    // Retrieve instructions text, and replace 0x10 chars with 0x10, 
    // 0x13 - required by EDIT (TEXTEDIT) controls
    GetDlgItemTextW(
        hDlg,
        ctrlID,
        msg,
        (sizeof(msg) / sizeof(*msg))
        );
    SDUStringReplaceW(msg, TEXT("\n"), TEXT("\r\n"));
    SetDlgItemTextW(
        hDlg,
        ctrlID,
        msg
        );

    
/*
    SDUSetWndStyle(hWndTmp, TRUE, WS_EX_STATICEDGE);

    //SDUSetWndStyle(hWndTmp, TRUE, WS_VSCROLL);
    scrollInfo.cbSize = sizeof(scrollInfo);
    scrollInfo.fMask = 0; // i.e. DO NOT SET SIF_DISABLENOSCROLL
    scrollInfo.fMask = SIF_DISABLENOSCROLL;
    SetScrollInfo(hWndTmp, SB_VERT, &scrollInfo, TRUE);
*/

    SizeControlMaxWidthBorder(
                              hDlg,
                              ctrlID,
                              FREEOTFE_DLG_BORDER
                             );
    SizeControlMaxDepth(hDlg, ctrlID);

    // Get all the vertial scroll bar information
    memset(&scrollInfo, 0, sizeof(scrollInfo));
    scrollInfo.cbSize = sizeof(scrollInfo);
    scrollInfo.fMask  = SIF_ALL;
    GetScrollInfo(hWndTmp, SB_VERT, &scrollInfo);
    // Save the position for comparison later on
    SizeControlMaxDepth(hDlg, ctrlID);
    SDUSetWndStyle(hWndTmp, (((UINT)scrollInfo.nMax) >= scrollInfo.nPage), WS_VSCROLL);

    // In case the scrollbar was turned on/off, 
    SetWindowPos(
                 hWndTmp, 
                 NULL, 
                 0, 
                 0, 
                 0, 
                 0, 
                 (
                  SWP_DRAWFRAME | 
                  SWP_FRAMECHANGED | 
                  SWP_NOZORDER | 
                  SWP_NOMOVE | 
                  SWP_NOSIZE
                 )
                );

    // Make readonly by intercepting WM_CHAR
    // Don't set the *control* to be readonly, as that results in wrong colour
    // background
    wpOrigEditProc = (WNDPROC)GetWindowLong(hWndTmp, GWL_WNDPROC);
    if (wpOrigEditProc != ReadonlyEditControlProc)
        {
        (WNDPROC)SetWindowLong(hWndTmp, GWL_WNDPROC, (LONG)ReadonlyEditControlProc);
        SetWindowLong(hWndTmp, GWL_USERDATA, (LONG)wpOrigEditProc);
        //lplp - SetWindowLong is WINDOWS MOBILE 5 AND LATER ONLY - NOT WM2003?
        }

}