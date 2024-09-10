/*********************************************************************************************
 *
 * This is the window procedure for the main window.
 *
 *      Message:                Action:
 *      ========                =======
 *      WM_CREATE               save hInst for dialog box calls, and save menu and window colors
 *      WM_DESTROY              indicate that the window proc is complete
 *      WM_PAINT                print output message centered in client area
 *      WM_SIZE                 save new client dimensions
 *      WM_COMMAND              IDM_LOCALTIME: display message box with local time
 *                              IDM_UPTIME: display message box with time system has been up
 *                              IDM_SHOWCOLORS: display message box with text representation of
 *                                         menu text and background colors
 *                              IDM_CHANGECOLORS: change menu text and background colors
 *                              IDM_RESTORECOLORS: restore menu text and background colors to their
 *                                         original values
 *                              IDM_SCRDIM: display message box with screen dimensions
 *                              IDM_BEEP: display beep dialog
 *                              IDM_EXIT: leave the program
 *
 *********************************************************************************************/
LRESULT CALLBACK WndProc(HWND hWnd,
                 UINT messg,
                 WPARAM wParam,
                 LPARAM lParam)
{
    static HINSTANCE hInst;           // used for dialog box
    static BOOL bNeedToRestoreColors; // flag to do cleanup
    HDC hdc;                          // device context for painting
    PAINTSTRUCT ps;                   // paint structure for painting
    DWORD dElapsedTimeSysHasBeenUp;   // time (ms) since system was booted
    DWORD dOtherTime;                 // another variable to hold time
    char lpstrOutString[256];         // string for message boxes
    SIZE mySize, *lpSize=&mySize;     // used to calculate coordinates to center text
    SYSTEMTIME SysTime;               // system time
    SYSTEMTIME *lpSysTime = &SysTime; // pointer to previous
    DWORD dwCheckColorInfo[2];        // holds color information
    DWORD dwNewColorInfo[2] =         // colors to change (red windows, green menus)
        {RGB(255,0,0),RGB(0,255,0)};
    static DWORD dwSavedColorInfo[2]= // saved colors
        {0,0};
    static int iDisplayElements[2] =  // elements to change
        {COLOR_MENUTEXT, COLOR_MENU};
    int i;                            // temp
    int hsize,vsize,hres,vres;        // screen dimensions

    switch (messg) {
        /*
         * WM_CREATE: get instance handle for later use putting up
         *            dialog box.  Get initial colors for windows and menus
         *            so they can be restored upon exit (unless the user
         *            remembers to do it).
         */
        case WM_CREATE:
            hInst = ((LPCREATESTRUCT) lParam) -> hInstance;
            dwSavedColorInfo[0] = GetSysColor(COLOR_MENUTEXT);
            dwSavedColorInfo[1] = GetSysColor(COLOR_MENU);
            bNeedToRestoreColors = FALSE;
            break;
        /*
         * WM_DESTROY: If user forgot to restore colors, do it.  Then
         *                         terminate this window.
         */
        case WM_DESTROY:
            if (bNeedToRestoreColors) {
                SetSysColors(2,iDisplayElements,dwSavedColorInfo);
                bNeedToRestoreColors = FALSE;
            }
            PostQuitMessage(0);
            break;
        /*
         * WM_PAINT: Put the text string into the window, at the center
         *           of the client area.
         */
        case WM_PAINT:
            hdc = BeginPaint(hWnd,&ps);
            GetTextExtentPoint(hdc,lpstrHiWorld,strlen(lpstrHiWorld),lpSize);
            TextOut(hdc,(newX-(lpSize->cx))/2, (newY-(lpSize->cy))/2, lpstrHiWorld,strlen(lpstrHiWorld));
            EndPaint(hWnd,&ps);
            break;
        /*
         * WM_SIZE: save new x and y coordinates to use later in
         *          centering
         */
        case WM_SIZE:
            newX = LOWORD(lParam);
            newY = HIWORD(lParam);
            break;
        /*
         * WM_COMMAND: see individual items
         */
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                /*
                 * IDM_LOCALTIME: Get the local time, put it into a string,
                 *                then output it via a message box
                 */
                case IDM_LOCALTIME:
                    GetLocalTime(lpSysTime);
                    sprintf(lpstrOutString,"Today is \n\t%02d/%02d/%02d\n and the time is \n\t%02d:%02d:%02d",
                            lpSysTime->wMonth,
                            lpSysTime->wDay,
                            lpSysTime->wYear-1900,
                            lpSysTime->wHour,
                            lpSysTime->wMinute,
                            lpSysTime->wSecond);
                    MessageBox(hWnd,lpstrOutString,"Local time",MB_OK);
                    break;
                /*
                 * IDM_UPTIME: Get the current time, put it into a string,
                 *             then output it via a message box
                 */
                case IDM_UPTIME:
                    dElapsedTimeSysHasBeenUp = GetCurrentTime();
                    dOtherTime = timeGetTime();
                    sprintf(lpstrOutString,"System has been up for:\n\t%d milliseconds (GetCurrentTime)\n\t%d milliseconds (timeGetTime)",
                            dElapsedTimeSysHasBeenUp,dOtherTime);
                    MessageBox(hWnd,lpstrOutString,"Time since system was booted",MB_OK);
                    break;
                /*
                 * IDM_SHOWCOLORS: Get the current menu text and menu background
                 *                 colors.  Put them into a text string then
                 *                 output them via a message box.
                 */
                case IDM_SHOWCOLORS:
                    i = 0;
                    dwCheckColorInfo[0] = GetSysColor(COLOR_MENUTEXT);
                    strcpy(lpstrOutString,"Menu text is ");
                    i += strlen(lpstrOutString);
                    RGB2Text(dwCheckColorInfo[0],&lpstrOutString[i]);
                    dwCheckColorInfo[1] = GetSysColor(COLOR_MENU);
                    strcat(lpstrOutString,"Menu background is ");
                    i = strlen(lpstrOutString);
                    RGB2Text(dwCheckColorInfo[1],&lpstrOutString[i]);
                    MessageBox(hWnd,lpstrOutString,"Color Information",MB_OK);
                    break;
                /*
                 * IDM_CHANGECOLORS: Enable the "restore" menu item.  Set flag to
                 *                   ensure that we clean up, then change the
                 *                   menu text and menu background colors.
                 */
                case IDM_CHANGECOLORS:
                    EnableMenuItem(GetMenu(hWnd),IDM_RESTORECOLORS,MF_ENABLED|MF_BYCOMMAND);
                    bNeedToRestoreColors = TRUE;
                    SetSysColors(2,iDisplayElements,dwNewColorInfo);
                    break;
                /*
                 * IDM_RESTORECOLORS: Disable the "restore" menu item.  Clear the
                 *                    cleanup flag, then change the
                 *                    menu text and menu background colors
                 *                    back to their original values.
                 */
                case IDM_RESTORECOLORS:
                    EnableMenuItem(GetMenu(hWnd),IDM_RESTORECOLORS,MF_GRAYED|MF_BYCOMMAND);
                    bNeedToRestoreColors = FALSE;
                    SetSysColors(2,iDisplayElements,dwSavedColorInfo);
                    break;
                /*
                 * IDM_SCRDIM: Get the screen dimensions, put them into a string,
                 *             then output it via a message box
                 */
                case IDM_SCRDIM:
                    hdc = GetDC(hWnd);
                    hsize = GetDeviceCaps(hdc,HORZSIZE);
                    vsize = GetDeviceCaps(hdc,VERTSIZE);
                    hres = GetDeviceCaps(hdc,HORZRES);
                    vres = GetDeviceCaps(hdc,VERTRES);
                    sprintf(lpstrOutString,
                            "Horizontal size:\t\t%d mm\nVertical Size:\t\t%d mm\nHorizontal resolution:\t%d pixels\nVertical Resolution:\t%d pixels",
                            hsize,vsize,hres,vres);
                    ReleaseDC(hWnd,hdc);
                    MessageBox(hWnd,lpstrOutString,"Screen Dimensions",MB_OK);
                    break;
                /*
                 * IDM_BEEP: Display beep dialog box.
                 */
                case IDM_BEEP:
                    DialogBox(hInst,MAKEINTRESOURCE(BEEPDIALOG),hWnd,BeepDiaProc);
                    break;
                /*
                 * WM_DESTROY: If user forgot to restore colors, do it.  Then
                 *                 terminate this window.
                 */
                case IDM_EXIT:
                    if (bNeedToRestoreColors) {
                        SetSysColors(2,iDisplayElements,dwSavedColorInfo);
                        bNeedToRestoreColors = FALSE;
                    }
                    PostQuitMessage(0);
                    break;
                default:
                    return(DefWindowProc(hWnd,messg,wParam,lParam));
                }
                break;
        default:
            return(DefWindowProc(hWnd,messg,wParam,lParam));
        }
        return(0L);
}