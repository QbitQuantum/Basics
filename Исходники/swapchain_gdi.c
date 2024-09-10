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
void x11_copy_to_screen(IWineD3DSwapChainImpl *This, const RECT *rc)
{
    IWineD3DSurfaceImpl *front = This->front_buffer;

    if(front->resource.usage & WINED3DUSAGE_RENDERTARGET) {
        POINT offset = {0,0};
        HWND hDisplayWnd;
        HDC hDisplayDC;
        HDC hSurfaceDC = 0;
        RECT drawrect;
        TRACE("(%p)->(%p): Copying to screen\n", front, rc);

        hSurfaceDC = front->hDC;

        hDisplayWnd = This->win_handle;
        hDisplayDC = GetDCEx(hDisplayWnd, 0, DCX_CLIPSIBLINGS|DCX_CACHE);
        if(rc) {
            TRACE(" copying rect (%d,%d)->(%d,%d), offset (%d,%d)\n",
                  rc->left, rc->top, rc->right, rc->bottom, offset.x, offset.y);
        }

        /* Front buffer coordinates are screen coordinates. Map them to the destination
         * window if not fullscreened
         */
        if(This->presentParms.Windowed) {
            ClientToScreen(hDisplayWnd, &offset);
        }
#if 0
        /* FIXME: This doesn't work... if users really want to run
        * X in 8bpp, then we need to call directly into display.drv
        * (or Wine's equivalent), and force a private colormap
        * without default entries. */
        if (front->palette) {
        SelectPalette(hDisplayDC, front->palette->hpal, FALSE);
        RealizePalette(hDisplayDC); /* sends messages => deadlocks */
    }
#endif
        drawrect.left   = 0;
        drawrect.right  = front->currentDesc.Width;
        drawrect.top    = 0;
        drawrect.bottom = front->currentDesc.Height;

#if 0
        /* TODO: Support clippers */
        if (front->clipper)
        {
        RECT xrc;
        HWND hwnd = ((IWineD3DClipperImpl *) front->clipper)->hWnd;
        if (hwnd && GetClientRect(hwnd,&xrc))
        {
        OffsetRect(&xrc,offset.x,offset.y);
        IntersectRect(&drawrect,&drawrect,&xrc);
    }
    }
#endif
        if (rc) {
            IntersectRect(&drawrect,&drawrect,rc);
        }
        else {
            /* Only use this if the caller did not pass a rectangle, since
            * due to double locking this could be the wrong one ...
            */
            if (front->lockedRect.left != front->lockedRect.right) {
                IntersectRect(&drawrect,&drawrect,&front->lockedRect);
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