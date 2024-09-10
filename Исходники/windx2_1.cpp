void update_screen() {
    IDirectDrawSurface *dst;
    RECT dstRect;
    RECT srcRect;
    HRESULT hr;
    POINT pt;

    // NTS: dx_bitmap.is_valid() is not a valid test because base==canvas==NULL unless surface is locked
    if (ddsurfaceBMP == NULL) return;

    // NTS: We must provide a source rect, else Windows XP in 24bpp mode will conveniently choose to render the
    //      right half (where extra padding+junk exist) rather than from the left side. Provide a source rect
    //      to make it 100% clear which part of the surface we want blitted to screen.
    pt.x = pt.y = 0;
    ClientToScreen(hwndMain,&pt);
    GetClientRect(hwndMain,&dstRect);
    OffsetRect(&dstRect,pt.x,pt.y);
    srcRect.top = srcRect.left = 0;
    srcRect.right = dx_bitmap.width;
    srcRect.bottom = dx_bitmap.height;

    if (ddsurfaceGDI != NULL)
        dst = ddsurfaceGDI;
    else if (ddsurfacePrimary != NULL)
        dst = ddsurfacePrimary;
    else
        dst = NULL;

    if (dst != NULL)
        hr = dst->Blt(&dstRect,ddsurfaceBMP,&srcRect,0,NULL);
    else
        hr = DD_OK;

    if (hr == DDERR_SURFACELOST) {
        fprintf(stderr,"Whoops, the primary surface was lost.\n");
        if ((hr=dst->Restore()) != DD_OK) {
            fprintf(stderr,"Unable to restore surface hr=0x%08lx.\n",hr);
            unlock_bitmap();
            free_bitmap();
            free_dx_primary_surface();
            init_dx_primary_surface();

            RECT rct;
            GetClientRect(hwndMain,&rct);

            if (!init_bitmap(rct.right,rct.bottom))
                fprintf(stderr,"WARNING WM_RESIZE init_bitmap(%u,%u) failed\n",
                        (unsigned int)rct.right,(unsigned int)rct.bottom);

            if (lock_bitmap()) {
                render_pattern(dx_bitmap);
                unlock_bitmap();
            }

            InvalidateRect(hwndMain,NULL,FALSE); // DWM compositor-based versions set WM_PAINT such that only the affected area will repaint
        }
    }
    else if (hr != DD_OK) {
        fprintf(stderr,"DirectX blit failed, HR=0x%08lx\n",hr);
    }
}