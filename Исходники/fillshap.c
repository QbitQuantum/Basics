BOOL APIENTRY
NtGdiExtFloodFill(
    HDC  hDC,
    INT  XStart,
    INT  YStart,
    COLORREF  Color,
    UINT  FillType)
{
    PDC dc;
#if 0
    PDC_ATTR   pdcattr;
#endif
    SURFACE    *psurf;
    EXLATEOBJ  exlo;
    BOOL       Ret = FALSE;
    RECTL      DestRect;
    POINTL     Pt;
    ULONG      ConvColor;

    dc = DC_LockDc(hDC);
    if (!dc)
    {
        EngSetLastError(ERROR_INVALID_HANDLE);
        return FALSE;
    }
    if (dc->dctype == DC_TYPE_INFO)
    {
        DC_UnlockDc(dc);
        /* Yes, Windows really returns TRUE in this case */
        return TRUE;
    }

    if (!dc->dclevel.pSurface)
    {
        Ret = FALSE;
        goto cleanup;
    }

#if 0
    pdcattr = dc->pdcattr;
#endif

    Pt.x = XStart;
    Pt.y = YStart;
    IntLPtoDP(dc, (LPPOINT)&Pt, 1);

    DC_vPrepareDCsForBlit(dc, &DestRect, NULL, NULL);

    /// FIXME: what about prgnVIS? And what about REAL clipping?
    psurf = dc->dclevel.pSurface;
    if (dc->prgnRao)
    {
        Ret = REGION_PtInRegion(dc->prgnRao, Pt.x, Pt.y);
        if (Ret)
            REGION_GetRgnBox(dc->prgnRao, (LPRECT)&DestRect);
        else
        {
            DC_vFinishBlit(dc, NULL);
            goto cleanup;
        }
    }
    else
    {
        RECTL_vSetRect(&DestRect, 0, 0, psurf->SurfObj.sizlBitmap.cx, psurf->SurfObj.sizlBitmap.cy);
    }

    EXLATEOBJ_vInitialize(&exlo, &gpalRGB, psurf->ppal, 0, 0xffffff, 0);

    /* Only solid fills supported for now
     * How to support pattern brushes and non standard surfaces (not offering dib functions):
     * Version a (most likely slow): call DrvPatBlt for every pixel
     * Version b: create a flood mask and let MaskBlt blit a masked brush */
    ConvColor = XLATEOBJ_iXlate(&exlo.xlo, Color);
    Ret = DIB_XXBPP_FloodFillSolid(&psurf->SurfObj, &dc->eboFill.BrushObject, &DestRect, &Pt, ConvColor, FillType);

    DC_vFinishBlit(dc, NULL);

    EXLATEOBJ_vCleanup(&exlo);

cleanup:
    DC_UnlockDc(dc);
    return Ret;
}