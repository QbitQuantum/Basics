LONG CALLBACK ResultImageWndProc(HWND hWnd, UINT iMsg,
        WPARAM wParam, LPARAM lParam)
{
        UINT            iBmp;
        PAINTSTRUCT     ps;
        HDC             hDC;

        //Handle standard Windows messages.
        switch (iMsg)
        {
                case WM_CREATE:
                        SetWindowWord(hWnd, RIWW_IMAGEINDEX, RESULTIMAGE_NONE);
                        return 0L;

                case WM_PAINT:
                        iBmp = GetWindowWord(hWnd, RIWW_IMAGEINDEX);
                        hDC = BeginPaint(hWnd, &ps);

                        RECT            rc;
                        UINT            x, y;
                        HDC             hDCDlg;
                        HBRUSH          hBr;
                        LOGBRUSH        lb;
                        HWND            hDlg;

                        /*
                         * Our job before using TransparentBlt is to figure out
                         * where to position the result image.  We place it centered
                         * on this control, so get our rect's center and subtract
                         * half of the image dimensions.
                         */
                        GetClientRect(hWnd, &rc);
                        x = (rc.right+rc.left-cxBmpResult)/2;
                        y = (rc.bottom+rc.top-cyBmpResult)/2;

                        // Get the backgroup color the dialog is using.
                        hDlg=GetParent(hWnd);
                        hDCDlg=GetDC(hDlg);
                        hBr = (HBRUSH)SendMessage(hDlg,
                                                                        WM_CTLCOLORDLG,
                                                                        (WPARAM)hDCDlg,
                                                                        (LPARAM)hDlg);
                        ReleaseDC(hDlg, hDCDlg);
                        GetObject(hBr, sizeof(LOGBRUSH), &lb);
                        SetBkColor(hDC, lb.lbColor);


                        if (RESULTIMAGE_NONE != iBmp)
                        {

                            TransparentBlt(hDC, x, y, hBmpResults, iBmp*cxBmpResult, 0,
                                    cxBmpResult, cyBmpResult, RGBTRANSPARENT);
                        }
                        else
                        {
                            FillRect(hDC, &rc, hBr);
                        }
                        EndPaint(hWnd, &ps);
                        break;

                case RIM_IMAGESET:
                        // wParam contains the new index.
                        iBmp=GetWindowWord(hWnd, RIWW_IMAGEINDEX);

                        // Validate the index before changing it and repainting
                        if (RESULTIMAGE_NONE==wParam ||
                                ((RESULTIMAGE_MIN <= wParam) && (RESULTIMAGE_MAX >= wParam)))
                        {
                                SetWindowWord(hWnd, RIWW_IMAGEINDEX, (WORD)wParam);
                                InvalidateRect(hWnd, NULL, FALSE);
                                UpdateWindow(hWnd);
                        }
                        // Return the previous index.
                        return iBmp;

                case RIM_IMAGEGET:
                        // Return the current index.
                        iBmp=GetWindowWord(hWnd, RIWW_IMAGEINDEX);
                        return (LONG)iBmp;

                default:
                        return DefWindowProc(hWnd, iMsg, wParam, lParam);
        }

        return 0L;
}