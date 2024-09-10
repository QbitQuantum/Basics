BOOL bBufferExpansion(
PDEV*     ppdev,
STROBJ*   pstro,
CLIPOBJ*  pco,
RECTL*    prclExtra,
RECTL*    prclOpaque,
BRUSHOBJ* pboFore,
BRUSHOBJ* pboOpaque)
{
    BYTE            jClip;
    BOOL            bMore;              // Flag for clip enumeration
    GLYPHPOS*       pgp;                // Points to the first glyph
    BOOL            bMoreGlyphs;        // Glyph enumeration flag
    ULONG           cGlyph;             // # of glyphs in one batch
    RECTL           arclTmp[4];         // Temporary storage for portions
                                        //   of opaquing rectangle
    RECTL*          prclClip;           // Points to list of clip rectangles
    RECTL*          prclDraw;           // Actual text to be drawn
    RECTL           rclDraw;
    ULONG           crcl;               // Temporary rectangle count
    ULONG           ulBufferBytes;
    ULONG           ulBufferHeight;
    BOOL            bTextPerfectFit;
    ULONG           flDraw;
    BOOL            bTmpAlloc;
    SURFOBJ         so;
    CLIPENUM        ce;
    RBRUSH_COLOR    rbc;
    ULONG           ulHwBackMix;        // Dictates whether opaque or
                                        //   transparent text
    XLATEOBJ        xlo;                // Temporary for passing colours
    XLATECOLORS     xlc;                // Temporary for keeping colours

    jClip = (pco == NULL) ? DC_TRIVIAL : pco->iDComplexity;

    // The foreground colour will always be solid:

    xlc.iForeColor = pboFore->iSolidColor;

    ASSERTDD(xlc.iForeColor != -1, "Expected solid foreground colour");

    // See if the temporary buffer is big enough for the text; if
    // not, try to allocate enough memory.  We round up to the
    // nearest dword multiple:

    so.lDelta = ((((pstro->rclBkGround.right + 31) & ~31) -
                              (pstro->rclBkGround.left & ~31)) >> 3);

    ulBufferHeight = pstro->rclBkGround.bottom - pstro->rclBkGround.top;

    ulBufferBytes = so.lDelta * ulBufferHeight;

    if (((ULONG)so.lDelta > FIFTEEN_BITS) ||
        (ulBufferHeight > FIFTEEN_BITS))
    {
        // the math will have overflowed
        return(FALSE);
    }

    // Use our temporary buffer if it's big enough, otherwise
    // allocate a buffer on the fly:

    if (ulBufferBytes >= TMP_BUFFER_SIZE)
    {
        // The textout is so big that I doubt this allocation will
        // cost a significant amount in performance:

        bTmpAlloc  = TRUE;
        so.pvScan0 = EngAllocUserMem(ulBufferBytes, ALLOC_TAG);
        if (so.pvScan0 == NULL)
            return(FALSE);
    }
    else
    {
        bTmpAlloc  = FALSE;
        so.pvScan0 = ppdev->pvTmpBuffer;
    }

    // Set fixed pitch, overlap, and top and bottom 'y' alignment
    // flags:

    if (!(pstro->flAccel & SO_HORIZONTAL) ||
         (pstro->flAccel & SO_REVERSED))
    {
        flDraw = 0;
    }
    else
    {
        flDraw = ((pstro->ulCharInc != 0) ? 0x01 : 0) |
                     (((pstro->flAccel & (SO_ZERO_BEARINGS |
                      SO_FLAG_DEFAULT_PLACEMENT)) !=
                      (SO_ZERO_BEARINGS | SO_FLAG_DEFAULT_PLACEMENT))
                      ? 0x02 : 0) |
                     (((pstro->flAccel & (SO_ZERO_BEARINGS |
                      SO_FLAG_DEFAULT_PLACEMENT |
                      SO_MAXEXT_EQUAL_BM_SIDE)) ==
                      (SO_ZERO_BEARINGS | SO_FLAG_DEFAULT_PLACEMENT |
                      SO_MAXEXT_EQUAL_BM_SIDE)) ? 0x04 : 0);
    }

    // If there's an opaque rectangle, we'll do as much opaquing
    // as possible as we do the text.  If the opaque rectangle is
    // larger than the text rectangle, then we'll do the fringe
    // areas right now, and the text and associated background
    // areas together later:

    ulHwBackMix = LEAVE_ALONE;
    if (prclOpaque != NULL)
    {
        ulHwBackMix = OVERPAINT;

        // Since we didn't set GCAPS_ARBRUSHOPAQUE (yes, it's
        // missing a 'b'), we don't have to worry about getting
        // anything other that a solid opaquing brush.  I wouldn't
        // recommend handling it anyway, since I'll bet it would
        // break quite a few applications:

        xlc.iBackColor = pboOpaque->iSolidColor;

        ASSERTDD(xlc.iBackColor != -1, "Expected solid background colour");

        // See if we have fringe areas to do.  If so, build a list of
        // rectangles to fill, in right-down order:

        crcl = 0;

        // Top fragment:

        if (pstro->rclBkGround.top > prclOpaque->top)
        {
            arclTmp[crcl].top      = prclOpaque->top;
            arclTmp[crcl].left     = prclOpaque->left;
            arclTmp[crcl].right    = prclOpaque->right;
            arclTmp[crcl++].bottom = pstro->rclBkGround.top;
        }

        // Left fragment:

        if (pstro->rclBkGround.left > prclOpaque->left)
        {
            arclTmp[crcl].top      = pstro->rclBkGround.top;
            arclTmp[crcl].left     = prclOpaque->left;
            arclTmp[crcl].right    = pstro->rclBkGround.left;
            arclTmp[crcl++].bottom = pstro->rclBkGround.bottom;
        }

        // Right fragment:

        if (pstro->rclBkGround.right < prclOpaque->right)
        {
            arclTmp[crcl].top      = pstro->rclBkGround.top;
            arclTmp[crcl].right    = prclOpaque->right;
            arclTmp[crcl].left     = pstro->rclBkGround.right;
            arclTmp[crcl++].bottom = pstro->rclBkGround.bottom;
        }

        // Bottom fragment:

        if (pstro->rclBkGround.bottom < prclOpaque->bottom)
        {
            arclTmp[crcl].bottom = prclOpaque->bottom;
            arclTmp[crcl].left   = prclOpaque->left;
            arclTmp[crcl].right  = prclOpaque->right;
            arclTmp[crcl++].top  = pstro->rclBkGround.bottom;
        }

        // Fill any fringe rectangles we found:

        if (crcl != 0)
        {
            if (jClip == DC_TRIVIAL)
            {
                rbc.iSolidColor = xlc.iBackColor;
                (ppdev->pfnFillSolid)(ppdev, crcl, arclTmp, OVERPAINT,
                                      OVERPAINT, rbc, NULL);
            }
            else
            {
                vClipSolid(ppdev, crcl, arclTmp, xlc.iBackColor, pco);
            }
        }
    }

    // We're done with separate opaquing; any further opaquing will
    // happen as part of the text drawing.

    // Clear the buffer if the text isn't going to set every bit:

    bTextPerfectFit = (pstro->flAccel & (SO_ZERO_BEARINGS |
            SO_FLAG_DEFAULT_PLACEMENT | SO_MAXEXT_EQUAL_BM_SIDE |
            SO_CHAR_INC_EQUAL_BM_BASE)) ==
            (SO_ZERO_BEARINGS | SO_FLAG_DEFAULT_PLACEMENT |
            SO_MAXEXT_EQUAL_BM_SIDE | SO_CHAR_INC_EQUAL_BM_BASE);

    if (!bTextPerfectFit)
    {
        // Note that we already rounded up to a dword multiple size.

        vClearMemDword((ULONG*) so.pvScan0, ulBufferBytes >> 2);
    }