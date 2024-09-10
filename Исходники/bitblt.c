/*****************************************************************************
 * XGA DrvCopyBits
 ****************************************************************************/
BOOL DrvCopyBits(
SURFOBJ  *psoDest,
SURFOBJ  *psoSrc,
CLIPOBJ  *pco,
XLATEOBJ *pxlo,
RECTL    *prclDest,
POINTL   *pptlSrc)
{
BOOL    b;

CLIPOBJ coLocal;
SURFOBJ *pso;

        DISPDBG((2, "XGA.DLL: DrvCopyBits - Entry\n"));

        // Need to determine which surface is the display.
        // So we can pickup the address of the XGA coprocessor regs.

        if ((psoDest) && (psoDest->iType == STYPE_DEVICE))
            pso = psoDest;

        else if ((psoSrc) && (psoSrc->iType == STYPE_DEVICE))
            pso = psoSrc;

        else
        {
            RIP ("XGA.DLL!DrvCopyBits - neither surface is a device surface\n");
            return (TRUE);
        }

        // Wait for the coprocessor.

        vWaitForCoProcessor((PPDEV)pso->dhpdev, 100);

        // Protect this routine from a potentially NULL clip object

        if (pco == NULL)
        {
            coLocal.iDComplexity    = DC_RECT;

            coLocal.rclBounds.left   = 0;
            coLocal.rclBounds.top    = 0;
            coLocal.rclBounds.right  = ((PPDEV)pso->dhpdev)->cxScreen;
            coLocal.rclBounds.bottom = ((PPDEV)pso->dhpdev)->cyScreen;

            pco = &coLocal;

        }

        // Check for a Screen to Screen or a Host to Screen blit.

        b = FALSE;

        if ((psoDest->iType == STYPE_DEVICE) &&
            (psoSrc->iType == STYPE_DEVICE) &&
            (((PPDEV)psoDest->dhpdev)->ulfBlitAccelerations_debug & SCRN_TO_SCRN_CPY))
        {
            b = bScrnToScrnCpy(psoDest,
                               psoSrc,
                               NULL,
                               pco,
                               pxlo,
                               prclDest,
                               pptlSrc,
                               NULL,
                               NULL,
                               NULL,
                               0xcccc);
        }

        if (b == FALSE)
        {
            if ((psoDest) && (psoDest->iType == STYPE_DEVICE))
                psoDest = ((PPDEV)(psoDest->dhpdev))->pSurfObj;

            if ((psoSrc) && (psoSrc->iType == STYPE_DEVICE))
                psoSrc = ((PPDEV)(psoSrc->dhpdev))->pSurfObj;

            EngCopyBits(psoDest,
                        psoSrc,
                        pco,
                        pxlo,
                        prclDest,
                        pptlSrc);

        }

        return (TRUE);

}