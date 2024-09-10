/*****************************************************************************
 * ScrollFont()
 *
 * purpose: scrolls tiny window at bottom
 *
 * params:  none
 *
 * returns: none
 *
 * side effects: alters scroll position variable
 *
 ****************************************************************************/
VOID
ScrollFont(
        VOID
        )
{
        HDC hDC;

    swH = max(0, swH);
    swH = min(100, swH);        /* maintain 0 - 100 range */
    SetScrollPos(hFont, SB_HORZ, swH, TRUE);     /* Move thumb */
    hDC = GetDC(hFont);
    FontShowPaint(hDC);
    ReleaseDC(hFont, hDC);
}