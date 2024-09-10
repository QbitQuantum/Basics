BOOL APIENTRY
IntEngAlphaBlend(IN SURFOBJ *psoDest,
                 IN SURFOBJ *psoSource,
                 IN CLIPOBJ *ClipRegion,
                 IN XLATEOBJ *ColorTranslation,
                 IN PRECTL DestRect,
                 IN PRECTL SourceRect,
                 IN BLENDOBJ *BlendObj)
{
    BOOL ret = FALSE;
    SURFACE *psurfDest;
    SURFACE *psurfSource;

    ASSERT(psoDest);
    psurfDest = CONTAINING_RECORD(psoDest, SURFACE, SurfObj);

    ASSERT(psoSource);
    psurfSource = CONTAINING_RECORD(psoSource, SURFACE, SurfObj);

    ASSERT(DestRect);
    ASSERT(SourceRect);

    /* Check if there is anything to draw */
    if (ClipRegion != NULL &&
            (ClipRegion->rclBounds.left >= ClipRegion->rclBounds.right ||
             ClipRegion->rclBounds.top >= ClipRegion->rclBounds.bottom))
    {
        /* Nothing to do */
        return TRUE;
    }

    /* Call the driver's DrvAlphaBlend if available */
    if (psurfDest->flags & HOOK_ALPHABLEND)
    {
        ret = GDIDEVFUNCS(psoDest).AlphaBlend(
                  psoDest, psoSource, ClipRegion, ColorTranslation,
                  DestRect, SourceRect, BlendObj);
    }

    if (! ret)
    {
        ret = EngAlphaBlend(psoDest, psoSource, ClipRegion, ColorTranslation,
                            DestRect, SourceRect, BlendObj);
    }

    return ret;
}