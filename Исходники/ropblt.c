BOOL
DoMix2(
    PPDEV       pPDev,
    SURFOBJ     *psoDst,
    SURFOBJ     *psoSrc,
    CLIPOBJ     *pco,
    XLATEOBJ    *pxlo,
    PRECTL      prclDst,
    PRECTL      prclSrc,
    PPOINTL     pptlSrcOrg,
    DWORD       Mix2
    )

/*++

Routine Description:

    This function is responsible for doing a device copy of a bitmap
    with/without tiling and activating the proper Rop2

Arguments:

    pPDev       - Pointer to the PDEV

    psoDst      - pointer to the destination surface object

    psoSrc      - pointer to the source surface object

    pco         - Pointer to the CLIPOBJ

    pxlo        - the translate object from the source to the destination

    prclDst     - the output destination rectangle area

    prclSrc     - the source rectangle area

    pptlSrcOrg  - brush origin for the source rectangle, if this is NULL then
                  prclSrc will not have to be aligned on the destination

    Mix2        - a rop2 mode 0 - 0x0F

Return Value:

    BOOLEAN

Author:

    08-Feb-1994 Tue 16:33:41 updated  
        fixed ptlSrcOrg problem, we need to modulate with source size before
        it get used.

    27-Jan-1994 Thu 23:45:46 updated  
        Re-write so that it can handle the tiling more efficient.

    13-Jan-1994 Sat 09:34:06 created  

Revision History:


--*/
{
    RECTL       rclSrc;
    RECTL       rclDst;
    POINTL      ptlSrcOrg;
    LONG        cxSrc;
    LONG        cySrc;
    DWORD       OHTFlags = 0;
    BOOL        MemMix2;


    //
    // The final ROP is either a ROP3 or a ROP4 (no mask) and it is always
    // a rop2 operation which deals with the source and destination
    //
    // First make it into a Rop3 representation of Rop2 (Mix2)
    //

    PLOTASSERT(1, "DoMix2: Passed INVALID psoSrc (%08lx) = STYPE_DEVICE",
                    (psoSrc) &&
                    (psoSrc->iType != STYPE_DEVICE), psoSrc);

    PLOTASSERT(1, "DoMix2: Unexpected Mix2 = %u, SHOULD NOT BE HERE",
                (Mix2 != MIX2_0) && (Mix2 != MIX2_1) &&
                (Mix2 != MIX2_D) && (Mix2 != MIX2_nD), Mix2);

    Mix2 &= 0x0F;
    Mix2 |= (DWORD)(Mix2 << 4);

    switch (Mix2) {

    case 0x00:  // 0
    case 0xFF:  // 1
    case 0x55:  // ~D

        DoSpecialRop3(psoDst, pco, prclDst, Mix2);

    case 0xAA:  // D

        return(TRUE);
    }

    if (MemMix2 = (BOOL)(psoDst->iType != STYPE_DEVICE)) {

        //
        // Now make it into Rop4 representation of Rop2 (Mix2)
        //

        Mix2 |= (Mix2 << 8);

    } else {

        if (!IsHTCompatibleSurfObj(pPDev,
                                   psoSrc,
                                   pxlo,
                                   ((pxlo) ? ISHTF_ALTFMT : 0)  |
                                        ISHTF_HTXB              |
                                        ISHTF_DSTPRIM_OK)) {

            PLOTERR(("DoMix2: The psoSrc is not HT compatible format (%08lx",
                                    psoSrc->iBitmapFormat));
            return(FALSE);
        }
    }

    cxSrc = prclSrc->right - prclSrc->left;
    cySrc = prclSrc->bottom - prclSrc->top;

    if (pptlSrcOrg) {

        ptlSrcOrg = *pptlSrcOrg;

        if ((ptlSrcOrg.x = (LONG)(prclDst->left - ptlSrcOrg.x) % cxSrc) < 0) {

            ptlSrcOrg.x += cxSrc;
        }

        if ((ptlSrcOrg.y = (LONG)(prclDst->top - ptlSrcOrg.y) % cySrc) < 0) {

            ptlSrcOrg.y += cySrc;
        }

        PLOTDBG(DBG_DOMIX2, ("DoMix2: ORG ptlSrcOrg=(%ld, %ld) -> (%ld, %ld)",
                    pptlSrcOrg->x, pptlSrcOrg->y, ptlSrcOrg.x, ptlSrcOrg.y));

    } else {

        ptlSrcOrg.x =
        ptlSrcOrg.y = 0;

        PLOTDBG(DBG_DOMIX2, ("DoMix2: >>> DO NOT NEED TO ALIGN SRC on DEST <<<"));
    }

    rclSrc.top    = prclSrc->top + ptlSrcOrg.y;
    rclSrc.bottom = prclSrc->bottom;
    rclDst.top    = prclDst->top;
    rclDst.bottom = rclDst.top + (rclSrc.bottom - rclSrc.top);

    PLOTDBG(DBG_DOMIX2, ("DoMix2: SrcFormat=%ld, DstFormat=%ld %hs",
                psoSrc->iBitmapFormat,
                psoDst->iBitmapFormat,
                (MemMix2) ? "[MemMix2]" : ""));

    PLOTDBG(DBG_DOMIX2, ("DoMix2: ORG: Dst=(%ld, %ld)-(%ld,%ld), Src=(%ld, %ld)-(%ld, %ld)",
                prclDst->left, prclDst->top,
                prclDst->right, prclDst->bottom,
                prclSrc->left, prclSrc->top,
                prclSrc->right, prclSrc->bottom));

    while (rclDst.top < prclDst->bottom) {

        //
        // check if the destination bottom is overhanging, clip it,
        //
        // NOTE: This could happen the first time.
        //

        if (rclDst.bottom > prclDst->bottom) {

            //
            // Clip the source/destination rectangle, because we may do
            // EngBitBlt() or OutputHTBitmap()
            //

            rclSrc.bottom -= (rclDst.bottom - prclDst->bottom);
            rclDst.bottom  = prclDst->bottom;
        }

        rclSrc.left  = prclSrc->left + ptlSrcOrg.x;
        rclSrc.right = prclSrc->right;
        rclDst.left  = prclDst->left;
        rclDst.right = rclDst.left + (rclSrc.right - rclSrc.left);

        while (rclDst.left < prclDst->right) {

            //
            // check if the destination right edge is overhanging, clip it if
            // necessary.
            //
            // NOTE: This could happen the first time.
            //

            if (rclDst.right > prclDst->right) {

                //
                // Clip the source/destination rectangle, because we may do a
                // EngBitBlt() or OutputHTBitmap()
                //

                rclSrc.right -= (rclDst.right - prclDst->right);
                rclDst.right  = prclDst->right;
            }

            PLOTDBG(DBG_DOMIX2, ("DoMix2: TILE: Dst=(%ld, %ld)-(%ld,%ld), Src=(%ld, %ld)-(%ld, %ld)",
                        rclDst.left, rclDst.top, rclDst.right, rclDst.bottom,
                        rclSrc.left, rclSrc.top, rclSrc.right, rclSrc.bottom));

            if (MemMix2) {

                //
                // In the memory version we don't have to worry about PCO so
                // just call EngBitBlt to do the work.
                //

                if (!(EngBitBlt(psoDst,                     // psoDst
                                psoSrc,                     // psoSrc
                                NULL,                       // psoMask
                                pco,                        // pco
                                NULL,                       // pxlo
                                &rclDst,                    // prclDst
                                (PPOINTL)&rclSrc,           // pptlSrc
                                NULL,                       // pptlMask
                                NULL,                       // pbo
                                (PPOINTL)&ptlZeroOrigin,    // pptlBrushOrg
                                Mix2))) {

                    PLOTERR(("DoMix2: EngBitBlt(MemMix2=%04lx) Failed!!!",Mix2));
                    return(FALSE);
                }

            } else {

                if (!OutputHTBitmap(pPDev,
                                    psoSrc,
                                    pco,
                                    (PPOINTL)&rclDst,
                                    &rclSrc,
                                    Mix2,
                                    &OHTFlags)) {

                    PLOTERR(("DoMix2: OutputHTBitmap() Failed!!!"));
                    return(FALSE);
                }
            }

            //
            // Reset <source left> to the original left margin and move the
            // destination right to the left for the next destination RECTL.
            //

            rclSrc.left   = prclSrc->left;
            rclDst.left   = rclDst.right;
            rclDst.right += cxSrc;
        }

        //
        // Reset <source top> to the original top margin and move the
        // destination bottom to the top, and set bottom for the next destination
        // RECTL.
        //

        rclSrc.top     = prclSrc->top;
        rclDst.top     = rclDst.bottom;
        rclDst.bottom += cySrc;
    }

    if (OHTFlags & OHTF_MASK) {

        OHTFlags |= OHTF_EXIT_TO_HPGL2;

        OutputHTBitmap(pPDev, psoSrc, NULL, NULL, NULL, 0xAA, &OHTFlags);
    }

    return(TRUE);
}