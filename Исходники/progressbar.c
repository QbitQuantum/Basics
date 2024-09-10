static void pbarOnDraw (HWND hwnd, HDC hdc, PROGRESSDATA* pData, BOOL fVertical)
{
    RECT    rcClient;
    int     x, y, w, h;
    ldiv_t   ndiv_progress;
    unsigned int     nAllPart;
    unsigned int     nNowPart;
    int     whOne, nRem;
    int     ix, iy;
    int     i;
    int     step;
    
    if (pData->nMax == pData->nMin)
        return;
    
    if ((pData->nMax - pData->nMin) > 5)
        step = 5;
    else
        step = 1;

    GetClientRect (hwnd, &rcClient);

    x = rcClient.left + WIDTH_PBAR_BORDER;
    y = rcClient.top + WIDTH_PBAR_BORDER;
    w = RECTW (rcClient) - (WIDTH_PBAR_BORDER << 1);
    h = RECTH (rcClient) - (WIDTH_PBAR_BORDER << 1);

    ndiv_progress = ldiv (pData->nMax - pData->nMin, step);
    nAllPart = ndiv_progress.quot;
    
    ndiv_progress = ldiv (pData->nPos - pData->nMin, step);
    nNowPart = ndiv_progress.quot;
    if (fVertical)
        ndiv_progress = ldiv (h, nAllPart);
    else
        ndiv_progress = ldiv (w, nAllPart);
        
    whOne = ndiv_progress.quot;
    nRem = ndiv_progress.rem;

    SetBrushColor (hdc, GetWindowElementColorEx (hwnd, BKC_HILIGHT_NORMAL));
 
    if (whOne >= 4) {
        if (fVertical) {
            for (i = 0, iy = y + h - 1; i < nNowPart; ++i) {
                if ((iy - whOne) < y) 
                    whOne = iy - y;

                FillBox (hdc, x + 1, iy - whOne, w - 2, whOne - 1);
                iy -= whOne;
                if(nRem > 0) {
                    iy --;
                    nRem --;
                }
            }
        }
        else {
            for (i = 0, ix = x + 1; i < nNowPart; ++i) {
                if ((ix + whOne) > (x + w)) 
                    whOne = x + w - ix;

                FillBox (hdc, ix, y + 1, whOne - 1, h - 2);
                ix += whOne;
                if(nRem > 0) {
                    ix ++;
                    nRem --;
                }
            }
        }
    }
    else {
        // no vertical support
        double d = (nNowPart*1.0)/nAllPart;

        if (fVertical) {
            int prog = (int)(h*d);

            FillBox (hdc, x + 1, rcClient.bottom - WIDTH_PBAR_BORDER - prog, 
                    w - 2, prog);
        }
        else {
            char szText[8];
            SIZE text_ext;
            RECT rc_clip = rcClient;
            int prog = (int)(w*d);

            FillBox (hdc, x, y + 1, (int)(w*d), h - 2);

            SetBkMode (hdc, BM_TRANSPARENT);
            sprintf (szText, "%.0f%%", (d*100));
            GetTextExtent (hdc, szText, -1, &text_ext);
            x += ((w - text_ext.cx) >> 1);
            y += ((h - text_ext.cy) >> 1);

            rc_clip.right = prog;
            SelectClipRect (hdc, &rc_clip);
            SetTextColor (hdc, GetWindowElementColorEx (hwnd, FGC_HILIGHT_NORMAL));
            SetBkColor (hdc, GetWindowElementColorEx (hwnd, BKC_HILIGHT_NORMAL));
            TextOut (hdc, x, y, szText);

            rc_clip.right = rcClient.right;
            rc_clip.left = prog;
            SelectClipRect (hdc, &rc_clip);
            SetTextColor (hdc, GetWindowElementColorEx (hwnd, FGC_CONTROL_NORMAL));
            SetBkColor (hdc, GetWindowBkColor (hwnd));
            TextOut (hdc, x, y, szText);
        }
    }
}