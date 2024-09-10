static SDL_Cursor *
WIN_CreateCursor(SDL_Surface * surface, int hot_x, int hot_y)
{
    SDL_Cursor *cursor;
    HICON hicon;
    HDC hdc;
    BITMAPV4HEADER bmh;
    LPVOID pixels;
    ICONINFO ii;

    SDL_zero(bmh);
    bmh.bV4Size = sizeof(bmh);
    bmh.bV4Width = surface->w;
    bmh.bV4Height = -surface->h; /* Invert the image */
    bmh.bV4Planes = 1;
    bmh.bV4BitCount = 32;
    bmh.bV4V4Compression = BI_BITFIELDS;
    bmh.bV4AlphaMask = 0xFF000000;
    bmh.bV4RedMask   = 0x00FF0000;
    bmh.bV4GreenMask = 0x0000FF00;
    bmh.bV4BlueMask  = 0x000000FF;

    hdc = GetDC(NULL);
    SDL_zero(ii);
    ii.fIcon = FALSE;
    ii.xHotspot = (DWORD)hot_x;
    ii.yHotspot = (DWORD)hot_y;
    ii.hbmColor = CreateDIBSection(hdc, (BITMAPINFO*)&bmh, DIB_RGB_COLORS, &pixels, NULL, 0);
    ii.hbmMask = CreateBitmap(surface->w, surface->h, 1, 1, NULL);
    ReleaseDC(NULL, hdc);

    SDL_assert(surface->format->format == SDL_PIXELFORMAT_ARGB8888);
    SDL_assert(surface->pitch == surface->w * 4);
    SDL_memcpy(pixels, surface->pixels, surface->h * surface->pitch);

    hicon = CreateIconIndirect(&ii);

    DeleteObject(ii.hbmColor);
    DeleteObject(ii.hbmMask);

    if (!hicon) {
        WIN_SetError("CreateIconIndirect()");
        return NULL;
    }

    cursor = SDL_calloc(1, sizeof(*cursor));
    if (cursor) {
        cursor->driverdata = hicon;
    } else {
        DestroyIcon(hicon);
        SDL_OutOfMemory();
    }

    return cursor;
}