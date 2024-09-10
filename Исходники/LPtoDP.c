static void DoTestEntry(HDC hDC, const TEST_ENTRY *entry)
{
    POINT pt, ptWnd, ptView;
    SIZE siz, sizWnd, sizView;
    INT ret;

    SetMapMode(hDC, entry->nMapMode);

    ret = SetWindowOrgEx(hDC, entry->preset.xWnd, entry->preset.yWnd, NULL);
    ok(ret == TRUE, "Line %d: SetWindowOrgEx failed\n", entry->lineno);

    ret = SetWindowExtEx(hDC, entry->preset.cxWnd, entry->preset.cyWnd, NULL);
    ok(ret == entry->bWndExt, "Line %d: SetWindowExtEx() expected %d, was %d\n", entry->lineno, entry->bWndExt, ret);

    ret = SetViewportOrgEx(hDC, entry->preset.xView, entry->preset.yView, NULL);
    ok(ret == TRUE, "Line %d: SetViewportOrgEx failed\n", entry->lineno);

    ret = SetViewportExtEx(hDC, entry->preset.cxView, entry->preset.cyView, NULL);
    ok(ret == TRUE, "Line %d: SetViewportExtEx failed\n", entry->lineno);

    ok(GetWindowOrgEx(hDC, &pt) == TRUE, "Line %d: GetWindowOrgEx failed\n", entry->lineno);
    ptWnd = pt;
    ok(GetWindowExtEx(hDC, &siz) == TRUE, "Line %d: GetWindowExtEx failed\n", entry->lineno);
    sizWnd = siz;

    ok(pt.x == entry->xWndOut && pt.y == entry->yWndOut,
       "Line %d: Window org expected (%ld, %ld), was (%ld, %ld)\n",
        entry->lineno, entry->xWndOut, entry->yWndOut, pt.x, pt.y);

    if (entry->cxWndOut == DISPLAY_SIZE || entry->cxWndOut == NEGA_DISPLAY_SIZE)
    {
        LONG cx = GetDeviceCaps(hDC, HORZRES);
        LONG cy = GetDeviceCaps(hDC, VERTRES);
        if (entry->cxWndOut == NEGA_DISPLAY_SIZE)
            cx = -cx;
        if (entry->cyWndOut == NEGA_DISPLAY_SIZE)
            cy = -cy;
        ok(siz.cx == cx && siz.cy == cy,
           "Line %d: Window ext expected display size (%ld, %ld), was (%ld, %ld)\n",
            entry->lineno, cx, cy, siz.cx, siz.cy);
    }
    else if (entry->cxWndOut != NO_CHECK)
    {
        ok(siz.cx == entry->cxWndOut && siz.cy == entry->cyWndOut,
           "Line %d: Window ext expected (%ld, %ld), was (%ld, %ld)\n",
            entry->lineno, entry->cxWndOut, entry->cyWndOut, siz.cx, siz.cy);
    }

    ok(GetViewportOrgEx(hDC, &pt) == TRUE, "Line %d: GetViewportOrgEx failed\n", entry->lineno);
    ptView = pt;
    ok(GetViewportExtEx(hDC, &siz) == TRUE, "Line %d: GetViewportExtEx failed\n", entry->lineno);
    sizView = siz;

    ok(pt.x == entry->xViewOut && pt.y == entry->yViewOut,
       "Line %d: Viewport org expected (%ld, %ld), was (%ld, %ld)\n",
        entry->lineno, entry->xViewOut , entry->yViewOut, pt.x, pt.y);

    if (entry->cxViewOut == DISPLAY_SIZE || entry->cxViewOut == NEGA_DISPLAY_SIZE)
    {
        LONG cx = GetDeviceCaps(hDC, HORZRES);
        LONG cy = GetDeviceCaps(hDC, VERTRES);
        if (entry->cxViewOut == NEGA_DISPLAY_SIZE)
            cx = -cx;
        if (entry->cyViewOut == NEGA_DISPLAY_SIZE)
            cy = -cy;
        ok(siz.cx == cx && siz.cy == cy,
           "Line %d: Viewport ext expected display size (%ld, %ld), was (%ld, %ld)\n",
            entry->lineno, cx, cy, siz.cx, siz.cy);
    }
    else if (entry->cxViewOut != NO_CHECK)
    {
        ok(siz.cx == entry->cxViewOut && siz.cy == entry->cyViewOut,
           "Line %d: Viewport ext expected (%ld, %ld), was (%ld, %ld)\n",
            entry->lineno, entry->cxViewOut, entry->cyViewOut, siz.cx, siz.cy);
    }

    pt = entry->ptSrc;

    SetLastError(0xDEADBEEF);
    ret = LPtoDP(hDC, &pt, 1);
    ok(ret == entry->ret, "Line %d: LPtoDP() expected %d, was %d\n", entry->lineno, entry->ret, ret);

    ok(GetLastError() == entry->error, "Line %d: GetLastError() expected %ld, was %ld\n",
       entry->lineno, entry->error, GetLastError());

    if (entry->ptDest.x == CALC_VALUE_1)
    {
        LONG x = MulDiv(entry->ptSrc.x - ptWnd.x, sizView.cx, sizWnd.cx) + ptView.x;
        LONG y = MulDiv(entry->ptSrc.y - ptWnd.y, sizView.cy, sizWnd.cy) + ptView.y;
        // TODO: make more accurate
        ok(labs(pt.x - x) <= 1 && labs(pt.y - y) <= 1,
           "Line %d: Dest expected (%ld, %ld), was (%ld, %ld)\n",
           entry->lineno, x, y, pt.x, pt.y);
    }
    else if (entry->ptDest.x == CALC_VALUE_2)
    {
        XFORM xform;
        LONG x, y;
        SetXForm1(&xform);
        x = (LONG)((xform.eM11 * entry->ptSrc.x + xform.eM12 * entry->ptSrc.y) + xform.eDx);
        y = (LONG)((xform.eM21 * entry->ptSrc.x + xform.eM22 * entry->ptSrc.y) + xform.eDy);
        x = MulDiv(x - ptWnd.x, sizView.cx, sizWnd.cx) + ptView.x;
        y = MulDiv(y - ptWnd.y, sizView.cy, sizWnd.cy) + ptView.y;
        // TODO: make more accurate
        ok(labs(pt.x - x) <= 1 && labs(pt.y - y) <= 1,
           "Line %d: Dest expected (%ld, %ld), was (%ld, %ld)\n",
           entry->lineno, x, y, pt.x, pt.y);
    }
    else if (entry->ptDest.x == CALC_VALUE_3)
    {
        XFORM xform;
        LONG x, y;
        SetXForm2(&xform);
        x = (LONG)((xform.eM11 * entry->ptSrc.x + xform.eM12 * entry->ptSrc.y) + xform.eDx);
        y = (LONG)((xform.eM21 * entry->ptSrc.x + xform.eM22 * entry->ptSrc.y) + xform.eDy);
        x = MulDiv(x - ptWnd.x, sizView.cx, sizWnd.cx) + ptView.x;
        y = MulDiv(y - ptWnd.y, sizView.cy, sizWnd.cy) + ptView.y;
        // TODO: make more accurate
        ok(labs(pt.x - x) <= 2 && labs(pt.y - y) <= 2,
           "Line %d: Dest expected (%ld, %ld), was (%ld, %ld)\n",
           entry->lineno, x, y, pt.x, pt.y);
    }
    else if (entry->ptDest.x != NO_CHECK)
    {
        ok(pt.x == entry->ptDest.x && pt.y == entry->ptDest.y,
           "Line %d: Dest expected (%ld, %ld), was (%ld, %ld)\n",
           entry->lineno, entry->ptDest.x, entry->ptDest.y, pt.x, pt.y);
    }
}