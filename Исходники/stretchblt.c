BOOL APIENTRY
IntEngStretchBlt(SURFOBJ *psoDest,
                 SURFOBJ *psoSource,
                 SURFOBJ *MaskSurf,
                 CLIPOBJ *ClipRegion,
                 XLATEOBJ *ColorTranslation,
                 COLORADJUSTMENT *pca,
                 RECTL *DestRect,
                 RECTL *SourceRect,
                 POINTL *pMaskOrigin,
                 BRUSHOBJ *pbo,
                 POINTL *BrushOrigin,
                 DWORD Rop4)
{
    BOOLEAN ret;
    POINTL MaskOrigin = {0, 0};
    SURFACE *psurfDest;
    //SURFACE *psurfSource = NULL;
    RECTL InputClippedRect;
    RECTL InputRect;
    RECTL OutputRect;
    BOOL UsesSource = ROP4_USES_SOURCE(Rop4);
    LONG InputClWidth, InputClHeight, InputWidth, InputHeight;

    ASSERT(psoDest);
    //ASSERT(psoSource); // FIXME!
    ASSERT(DestRect);
    //ASSERT(SourceRect); // FIXME!
    //ASSERT(!RECTL_bIsEmptyRect(SourceRect)); // FIXME!

    /* If no clip object is given, use trivial one */
    if (!ClipRegion) ClipRegion = &gxcoTrivial.ClipObj;

    psurfDest = CONTAINING_RECORD(psoDest, SURFACE, SurfObj);

    /* Sanity check */
    ASSERT(IS_VALID_ROP4(Rop4));

    /* Check if source and dest size are equal */
    if (((DestRect->right - DestRect->left) == (SourceRect->right - SourceRect->left)) &&
        ((DestRect->bottom - DestRect->top) == (SourceRect->bottom - SourceRect->top)))
    {
        /* Pass the request to IntEngBitBlt */
        return IntEngBitBlt(psoDest,
                            psoSource,
                            MaskSurf,
                            ClipRegion,
                            ColorTranslation,
                            DestRect,
                            (PPOINTL)SourceRect,
                            pMaskOrigin,
                            pbo,
                            BrushOrigin,
                            Rop4);
    }

    InputClippedRect = *DestRect;
    if (InputClippedRect.right < InputClippedRect.left)
    {
        InputClippedRect.left = DestRect->right;
        InputClippedRect.right = DestRect->left;
    }
    if (InputClippedRect.bottom < InputClippedRect.top)
    {
        InputClippedRect.top = DestRect->bottom;
        InputClippedRect.bottom = DestRect->top;
    }

    if (NULL == SourceRect || NULL == psoSource)
    {
        return FALSE;
    }
    InputRect = *SourceRect;

    if (InputRect.right < InputRect.left ||
            InputRect.bottom < InputRect.top)
    {
        /* Everything clipped away, nothing to do */
        return TRUE;
    }

    if (ClipRegion->iDComplexity != DC_TRIVIAL)
    {
        if (!RECTL_bIntersectRect(&OutputRect, &InputClippedRect,
                               &ClipRegion->rclBounds))
        {
            return TRUE;
        }
        /* Update source rect */
        InputClWidth = InputClippedRect.right - InputClippedRect.left;
        InputClHeight = InputClippedRect.bottom - InputClippedRect.top;
        InputWidth = InputRect.right - InputRect.left;
        InputHeight = InputRect.bottom - InputRect.top;

        InputRect.left += (InputWidth * (OutputRect.left - InputClippedRect.left)) / InputClWidth;
        InputRect.right -= (InputWidth * (InputClippedRect.right - OutputRect.right)) / InputClWidth;
        InputRect.top += (InputHeight * (OutputRect.top - InputClippedRect.top)) / InputClHeight;
        InputRect.bottom -= (InputHeight * (InputClippedRect.bottom - OutputRect.bottom)) / InputClHeight;
    }
    else
    {
        OutputRect = InputClippedRect;
    }

    if (pMaskOrigin != NULL)
    {
        MaskOrigin.x = pMaskOrigin->x;
        MaskOrigin.y = pMaskOrigin->y;
    }

    /* No success yet */
    ret = FALSE;

    if (UsesSource)
    {
        //psurfSource = CONTAINING_RECORD(psoSource, SURFACE, SurfObj);
    }

    /* Call the driver's DrvStretchBlt if available */
    if (psurfDest->flags & HOOK_STRETCHBLTROP)
    {
        /* Drv->StretchBltROP (look at http://www.osronline.com/ddkx/graphics/ddifncs_0z3b.htm ) */
        ret = GDIDEVFUNCS(psoDest).StretchBltROP(psoDest,
                                                 psoSource,
                                                 MaskSurf,
                                                 ClipRegion,
                                                 ColorTranslation,
                                                 pca,
                                                 BrushOrigin,
                                                 &OutputRect,
                                                 &InputRect,
                                                 &MaskOrigin,
                                                 COLORONCOLOR,
                                                 pbo,
                                                 Rop4);
    }

    if (! ret)
    {
        ret = EngStretchBltROP(psoDest,
                               psoSource,
                               MaskSurf,
                               ClipRegion,
                               ColorTranslation,
                               pca,
                               BrushOrigin,
                               &OutputRect,
                               &InputRect,
                               &MaskOrigin,
                               COLORONCOLOR,
                               pbo,
                               Rop4);
    }

    return ret;
}