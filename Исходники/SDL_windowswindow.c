void
WIN_SetWindowIcon(_THIS, SDL_Window * window, SDL_Surface * icon)
{
    HWND hwnd = ((SDL_WindowData *) window->driverdata)->hwnd;
    HICON hicon = NULL;
    BYTE *icon_bmp;
    int icon_len;
    SDL_RWops *dst;
    SDL_Surface *surface;

    /* Create temporary bitmap buffer */
    icon_len = 40 + icon->h * icon->w * 4;
    icon_bmp = SDL_stack_alloc(BYTE, icon_len);
    dst = SDL_RWFromMem(icon_bmp, icon_len);
    if (!dst) {
        SDL_stack_free(icon_bmp);
        return;
    }

    /* Write the BITMAPINFO header */
    SDL_WriteLE32(dst, 40);
    SDL_WriteLE32(dst, icon->w);
    SDL_WriteLE32(dst, icon->h * 2);
    SDL_WriteLE16(dst, 1);
    SDL_WriteLE16(dst, 32);
    SDL_WriteLE32(dst, BI_RGB);
    SDL_WriteLE32(dst, icon->h * icon->w * 4);
    SDL_WriteLE32(dst, 0);
    SDL_WriteLE32(dst, 0);
    SDL_WriteLE32(dst, 0);
    SDL_WriteLE32(dst, 0);

    /* Convert the icon to a 32-bit surface with alpha channel */
    surface = SDL_ConvertSurfaceFormat(icon, SDL_PIXELFORMAT_ARGB8888, 0);
    if (surface) {
        /* Write the pixels upside down into the bitmap buffer */
        int y = surface->h;
        while (y--) {
            Uint8 *src = (Uint8 *) surface->pixels + y * surface->pitch;
            SDL_RWwrite(dst, src, surface->pitch, 1);
        }
        SDL_FreeSurface(surface);

/* TODO: create the icon in WinCE (CreateIconFromResource isn't available) */
#ifndef _WIN32_WCE
        hicon = CreateIconFromResource(icon_bmp, icon_len, TRUE, 0x00030000);
#endif
    }
    SDL_RWclose(dst);
    SDL_stack_free(icon_bmp);

    /* Set the icon for the window */
    SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM) hicon);

    /* Set the icon in the task manager (should we do this?) */
    SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM) hicon);
}