void GUIAPI PutSavedBoxOnDC (HDC hdc, int x, int y, int w, int h, void* vbuf)
{
    PCLIPRECT pClipRect;
    PDC pdc;
    RECT rcOutput;

    pdc = dc_HDC2PDC(hdc);

    if (dc_IsGeneralHDC(hdc)) {
        if (!dc_GenerateECRgn (pdc, FALSE)) {
            return;
        }
    }

    // Transfer logical to device to screen here.
    w += x; h += y;
    coor_LP2SP(pdc, &x, &y);
    coor_LP2SP(pdc, &w, &h);
    rcOutput.left = x;
    rcOutput.top = y;
    rcOutput.right = w;
    rcOutput.bottom = h;
    NormalizeRect (&rcOutput);
    w = RECTW (rcOutput); h = RECTH (rcOutput);

    IntersectRect (&rcOutput, &rcOutput, &pdc->ecrgn.rcBound);
    if( !dc_IsMemHDC(hdc) ) ShowCursorForGDI(FALSE, &rcOutput);

    GAL_SetGC (pdc->gc);

    pClipRect = pdc->ecrgn.head;
    while(pClipRect)
    {
        if (DoesIntersect (&rcOutput, &pClipRect->rc)) {
            GAL_SetClipping(pdc->gc, pClipRect->rc.left, pClipRect->rc.top,
                    pClipRect->rc.right - 1, pClipRect->rc.bottom - 1);

            GAL_PutBox (pdc->gc, x, y, w, h, vbuf);
        }

        pClipRect = pClipRect->next;
    }

    if( !dc_IsMemHDC(hdc) ) ShowCursorForGDI(TRUE, &rcOutput);
}