BOOL vrdpDrvRealizeBrush(BRUSHOBJ *pbo, SURFOBJ *psoTarget, SURFOBJ *psoPattern, SURFOBJ *psoMask,
                        XLATEOBJ *pxlo, ULONG iHatch)
{
    BOOL bRc = FALSE;

    LOGF(("psoMask = %p, iHatch = %d", psoMask, iHatch));
    VBoxDispDumpPSO(psoPattern, "psoPattern");

    if (psoPattern
        && psoPattern->sizlBitmap.cx == 8
        && psoPattern->sizlBitmap.cy == 8
        && psoPattern->iBitmapFormat == 1
       )
    {
        uint32_t cbBrush = sizeof (VRDPBRUSH);

        VRDPBRUSH *pBrush = (VRDPBRUSH *)BRUSHOBJ_pvAllocRbrush (pbo, cbBrush);

        LOG(("pattern pBrush = %p, size = %d", pBrush, cbBrush));

        if (pBrush)
        {
            int i;
            uint8_t *pu8Bits = (uint8_t *)psoPattern->pvScan0;

            for (i = 0; i < 8; i++)
            {
                pBrush->u.pat.au8Pattern[i] = *pu8Bits;

                pu8Bits += psoPattern->lDelta;
            }

            /* Obtain RGB values for the brush fore and background colors:
             * "should translate color zero through the XLATEOBJ to get the foreground color for the brush."
             */
            pBrush->u.pat.rgbFG = vrdpColor2RGB (psoTarget, pxlo->pulXlate[0]);
            pBrush->u.pat.rgbBG = vrdpColor2RGB (psoTarget, pxlo->pulXlate[1]);

            pBrush->fPattern = TRUE;

            bRc = TRUE;
        }
    }
#if 0
    else if (psoPattern)
    {
        /* Color brushes and brushes >8x8 are cached and MEMBLT order generated. */
        uint32_t cbBrush = sizeof (VRDPBRUSH) +
                           psoTarget->sizlBitmap.cx * sizeof (uint32_t) * psoTarget->sizlBitmap.cy;
                           ??? target

        VRDPBRUSH *pBrush = (VRDPBRUSH *)BRUSHOBJ_pvAllocRbrush (pbo, cbBrush);

        LOG(("bitmap pBrush = %p, size = %d", pBrush, cbBrush));

        if (pBrush)
        {
            /* Byte per pattern pixel. */
            uint32_t cbSrcBPP = format2BytesPerPixel(psoPattern);

            /* Source bits scanline pointer. */
            uint8_t  *pu8BitsSrcScanLine = (uint8_t *)psoPattern->pvScan0;

            /* Target RGB pixel pointer. */
            uint32_t *pu32BitsDst = &pBrush->u.bitmap.au32Bits[0];

            int y;
            for (y = 0; y < psoTarget->sizlBitmap.cy; y++, pu8BitsSrcScanLine += psoPattern->lDelta)
            {
                uint8_t *pu8BitsSrc = pu8BitsSrcScanLine;

                int x;

                for (x = 0; x < psoTarget->sizlBitmap.cx; x++, pu8BitsSrc += cbSrcBPP)
                {
                    uint32_t color = 0;

                    memcpy (&color, pu8BitsSrc, cbSrcBPP);

                    if (pxlo)
                    {
                        color = XLATEOBJ_iXlate (pxlo, color);
                    }

                    *pu32BitsDst++ = vrdpColor2RGB (psoTarget, color);

                    /* LOG(("%08X", pu32BitsDst[-1])); */
                }
            }

            pBrush->u.bitmap.w = (uint16_t)psoTarget->sizlBitmap.cx;
            pBrush->u.bitmap.h = (uint16_t)psoTarget->sizlBitmap.cy;

            pBrush->fPattern = FALSE;

            bRc = TRUE;
        }
    }