LRESULT CALLBACK CompStrWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HIMC hIMC    = NULL;
    HIMC hOldIMC = NULL;

    switch (message) 
    {
        case WM_CREATE:
            hIMC = ImmCreateContext();
            hOldIMC = ImmAssociateContext(hWnd,hIMC);
            SetWindowLongPtr(hWnd, 0, (LONG_PTR)hOldIMC);
            fdwProperty = ImmGetProperty(GetKeyboardLayout(0), IGP_PROPERTY);
            break;

        case WM_CHAR:
            HandleChar(hWnd,wParam,lParam);
            break;

        case WM_LBUTTONUP:  /* fall-through */
        case WM_RBUTTONUP:
            if (hIMC = ImmGetContext(hWnd))
            {
                HMENU hMenu = NULL;

                InitMenuItemIDTable();
                hMenu = CreateImeMenu(hWnd, hIMC, NULL,(message == WM_RBUTTONUP));

                if (hMenu)
                {
                    DWORD dwItemData;
                    DWORD dwPos = (DWORD)GetMessagePos();
                    int nCmd;
                  
                    nCmd = TrackPopupMenuEx(hMenu,
                                            TPM_RETURNCMD | TPM_NONOTIFY | 
                                            TPM_LEFTBUTTON | TPM_LEFTALIGN | TPM_TOPALIGN, 
                                            LOWORD(dwPos), HIWORD(dwPos), 
                                            hWnd, NULL);

                    if (nCmd)
                    {
                        nCmd -= IDM_STARTIMEMENU;
                        dwItemData = FindItemData(nCmd);
                        ImmNotifyIME(hIMC, NI_IMEMENUSELECTED, nCmd, dwItemData);
                    }
                }
                EndMenuItemIDTable();

                DestroyMenu(hMenu);
            }
            break;

        case WM_IME_SETCONTEXT:
            if (fShowCand)
            {
                lParam &= ~ISC_SHOWUICANDIDATEWINDOW;
            }

            if (fdwProperty & IME_PROP_SPECIAL_UI)
            {
                // EMPTY
            }
            else if (fdwProperty & IME_PROP_AT_CARET)
            {
                lParam &= ~ISC_SHOWUICOMPOSITIONWINDOW;
            }
            else
            {
                // EMPTY
            }

            return (DefWindowProc(hWnd, message, wParam, lParam));

        case WM_IME_STARTCOMPOSITION:
            // Normally, we should not call into HandleStartComposition
            // for IME_PROP_SPECIAL_UI and not IME_PROP_AT_CARET IMEs
            // we should pass this message to DefWindowProc directly for
            // this kind of IMEs

            HandleStartComposition(hWnd,wParam,lParam);

            // pass this message to DefWindowProc for IME_PROP_SPECIAL_UI
            // and not IME_PROP_AT_CARET IMEs

            if (fdwProperty & IME_PROP_SPECIAL_UI)
            {
                return (DefWindowProc(hWnd, message, wParam, lParam));
            }
            else if (fdwProperty & IME_PROP_AT_CARET)
            {
                // EMPTY
            }
            else
            {
                return (DefWindowProc(hWnd, message, wParam, lParam));
            }

            break;

        case WM_IME_ENDCOMPOSITION:
            // Normally, we should not call into HandleEndComposition
            // for IME_PROP_SPECIAL_UI and not IME_PROP_AT_CARET IMEs
            // we should pass this message to DefWindowProc directly for
            // this kind of IMEs

            HandleEndComposition(hWnd,wParam,lParam);

            // pass this message to DefWindowProc for IME_PROP_SPECIAL_UI
            // and not IME_PROP_AT_CARET IMEs

            if (fdwProperty & IME_PROP_SPECIAL_UI)
            {
                return (DefWindowProc(hWnd, message, wParam, lParam));
            }
            else if (fdwProperty & IME_PROP_AT_CARET)
            {
                // EMPTY
            }
            else
            {
                return (DefWindowProc(hWnd, message, wParam, lParam));
            }
            break;

        case WM_IME_COMPOSITION:
            // Normally, we should not call into HandleComposition
            // for IME_PROP_SPECIAL_UI and not IME_PROP_AT_CARET IMEs
            // we should pass this message to DefWindowProc directly for
            // this kind of IMEs

            HandleComposition(hWnd,wParam,lParam);

            // pass this message to DefWindowProc for IME_PROP_SPECIAL_UI
            // and not IME_PROP_AT_CARET IMEs

            if (fdwProperty & IME_PROP_SPECIAL_UI)
            {
                return (DefWindowProc(hWnd, message, wParam, lParam));
            }
            else if (fdwProperty & IME_PROP_AT_CARET)
            {
                // EMPTY
            }
            else
            {
                return (DefWindowProc(hWnd, message, wParam, lParam));
            }
            break;

        case WM_PAINT:
            HandlePaint(hWnd,wParam,lParam);
            break;

        case WM_IME_NOTIFY:
            {
                LRESULT lRet;

                // Normally, we should not call into HandleNotify
                // for IME_PROP_SPECIAL_UI and not IME_PROP_AT_CARET IMEs
                // we should pass this message to DefWindowProc directly for
                // this kind of IMEs

                lRet = HandleNotify(hWnd, message, wParam, lParam);
 
                // pass this message to DefWindowProc for IME_PROP_SPECIAL_UI
                // and not IME_PROP_AT_CARET IMEs

                if (fdwProperty & IME_PROP_SPECIAL_UI)
                {
                    return (DefWindowProc(hWnd, message, wParam, lParam));
                }
                else if (fdwProperty & IME_PROP_AT_CARET)
                {
                    // EMPTY
                }
                else
                {
                    return (DefWindowProc(hWnd, message, wParam, lParam));
                }

                return lRet;
            }

        case WM_DESTROY:
            hOldIMC = (HIMC)GetWindowLongPtr(hWnd, 0);
            hIMC = ImmAssociateContext(hWnd, hOldIMC);
            ImmDestroyContext(hIMC);
            break;

        case WM_INPUTLANGCHANGE:
            fdwProperty = ImmGetProperty(GetKeyboardLayout(0), IGP_PROPERTY);

            if (hIMC = ImmGetContext(hWnd))
            {
                CANDIDATEFORM cdf = {0};

                if (fdwProperty & IME_PROP_AT_CARET)
                {
                    cdf.dwIndex = 0;
                    cdf.dwStyle = CFS_CANDIDATEPOS;
                    cdf.ptCurrentPos.x = ptImeUIPos.x;
                    cdf.ptCurrentPos.y = ptImeUIPos.y;
                    ImmSetCandidateWindow(hIMC, &cdf);
                }
                else
                {
                    UINT i;

                    // The candidate position should be decided by a near caret
                    // IME. There are 4 candidate form in the input context

                    for (i = 0; i < 4; i++)
                    {
                        if (!ImmGetCandidateWindow(hIMC, i, &cdf))
                        {
                            continue;
                        }

                        if (cdf.dwStyle == CFS_DEFAULT)
                        {
                            continue;
                        }

                        cdf.dwStyle = CFS_DEFAULT;

                        ImmSetCandidateWindow(hIMC, &cdf);
                    }

                }

                ImmReleaseContext(hWnd, hIMC);
            }

            return (DefWindowProc(hWnd, message, wParam, lParam));

        default:
	        return (DefWindowProc(hWnd, message, wParam, lParam));
    }
    return 0L;
}