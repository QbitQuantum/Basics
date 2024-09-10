static Bool
winActivateAppPrimaryDD(ScreenPtr pScreen)
{
    winScreenPriv(pScreen);
    RECT rcSrc, rcClient;
    HRESULT ddrval = DD_OK;

    /* Check for errors */
    if (pScreenPriv == NULL
        || pScreenPriv->pScreenInfo == NULL
        || pScreenPriv->pddsPrimary == NULL
        || pScreenPriv->pddsOffscreen == NULL)
        return FALSE;

    /* Check for do-nothing */
    if (!pScreenPriv->fActive)
        return TRUE;

    /* We are activating */
    ddrval = IDirectDrawSurface2_IsLost(pScreenPriv->pddsOffscreen);
    if (ddrval == DD_OK) {
        IDirectDrawSurface2_Unlock(pScreenPriv->pddsOffscreen, NULL);
        /*
         * We don't check for an error from Unlock, because it
         * doesn't matter if the Unlock failed.
         */
    }

    /* Restore both surfaces, just cause I like it that way */
    IDirectDrawSurface2_Restore(pScreenPriv->pddsOffscreen);
    IDirectDrawSurface2_Restore(pScreenPriv->pddsPrimary);

    /* Get client area in screen coords */
    GetClientRect(pScreenPriv->hwndScreen, &rcClient);
    MapWindowPoints(pScreenPriv->hwndScreen,
                    HWND_DESKTOP, (LPPOINT) &rcClient, 2);

    /* Setup a source rectangle */
    rcSrc.left = 0;
    rcSrc.top = 0;
    rcSrc.right = pScreenPriv->pScreenInfo->dwWidth;
    rcSrc.bottom = pScreenPriv->pScreenInfo->dwHeight;

    ddrval = IDirectDrawSurface2_Blt(pScreenPriv->pddsPrimary,
                                     &rcClient,
                                     pScreenPriv->pddsOffscreen,
                                     &rcSrc, DDBLT_WAIT, NULL);
    if (ddrval != DD_OK)
        FatalError("winActivateAppPrimaryDD () - Failed blitting offscreen "
                   "surface to primary surface %08x\n", (unsigned int) ddrval);

    /* Lock the primary surface */
    ddrval = IDirectDrawSurface2_Lock(pScreenPriv->pddsPrimary,
                                      &rcClient,
                                      pScreenPriv->pddsdPrimary,
                                      DDLOCK_WAIT, NULL);
    if (ddrval != DD_OK || pScreenPriv->pddsdPrimary->lpSurface == NULL)
        FatalError("winActivateAppPrimaryDD () - Could not lock "
                   "primary surface\n");

    /* Notify FB of the new memory pointer */
    winUpdateFBPointer(pScreen, pScreenPriv->pddsdPrimary->lpSurface);

    /*
     * Register the Alt-Tab combo as a hotkey so we can copy
     * the primary framebuffer before the display mode changes
     */
    RegisterHotKey(pScreenPriv->hwndScreen, 1, MOD_ALT, 9);

    return TRUE;
}