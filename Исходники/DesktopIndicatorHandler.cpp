// Called from the Windows notification handler thread, in its message loop
LRESULT CALLBACK
DesktopIndicatorHandler::WndProc
(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
    // Check for our special notification message
    if ((uMessage != WM_DESKTOPINDICATOR_CLICK)) {
        return DefWindowProc(hWnd, uMessage, wParam, lParam);
    }
    DesktopIndicatorHandler *pthis = (DesktopIndicatorHandler *)
        GetWindowLong(hWnd, GWL_USERDATA);
    switch (lParam) {
    case WM_LBUTTONDBLCLK:
        // Execute the default action of the right-click popup menu
        pthis->restoreApplication();
        break;
    //case WM_LBUTTONDOWN:
    //case WM_RBUTTONDOWN:
    //case WM_LBUTTONUP:
        //break;
    case WM_RBUTTONUP: // Display popup menu on right click
        {
            SetForegroundWindow(hWnd);
            POINT pos;
            GetCursorPos(&pos);
            int cxMenuCheck = GetSystemMetrics(SM_CXMENUCHECK);
            int cyMenuCheck = GetSystemMetrics(SM_CYMENUCHECK);
            HMENU hMenu = CreatePopupMenu();
            UAppendMenu(hMenu, MF_STRING, MNU_RESTORE,
                pthis->m_lpwszItemRestore);     // L"Restore";
            UAppendMenu(hMenu, MF_STRING, MNU_ABOUT,
                pthis->m_lpwszItemAbout);       // L"About...";
            UAppendMenu(hMenu, MF_SEPARATOR, 0, (LPCWSTR)NULL);
            UAppendMenu(hMenu, MF_STRING, MNU_EXIT_AFTER,
                pthis->m_lpwszItemExitLater);   // L"Exit After Transfers";
            UAppendMenu(hMenu, MF_STRING, MNU_EXIT,
                pthis->m_lpwszItemExit);        // L"Exit";
            //Load 15x15 bitmaps for unchecked state of menu options
            //Remap colors  #000000, #808080, #C0C0C0, #DFDFDF, #FFFFFF
            //to 3D colors: DlgText, 3DDark, 3DFace, 3DLight, WindowBg
            HBITMAP hbmpRestore = (HBITMAP)LoadImageA(
                ::g_hInstance, MAKEINTRESOURCEA(IDB_RESTORE),
                IMAGE_BITMAP, cxMenuCheck, cyMenuCheck,
                LR_LOADMAP3DCOLORS);
            HBITMAP hbmpHelp = (HBITMAP)LoadImageA(
                ::g_hInstance, MAKEINTRESOURCEA(IDB_HELP),
                IMAGE_BITMAP, cxMenuCheck, cyMenuCheck,
                LR_LOADMAP3DCOLORS);
            HBITMAP hbmpWaitClose = (HBITMAP)LoadImageA(
                ::g_hInstance, MAKEINTRESOURCEA(IDB_WAITCLOSE),
                IMAGE_BITMAP, cxMenuCheck, cyMenuCheck,
                LR_LOADMAP3DCOLORS);
            HBITMAP hbmpClose = (HBITMAP)LoadImageA(
                ::g_hInstance, MAKEINTRESOURCEA(IDB_CLOSE),
                IMAGE_BITMAP, cxMenuCheck, cyMenuCheck,
                LR_LOADMAP3DCOLORS);
            SetMenuItemBitmaps(hMenu, MNU_RESTORE, MF_BYCOMMAND,
                hbmpRestore, (HBITMAP)NULL);
            SetMenuItemBitmaps(hMenu, MNU_ABOUT, MF_BYCOMMAND,
                hbmpHelp, (HBITMAP)NULL);
            SetMenuItemBitmaps(hMenu, MNU_EXIT_AFTER, MF_BYCOMMAND,
                hbmpWaitClose, (HBITMAP)NULL);
            SetMenuItemBitmaps(hMenu, MNU_EXIT, MF_BYCOMMAND,
                hbmpClose, (HBITMAP)NULL);
            SetMenuDefaultItem(hMenu, MNU_RESTORE, MF_BYCOMMAND);
            switch (TrackPopupMenu(hMenu,
                TPM_CENTERALIGN | TPM_BOTTOMALIGN |
                TPM_LEFTBUTTON |
                TPM_NONOTIFY | TPM_RETURNCMD, /* return an item.wID instead of BOOL */
                pos.x, pos.y,
                0, hWnd, (LPCRECT)NULL)) {
            case MNU_RESTORE:
                pthis->restoreApplication();
                break;
            case MNU_ABOUT:
                pthis->showAboutWindow();
                break;
            case MNU_EXIT_AFTER:
                pthis->exitAfterTransfers();
                break;
            case MNU_EXIT:
                pthis->exitApplication();
                break;
            }
            DestroyMenu(hMenu);
            DeleteObject((HGDIOBJ)hbmpRestore);
            DeleteObject((HGDIOBJ)hbmpClose);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return 0;
}