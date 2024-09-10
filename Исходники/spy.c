LRESULT CALLBACK
SpyWndProc(
    HWND hwnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam
    )
{
    switch (msg)
    {
        case WM_CREATE:
            MyCreatePrintfWin(hwnd);
            return 0;

        case WM_INITMENU:
            if (GetMenu(ghwndSpyApp) == (HMENU)wParam)
                InitMenu((HMENU)wParam);

            break;

        case WM_COMMAND:
            return SpyCommand(hwnd, LOWORD(wParam), HIWORD(wParam));

        case WM_ACTIVATE:
            /*
             * Set the focus to the printf window if we are being activated.
             */
            if (LOWORD(wParam))
                SetFocus(ghwndPrintf);

            break;

        case WM_SIZE:
            /*
             * Size the printf window to fit into the new client area size.
             */
            MoveWindow(ghwndPrintf, -gcxBorder, -gcyBorder,
                LOWORD(lParam) + (2 * gcxBorder),
                HIWORD(lParam) + (2 * gcyBorder), TRUE);
            break;

        case WM_CLOSE:
            SetSpyHook(FALSE);

#ifdef JAPAN    // DBCS_FIX
            if (gfhCom1 != INVALID_HANDLE_VALUE)
                CloseHandle(gfhCom1);
#endif
            if (gfhFile)
                _lclose(gfhFile);

            SendMessage(ghwndSpyHook, WM_CLOSE, 0, 0);
            WriteRegistry();
            WaitForSingleObject(ghHookThread, INFINITE);
            DestroyWindow(ghwndSpyApp);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);   /* Kill the main window */
            ghwndSpyApp = NULL;
            ghwndPrintf = NULL;
            break;

        case WM_EXECINSTANCE:
            /*
             * another instance of spy has been started.
             */
            if (IsIconic(hwnd))
                ShowWindow(hwnd,SW_SHOWNORMAL);

            SetForegroundWindow(hwnd);
            BringWindowToTop(hwnd);

            break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    return 0;
}