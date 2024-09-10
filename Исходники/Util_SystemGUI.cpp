bool DisplayMessageBox(const char* pTitle, const char* pText)
{
    #define ID_EDIT 100

    struct Dialog
    {
        static size_t LineCount(const char* pText)
        {
            size_t count = 0;
            while(*pText)
            {
                if(*pText++ == '\n')
                    count++;
            }
            return count;
        }

        static WORD* WordUp(WORD* pIn){ return (WORD*)((((uintptr_t)pIn + 3) >> 2) << 2); }

        static BOOL CALLBACK Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
        {
            switch (iMsg)
            {
                case WM_INITDIALOG:
                {
                    HWND hWndEdit = GetDlgItem(hDlg, ID_EDIT);

                    const wchar_t* pText = (const wchar_t*)lParam;
                    SetWindowTextW(hWndEdit, pText);

                    HFONT hFont = CreateFontW(-11, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"Courier New");
                    if(hFont)
                        SendMessage(hWndEdit, WM_SETFONT, WPARAM(hFont), TRUE);

                    SendMessage(hWndEdit, EM_SETSEL, (WPARAM)0, (LPARAM)0);

                    return TRUE;
                }

                case WM_COMMAND:
                    switch (LOWORD(wParam))
                    {
                        case ID_EDIT:
                        {
                            // Handle messages from the edit control here.
                            HWND hWndEdit = GetDlgItem(hDlg, ID_EDIT);
                            SendMessage(hWndEdit, EM_SETSEL, (WPARAM)0, (LPARAM)0);
                            return TRUE;
                        }

                        case IDOK:
                            EndDialog(hDlg, 0);
                            return TRUE;
                        case IDABORT:
                            _exit(0); // We don't call abort() because the visual studio runtime
                                      // will capture the signal and throw up another dialog
                    }
                    break;
                case WM_CLOSE:

                    EndDialog(hDlg, 0);
                    return TRUE;
            }

            return FALSE;
        }
    };