// -----------------------------------------------------------------------
// Initialize Form
int CALLBACK FRMAboutProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    RECT SplashRect;
    PAINTSTRUCT AboutPs;

    switch(uMsg)
    {
        case WM_INITDIALOG:
            MainAbouthWnd = hwndDlg;
            AboutSerFont8 = GDIObtainFont("MS Sans Serif", 8, hwndDlg, 0, 0);
            AboutCourFont8 = GDIObtainFont("Courier New", 9, hwndDlg, 0, 0);
            CreatePictureBox(0, 0, 500, 194, hwndDlg,
                             LoadBitmap(ApphInstance, MAKEINTRESOURCE(MBMP_BASE + MBMP_TITLE)),
                             IMAGE_BITMAP, 0, 0, SS_CENTERIMAGE);
            AbouthWnd = CreateLabel(4, 195, 302, 104, hwndDlg, "", 2, &FrmAboutTypeWriterHook, 0, 0);
            ControlSetText(hwndDlg, "About " + (CStr) AppTitle);
            FreezeTimer = 1;
            AboutPosInText = 1;
            AboutPosOnScreen = 0;
            AbLine1 = "";
            AbLine2 = "";
            AbLine3 = "";
            AbLine4 = "";
            AbLine5 = "";
            AbLine6 = "";
            AbLine7 = "";
            AbLine8 = "";
            AboutScrollAmount = GDIGetTextHeight(AbouthWnd, AboutCourFont8, "hg");
            AboutText = "\r";
			AboutText = AboutText + (CStr) Requesters + (CStr) "\r";
            AboutText = AboutText + (CStr) "Integrated Development Environment\r";
            AboutText = AboutText + (CStr) "(Build: " __DATE__ + (CStr) ")\r\r";
            AboutText = AboutText + (CStr) "Written by Franck Charlet.\r\r";
            AboutText = AboutText + (CStr) "I would like to thank the following\r";
            AboutText = AboutText + (CStr) "people who have more or less,\r";
            AboutText = AboutText + (CStr) "directly or indirectly contributed\r";
            AboutText = AboutText + (CStr) "to this marvellous tool of mine:\r\r";
            AboutText = AboutText + (CStr) "Barry Allyn (cmax)\r";
            AboutText = AboutText + (CStr) "EliCZ (nt driver model)\r";
            AboutText = AboutText + (CStr) "Cppreference.com people (cpp.chm)\r";
            AboutText = AboutText + (CStr) "Jordan Russel (Inno setup)\r";
            AboutText = AboutText + (CStr) "Me (who ?)\r";
            AboutText = AboutText + (CStr) "Roman Novgorodov (x86eas.hlp)\r";
            AboutText = AboutText + (CStr) "Steve Hutchesson (masm32)\r";
            AboutText = AboutText + (CStr) "So long...\r\r";
            AboutText = AboutText + (CStr) "If you can read this you're dying.\r\r\r\r\r\r\r";
            AboutTimerHandle = SetTimer(hwndDlg, 1, 105, &AboutTimerNotify);
            AboutBrush.lbStyle = BS_SOLID;
            AboutBrush.lbHatch = 0;
            AboutBrush.lbColor = ABOUT_BACKCOLOR;
            hAboutBrush = CreateBrushIndirect(&AboutBrush);
            return(0);
        case WM_ERASEBKGND:
            GetClientRect(hwndDlg, &SplashRect);
            FillRect((HDC) wParam, &SplashRect, hAboutBrush);
            return(1);
        case WM_PAINT:
            BeginPaint(hwndDlg, &AboutPs);
            EndPaint(hwndDlg, &AboutPs);
            break;
        case WM_CLOSE:
            if(hAboutBrush != 0) DeleteObject(hAboutBrush);
            if(AboutTimerHandle != 0) KillTimer(hwndDlg, 1);
            if(AboutCourFont8 != 0) DeleteObject(AboutCourFont8);
            if(AboutSerFont8 != 0) DeleteObject(AboutSerFont8);
            FreezeTimer = 0;
            EndDialog(hwndDlg, 0);
            break;
    }
    return(0);
}