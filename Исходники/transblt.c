BOOL
FASTCALL
IntEngTransparentBlt(
    SURFOBJ *psoDest,
    SURFOBJ *psoSource,
    CLIPOBJ *Clip,
    XLATEOBJ *ColorTranslation,
    PRECTL DestRect,
    PRECTL SourceRect,
    ULONG iTransColor,
    ULONG Reserved)
{
    BOOL Ret;
    RECTL OutputRect, InputClippedRect;
    SURFACE *psurfDest;
    SURFACE *psurfSource;
    RECTL InputRect;
    LONG InputClWidth, InputClHeight, InputWidth, InputHeight;

    ASSERT(psoDest);
    ASSERT(psoSource);
    ASSERT(DestRect);

    psurfDest = CONTAINING_RECORD(psoDest, SURFACE, SurfObj);
    psurfSource = CONTAINING_RECORD(psoSource, SURFACE, SurfObj);

    ASSERT(psurfDest);
    ASSERT(psurfSource);

    /* If no clip object is given, use trivial one */
    if (!Clip) Clip = &gxcoTrivial.ClipObj;

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

    InputRect = *SourceRect;
    /* Clip against the bounds of the clipping region so we won't try to write
     * outside the surface */
    if (Clip->iDComplexity != DC_TRIVIAL)
    {
        if (!RECTL_bIntersectRect(&OutputRect, &InputClippedRect, &Clip->rclBounds))
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

    if (psurfDest->flags & HOOK_TRANSPARENTBLT)
    {
        Ret = GDIDEVFUNCS(psoDest).TransparentBlt(psoDest,
                                                  psoSource,
                                                  Clip,
                                                  ColorTranslation,
                                                  &OutputRect,
                                                  &InputRect,
                                                  iTransColor,
                                                  Reserved);
    }
    else
        Ret = FALSE;

    if (!Ret)
    {
        Ret = EngTransparentBlt(psoDest,
                                psoSource,
                                Clip,
                                ColorTranslation,
                                &OutputRect,
                                &InputRect,
                                iTransColor,
                                Reserved);
    }

    return Ret;
}