static int OnCommand(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (LOWORD(wParam))
    {
        case CMD_OPEN:
        {
            LoadClipboardFromFile();
            break;
        }

        case CMD_SAVE_AS:
        {
            SaveClipboardToFile();
            break;
        }

        case CMD_EXIT:
        {
            PostMessageW(Globals.hMainWnd, WM_CLOSE, 0, 0);
            break;
        }

        case CMD_DELETE:
        {
            if (MessageBoxRes(Globals.hMainWnd, Globals.hInstance,
                              STRING_DELETE_MSG, STRING_DELETE_TITLE,
                              MB_ICONWARNING | MB_YESNO) != IDYES)
            {
                break;
            }

            DeleteClipboardContent();
            break;
        }

        case CMD_AUTOMATIC:
        {
            SetDisplayFormat(0);
            break;
        }

        case CMD_HELP:
        {
            HtmlHelpW(Globals.hMainWnd, L"clipbrd.chm", 0, 0);
            break;
        }

        case CMD_ABOUT:
        {
            HICON hIcon;
            WCHAR szTitle[MAX_STRING_LEN];

            hIcon = LoadIconW(Globals.hInstance, MAKEINTRESOURCE(CLIPBRD_ICON));
            LoadStringW(Globals.hInstance, STRING_CLIPBOARD, szTitle, ARRAYSIZE(szTitle));
            ShellAboutW(Globals.hMainWnd, szTitle, NULL, hIcon);
            DeleteObject(hIcon);
            break;
        }

        default:
        {
            break;
        }
    }
    return 0;
}