HBITMAP APIENTRY VBoxDispDrvDeriveSurface(DD_DIRECTDRAW_GLOBAL *pDirectDraw, DD_SURFACE_LOCAL *pSurface)
{
    PVBOXDISPDEV pDev = (PVBOXDISPDEV)pDirectDraw->dhpdev;
    LOGF_ENTER();

    if (pSurface->ddsCaps.dwCaps & DDSCAPS_NONLOCALVIDMEM)
    {
        WARN(("Can't derive surface DDSCAPS_NONLOCALVIDMEM"));
        return NULL;
    }

    if (pSurface->lpSurfMore->ddsCapsEx.dwCaps2 & DDSCAPS2_TEXTUREMANAGE)
    {
        WARN(("Can't derive surface DDSCAPS2_TEXTUREMANAGE"));
        return NULL;
    }

    if (pSurface->lpGbl->ddpfSurface.dwRGBBitCount != pDev->mode.ulBitsPerPel)
    {
        WARN(("Can't derive surface with different bpp"));
        return NULL;
    }

    Assert(pDev->surface.hSurface);

    /* Create GDI managed bitmap, which resides in our DDraw heap memory */
    HBITMAP hBitmap;
    SIZEL size;

    size.cx = pDev->mode.ulWidth;
    size.cy = pDev->mode.ulHeight;

    hBitmap = EngCreateBitmap(size, pSurface->lpGbl->lPitch, pDev->surface.ulFormat,
                              pDev->mode.lScanlineStride>0 ? BMF_TOPDOWN:0,
                              (PBYTE)pDev->memInfo.VideoRamBase + pSurface->lpGbl->fpVidMem);

    if (!hBitmap)
    {
        WARN(("EngCreateBitmap failed"));
        return 0;
    }

    if (pSurface->lpGbl->fpVidMem == 0)
    {
        /* Screen surface, mark it so it will be recognized by the driver.
         * so the driver will be called on any operations on the surface
         * (required for VBVA and VRDP).
         */
        SURFOBJ *pso;

        if (!EngAssociateSurface((HSURF)hBitmap, pDev->hDevGDI, pDev->flDrawingHooks))
        {
            WARN(("EngAssociateSurface failed"));
            EngDeleteSurface((HSURF)hBitmap);
            return NULL;
        }

        pso = EngLockSurface((HSURF)hBitmap);
        if (!pso)
        {
            WARN(("EngLockSurface failed"));
            EngDeleteSurface((HSURF)hBitmap);
            return NULL;
        }

        pso->dhpdev = (DHPDEV)pDev;
        EngUnlockSurface(pso);
    }

    LOGF_LEAVE();
    return hBitmap;
}