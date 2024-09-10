INT_PTR CWipeProp::OnReceiveMsg(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static COLORREF acrCustomClr[16];

    switch (msg)
    {
        case WM_DRAWITEM:
            // Paint the color swatch
            if (wParam == IDC_SMPTE_COLOR)
            {
                HBRUSH solidBrush = CreateSolidBrush(m_dwBorderColor);

                DRAWITEMSTRUCT *pDraw = (DRAWITEMSTRUCT*)lParam;
                FillRect(pDraw->hDC, &pDraw->rcItem, solidBrush);
                FrameRect(pDraw->hDC, &pDraw->rcItem, (HBRUSH)GetStockObject(BLACK_BRUSH));

                DeleteObject(solidBrush);

                return TRUE;
            }
            break;

        case WM_COMMAND:        
            switch (LOWORD(wParam))
            {
                case IDC_SMPTE_PICK_COLOR:
                {
                    // Show the Choose Color dialog to pick a new color swatch
                    CHOOSECOLOR cc;
        
                    ZeroMemory(&cc, sizeof(CHOOSECOLOR));
                    cc.lStructSize = sizeof(CHOOSECOLOR);
                    cc.hwndOwner = m_hDlg;
                    cc.lpCustColors = (LPDWORD)acrCustomClr;
                    cc.Flags = CC_RGBINIT;
                    cc.rgbResult = m_dwBorderColor;
        
                    if (ChooseColor(&cc))
                    {
                        m_dwBorderColor = cc.rgbResult;
                        InvalidateRect(GetDlgItem(hDlg, IDC_SMPTE_COLOR), 0, FALSE);
                    }
                }
                return TRUE;

            } // inner switch            
            break;
    }

    // default
    return FALSE;
}