ULONG
NTAPI
GreSetPointerShape(
    _In_ HDC hdc,
    _In_opt_ HBITMAP hbmMask,
    _In_opt_ HBITMAP hbmColor,
    _In_ LONG xHot,
    _In_ LONG yHot,
    _In_ LONG x,
    _In_ LONG y,
    _In_ FLONG fl)
{
    PDC pdc;
    PSURFACE psurf, psurfMask, psurfColor;
    EXLATEOBJ exlo;
    ULONG ulResult = 0;

    pdc = DC_LockDc(hdc);
    if (!pdc)
    {
        DPRINT1("Failed to lock the DC.\n");
        return 0;
    }

    ASSERT(pdc->dctype == DCTYPE_DIRECT);
    EngAcquireSemaphore(pdc->ppdev->hsemDevLock);
    /* We're not sure DC surface is the good one */
    psurf = pdc->ppdev->pSurface;
    if (!psurf)
    {
        DPRINT1("DC has no surface.\n");
        EngReleaseSemaphore(pdc->ppdev->hsemDevLock);
        DC_UnlockDc(pdc);
        return 0;
    }

    /* Lock the mask bitmap */
    if (hbmMask)
    {
        psurfMask = SURFACE_ShareLockSurface(hbmMask);
    }
    else
    {
        //ASSERT(fl & SPS_ALPHA);
        psurfMask = NULL;
    }

    /* Check for color bitmap */
    if (hbmColor)
    {
        /* We have one, lock it */
        psurfColor = SURFACE_ShareLockSurface(hbmColor);

        if (psurfColor)
        {
            /* Create an XLATEOBJ, no mono support */
            EXLATEOBJ_vInitialize(&exlo, psurfColor->ppal, psurf->ppal, 0, 0, 0);
        }
    }
    else
        psurfColor = NULL;

    /* We must have a valid surface in case of alpha bitmap */
    ASSERT(((fl & SPS_ALPHA) && psurfColor) || !(fl & SPS_ALPHA));

    /* Call the driver or eng function */
    ulResult = IntEngSetPointerShape(&psurf->SurfObj,
                                     psurfMask ? &psurfMask->SurfObj : NULL,
                                     psurfColor ? &psurfColor->SurfObj : NULL,
                                     psurfColor ? &exlo.xlo : NULL,
                                     xHot,
                                     yHot,
                                     x,
                                     y,
                                     &pdc->ppdev->Pointer.Exclude,
                                     fl | SPS_CHANGE);

    /* Cleanup */
    if (psurfColor)
    {
        EXLATEOBJ_vCleanup(&exlo);
        SURFACE_ShareUnlockSurface(psurfColor);
    }

    if (psurfMask)
        SURFACE_ShareUnlockSurface(psurfMask);

    EngReleaseSemaphore(pdc->ppdev->hsemDevLock);

    /* Unlock the DC */
    DC_UnlockDc(pdc);

    /* Return result */
    return ulResult;
}