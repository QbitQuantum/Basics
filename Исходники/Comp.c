LRESULT HandleNotify(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HIMC hIMC = NULL;
    BOOL fOpen = FALSE;
    DWORD dwConvMode, dwSentMode;


    switch (wParam)
    {
        case IMN_OPENSTATUSWINDOW: /* fall-through */
        case IMN_CLOSESTATUSWINDOW:
            break;

        case IMN_SETOPENSTATUS:
            SetStatusItems(hWnd);

            hIMC = ImmGetContext(hWnd);
            fOpen = ImmGetOpenStatus(hIMC);
            UpdateShowOpenStatusButton(fOpen);

            ImmReleaseContext(hWnd,hIMC);
            break;

        case IMN_SETCONVERSIONMODE:
            hIMC = ImmGetContext(hWnd);
            fOpen = ImmGetOpenStatus(hIMC);
            ImmGetConversionStatus(hIMC,&dwConvMode,&dwSentMode);
            if (fOpen)
            {
                SetConvModeParts(dwConvMode);
                UpdateModeButton(dwConvMode);
            }
            else
            {
                ClearConvModeParts();
            }
            ImmReleaseContext(hWnd,hIMC);
            break;

        case IMN_OPENCANDIDATE:
            if (!fShowCand || (lParam != 0x01))
            {
                if (fdwProperty & IME_PROP_SPECIAL_UI)
                {
                    // Normally, we only need to set the composition window
                    // position for a special UI IME
                }
                else if (fdwProperty & IME_PROP_AT_CARET)
                {
                    CANDIDATEFORM cdf;
                    HIMC          hIMC;
 
                    hIMC = ImmGetContext(hWnd);

                    cdf.dwIndex = 0;
                    cdf.dwStyle = CFS_CANDIDATEPOS;
                    cdf.ptCurrentPos.x = ptImeUIPos.x;
                    cdf.ptCurrentPos.y = ptImeUIPos.y;
                    ImmSetCandidateWindow(hIMC,&cdf);

                    ImmReleaseContext(hWnd,hIMC);
                }
                else
                {
                    // Normally, we only need to set the composition window
                    // position for a near caret IME
                }

                return (DefWindowProc(hWnd, message, wParam, lParam));
            }

        case IMN_CHANGECANDIDATE:

#ifdef _DEBUG
            {
                TCHAR szDev[80];
                DWORD dwSize;
                LPCANDIDATELIST lpC;

                hIMC = ImmGetContext(hWnd);
                if (dwSize = ImmGetCandidateList(hIMC,0x0,NULL,0))
                {
                    lpC = (LPCANDIDATELIST)GlobalAlloc(GPTR,dwSize);
                   
                    ImmGetCandidateList(hIMC,0x0,lpC,dwSize);

                    OutputDebugString(TEXT("DumpCandList!!!\r\n"));
                    StringCchPrintf((LPTSTR)szDev,ARRAYSIZE(szDev),TEXT("dwCount %d\r\n"),lpC->dwCount);
                    OutputDebugString((LPTSTR)szDev);
                    StringCchPrintf((LPTSTR)szDev,ARRAYSIZE(szDev),TEXT("dwSelection %d\r\n"),lpC->dwSelection);
                    OutputDebugString((LPTSTR)szDev);
                    StringCchPrintf((LPTSTR)szDev,ARRAYSIZE(szDev),TEXT("dwPageStart %d\r\n"),lpC->dwPageStart);
                    OutputDebugString((LPTSTR)szDev);
                    StringCchPrintf((LPTSTR)szDev,ARRAYSIZE(szDev),TEXT("dwPageSize %d\r\n"),lpC->dwPageSize);
                    OutputDebugString((LPTSTR)szDev);
                    GlobalFree((HANDLE)lpC);
                }
            }
#endif
            if (fShowCand && (lParam == 0x01))
            {
                DWORD dwSize;

                if (!lpCandList)
                    lpCandList = (LPCANDIDATELIST)GlobalAlloc(GPTR,sizeof(CANDIDATELIST));

                hIMC = ImmGetContext(hWnd);
                if (dwSize = ImmGetCandidateList(hIMC,0x0,NULL,0))
                {
                    GlobalFree((HANDLE)lpCandList);
                    lpCandList = (LPCANDIDATELIST)GlobalAlloc(GPTR,dwSize);
                   
                    ImmGetCandidateList(hIMC,0x0,lpCandList,dwSize);
                }
                else
                {
                    memset(lpCandList, 0, sizeof(CANDIDATELIST));
                }

                InvalidateRect(hWndCandList,NULL,TRUE);
                UpdateWindow(hWndCandList);
                    

                ImmReleaseContext(hWnd,hIMC);
            }
            else
            {
                return (DefWindowProc(hWnd, message, wParam, lParam));
            }
            break;

        case IMN_CLOSECANDIDATE:
            if (fShowCand && (lParam == 0x01))
            {
                if (!lpCandList)
                {
                    lpCandList = (LPCANDIDATELIST)GlobalAlloc(GPTR,sizeof(CANDIDATELIST));
                }

                memset(lpCandList, 0, sizeof(CANDIDATELIST));
                InvalidateRect(hWndCandList,NULL,TRUE);
                UpdateWindow(hWndCandList);
            }
            else
            {
                return (DefWindowProc(hWnd, message, wParam, lParam));
            }
            break;


       default:
            return (DefWindowProc(hWnd, message, wParam, lParam));
    }

    return 0;
}