BOOL vrdpReportText(PVBOXDISPDEV pDev, VRDPCLIPRECTS *pClipRects, STROBJ *pstro, FONTOBJ *pfo,
                    RECTL *prclOpaque, ULONG ulForeRGB, ULONG ulBackRGB)
{
    FONTINFO fi;
    uint32_t cbOrderMax;
    VRDEORDERTEXT *pOrder;
    BOOL fResult;
    uint8_t *pu8GlyphPtr;
    uint8_t *pu8GlyphEnd;

    LOGF(("pDev %p, pClipRects %p, pstro %p, pfo %p, prclOpaque %p, ulForeRGB %x, ulBackRGB %x",
          pDev, pClipRects, pstro, pfo, prclOpaque, ulForeRGB, ulBackRGB));

    if (pstro->ulCharInc > 0xFF)
    {
        return FALSE;
    }

    /* The driver can get vertical strings with both SO_HORIZONTAL and SO_VERTICAL bits equal to zero. */
    if (   (pstro->flAccel & SO_HORIZONTAL) == 0
        || (pstro->flAccel & SO_REVERSED) != 0)
    {
        /* Do not support (yet) the vertical and right to left strings.
         * @todo implement and test.
         */
        return FALSE;
    }

    memset (&fi, 0, sizeof (fi));

    FONTOBJ_vGetInfo (pfo, sizeof (fi), &fi);

    if (   fi.cjMaxGlyph1 == 0
        || fi.cjMaxGlyph1 > VRDP_TEXT_MAX_GLYPH_SIZE)
    {
        /* No 1BPP bitmaps or the bitmap is larger than the cache supports. */
        LOG(("fi.cjMaxGlyph1 = %x. Return FALSE", fi.cjMaxGlyph1));
        return FALSE;
    }

    cbOrderMax = vrdpSizeofTextOrder(pstro->cGlyphs, fi.cjMaxGlyph1);

    LOG(("pstro->cGlyphs = %d, fi.cjMaxGlyph1 = 0x%x, cbOrderMax = 0x%x.", pstro->cGlyphs, fi.cjMaxGlyph1, cbOrderMax));

    pOrder = (VRDEORDERTEXT *)EngAllocMem(0, cbOrderMax, MEM_ALLOC_TAG);

    if (!pOrder)
    {
        LOG(("pOrder = %x. Return FALSE", pOrder));
        return FALSE;
    }

    pu8GlyphPtr = (uint8_t *)&pOrder[1]; /* Follows the order header. */
    pu8GlyphEnd = (uint8_t *)pOrder + cbOrderMax;

    pOrder->xBkGround = (int16_t)pstro->rclBkGround.left;
    pOrder->yBkGround = (int16_t)pstro->rclBkGround.top;
    pOrder->wBkGround = (uint16_t)(pstro->rclBkGround.right - pstro->rclBkGround.left);
    pOrder->hBkGround = (uint16_t)(pstro->rclBkGround.bottom - pstro->rclBkGround.top);

    if (prclOpaque)
    {
        pOrder->xOpaque = (int16_t)prclOpaque->left;
        pOrder->yOpaque = (int16_t)prclOpaque->top;
        pOrder->wOpaque = (uint16_t)(prclOpaque->right - prclOpaque->left);
        pOrder->hOpaque = (uint16_t)(prclOpaque->bottom - prclOpaque->top);
    }
    else
    {
        pOrder->xOpaque = 0;
        pOrder->yOpaque = 0;
        pOrder->wOpaque = 0;
        pOrder->hOpaque = 0;
    }

    pOrder->u16MaxGlyph = (uint16_t)fi.cjMaxGlyph1;

    pOrder->u8Glyphs = (uint8_t)pstro->cGlyphs;

    pOrder->u8Flags = (uint8_t)pstro->flAccel;

    pOrder->u8CharInc = (uint8_t)pstro->ulCharInc;

    pOrder->u32FgRGB = ulForeRGB;
    pOrder->u32BgRGB = ulBackRGB;

    LOG(("pstro->pgp %p.", pstro->pgp));

    /* Enumerate glyphs. */
    STROBJ_vEnumStart(pstro);

    fResult = TRUE;

    for (;;)
    {
        ULONG i;
        ULONG cGlyphs = 0;
        GLYPHPOS *pGlyphPos = NULL;

        BOOL fMore = STROBJ_bEnum (pstro, &cGlyphs, &pGlyphPos);

        LOG(("cGlyphs %d.", cGlyphs));

        for (i = 0; i < cGlyphs; i++)
        {
            fResult = vrdpReportGlyph(&pGlyphPos[i], &pu8GlyphPtr, pu8GlyphEnd);

            if (!fResult)
            {
                break;
            }
        }

        if (!fMore || !fResult)
        {
            break;
        }
    }

    LOG(("fResult %d", fResult));

    if (fResult)
    {
        pOrder->cbOrder = (uint32_t)(pu8GlyphPtr - (uint8_t *)pOrder);

        vrdpReportOrderGeneric(pDev, pClipRects, pOrder, pOrder->cbOrder, VRDE_ORDER_TEXT);
    }

    EngFreeMem(pOrder);

    return fResult;
}