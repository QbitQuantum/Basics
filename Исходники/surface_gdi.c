/*****************************************************************************
 * x11_copy_to_screen
 *
 * Helper function that blts the front buffer contents to the target window
 *
 * Params:
 *  This: Surface to copy from
 *  rc: Rectangle to copy
 *
 *****************************************************************************/
static void
x11_copy_to_screen(IWineD3DSurfaceImpl *This,
                   LPRECT rc)
{
    if(This->resource.usage & WINED3DUSAGE_RENDERTARGET)
    {
        POINT offset = {0,0};
        HWND hDisplayWnd;
        HDC hDisplayDC;
        HDC hSurfaceDC = 0;
        RECT drawrect;
        TRACE("(%p)->(%p): Copying to screen\n", This, rc);

        hSurfaceDC = This->hDC;

        hDisplayWnd = This->resource.wineD3DDevice->ddraw_window;
        hDisplayDC = GetDCEx(hDisplayWnd, 0, DCX_CLIPSIBLINGS|DCX_CACHE);
        if(rc)
        {
            TRACE(" copying rect (%d,%d)->(%d,%d), offset (%d,%d)\n",
            rc->left, rc->top, rc->right, rc->bottom, offset.x, offset.y);
        }

        /* Front buffer coordinates are screen coordinates. Map them to the destination
         * window if not fullscreened
         */
        if(!This->resource.wineD3DDevice->ddraw_fullscreen) {
            ClientToScreen(hDisplayWnd, &offset);
        }
#if 0
        /* FIXME: this doesn't work... if users really want to run
        * X in 8bpp, then we need to call directly into display.drv
        * (or Wine's equivalent), and force a private colormap
        * without default entries. */
        if (This->palette) {
            SelectPalette(hDisplayDC, This->palette->hpal, FALSE);
            RealizePalette(hDisplayDC); /* sends messages => deadlocks */
        }
#endif
        drawrect.left	= 0;
        drawrect.right	= This->currentDesc.Width;
        drawrect.top	= 0;
        drawrect.bottom	= This->currentDesc.Height;

#if 0
        /* TODO: Support clippers */
        if (This->clipper)
        {
            RECT xrc;
            HWND hwnd = ((IWineD3DClipperImpl *) This->clipper)->hWnd;
            if (hwnd && GetClientRect(hwnd,&xrc))
            {
                OffsetRect(&xrc,offset.x,offset.y);
                IntersectRect(&drawrect,&drawrect,&xrc);
            }
        }
#endif
        if (rc)
        {
            IntersectRect(&drawrect,&drawrect,rc);
        }
        else
        {
            /* Only use this if the caller did not pass a rectangle, since
             * due to double locking this could be the wrong one ...
             */
            if (This->lockedRect.left != This->lockedRect.right)
            {
                IntersectRect(&drawrect,&drawrect,&This->lockedRect);
            }
        }

        BitBlt(hDisplayDC,
               drawrect.left-offset.x, drawrect.top-offset.y,
               drawrect.right-drawrect.left, drawrect.bottom-drawrect.top,
               hSurfaceDC,
               drawrect.left, drawrect.top,
               SRCCOPY);
        ReleaseDC(hDisplayWnd, hDisplayDC);
    }
}