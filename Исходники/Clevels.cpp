INT_PTR TlevelsPage::msgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_DESTROY:
        SelectObject(hdcGradient, oldHDCgradient);
        DeleteDC(hdcGradient);
        DeleteBitmap(bmpGradient);
        DeleteFont(fontGradient);
        SendMessage(GetDlgItem(m_hwnd, IDC_LBX_LEVELS_CURVES), WM_SETFONT, NULL, FALSE);
        DeleteFont(fontCurier);
        break;
    case WM_DRAWITEM:
        switch (wParam) {
        case IDC_BMP_HISTOGRAM: {
            LPDRAWITEMSTRUCT dis = LPDRAWITEMSTRUCT(lParam);
            int full = cfgGet(IDFF_levelsFullY);
            StretchDIBits(dis->hDC, 0, 0, dis->rcItem.right, dis->rcItem.bottom, full ? 0 : 16, 0, full ? 256 : 234 - 16 + 1, 64, histogramBits, (BITMAPINFO*)&histogramBmp, DIB_RGB_COLORS, SRCCOPY);
            wIn->draw(dis);
            return TRUE;
        }
        case IDC_BMP_LEVELS_IN: {
            LPDRAWITEMSTRUCT dis = LPDRAWITEMSTRUCT(lParam);
            StretchBlt(dis->hDC, 0, 0, dis->rcItem.right, 10, hdcGradient, 0, 0, 256, 1, SRCCOPY);
            RECT r = dis->rcItem;
            r.top = 10;
            FillRect(dis->hDC, &r, GetSysColorBrush(COLOR_BTNFACE));
            if (filter && getCheck(IDC_CHB_LEVELS_INPUT_AUTO)) {
                int min, max;
                filter->getInAuto(&min, &max);
                drawTriangle(dis, min, true);
                drawTriangle(dis, max, true);
            }
            drawTriangle(dis, cfgGet(IDFF_levelsInMin));
            drawTriangle(dis, cfgGet(IDFF_levelsInMax));
            return TRUE;
        }
        case IDC_BMP_LEVELS_OUT: {
            LPDRAWITEMSTRUCT dis = LPDRAWITEMSTRUCT(lParam);
            StretchBlt(dis->hDC, 0, 0, dis->rcItem.right, 10, hdcGradient, 0, 0, 256, 1, SRCCOPY);
            RECT r = dis->rcItem;
            r.top = 10;
            FillRect(dis->hDC, &r, GetSysColorBrush(COLOR_BTNFACE));
            drawTriangle(dis, cfgGet(IDFF_levelsOutMin));
            drawTriangle(dis, cfgGet(IDFF_levelsOutMax));
            return TRUE;
        }
        case IDC_BMP_LEVELS_CURVES: {
            LPDRAWITEMSTRUCT dis = LPDRAWITEMSTRUCT(lParam);
            StretchDIBits(dis->hDC, 0, 0, dis->rcItem.right, dis->rcItem.bottom, 0, 0, 256, 256, histogramBits, (BITMAPINFO*)&curvesBmp, DIB_RGB_COLORS, SRCCOPY);
            wCurves->draw(dis);
            return TRUE;
        }
        }
        break;
    case WM_SETCURSOR:
        if (HWND(wParam) == hcurves) {
            if (wCurves->setCursor()) {
                SetCursor(LoadCursor(NULL, IDC_SIZEALL));
                setDlgResult(TRUE);
            }
            return TRUE;
        }
        break;
    }
    return TconfPageDecVideo::msgProc(uMsg, wParam, lParam);
}