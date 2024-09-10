// ============================================================================
//
//  GetMenuItemRect()
//
// ============================================================================
BOOL xxxGetMenuItemRect(PWND pwnd, PMENU pMenu, UINT uIndex, LPRECT lprcScreen)
{
    PITEM  pItem;
    int     dx, dy;

    CheckLock(pwnd);
    CheckLock(pMenu);

    SetRectEmpty(lprcScreen);

    if (uIndex >= pMenu->cItems)
        return(FALSE);

    /*
     * Raid #315084: Compatiblity with NT4/Win95/98
     *
     * WordPerfect does a long complex way to calc the menu rect
     * by calling this API. It calls GetMenuItemRect() with the app's
     * window.
     */
    if (pwnd == NULL || TestWF(pwnd, WFWIN50COMPAT)) {
        pwnd = GetMenuPwnd(pwnd, pMenu);
    }

    /*
     * If no pwnd, no go.
     * IMPORTANT: for MFISPOPUP we might get a different pwnd but we don't lock
     *   it because we won't call back
     */
    if (pwnd == NULL) {
        return FALSE;
    }

    if (TestMF(pMenu, MFISPOPUP)) {
        dx = pwnd->rcClient.left;
        dy = pwnd->rcClient.top;
    } else {
        xxxMNRecomputeBarIfNeeded(pwnd, pMenu);

        dx = pwnd->rcWindow.left;
        dy = pwnd->rcWindow.top;
    }

    if (uIndex >= pMenu->cItems)
        return(FALSE);

    pItem = pMenu->rgItems + uIndex;

    lprcScreen->right   = pItem->cxItem;
    lprcScreen->bottom  = pItem->cyItem;

    OffsetRect(lprcScreen, dx + pItem->xItem, dy + pItem->yItem);
    return(TRUE);
}