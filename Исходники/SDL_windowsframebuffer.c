int WIN_CreateWindowFramebuffer(_THIS, SDL_Window * window, Uint32 * format, void ** pixels, int *pitch)
{
    SDL_WindowData *data = (SDL_WindowData *) window->driverdata;
    size_t size;
    LPBITMAPINFO info;
#ifdef HAVE_GETDIBITS
    HBITMAP hbm;
#endif

    /* Free the old framebuffer surface */
    if (data->mdc) {
        DeleteDC(data->mdc);
    }
    if (data->hbm) {
        DeleteObject(data->hbm);
    }

    /* Find out the format of the screen */
    size = sizeof(BITMAPINFOHEADER) + 256 * sizeof (RGBQUAD);
    info = (LPBITMAPINFO)SDL_stack_alloc(Uint8, size);

#ifdef HAVE_GETDIBITS
    SDL_memset(info, 0, size);
    info->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);

    /* The second call to GetDIBits() fills in the bitfields */
    hbm = CreateCompatibleBitmap(data->hdc, 1, 1);
    GetDIBits(data->hdc, hbm, 0, 0, NULL, info, DIB_RGB_COLORS);
    GetDIBits(data->hdc, hbm, 0, 0, NULL, info, DIB_RGB_COLORS);
    DeleteObject(hbm);

    *format = SDL_PIXELFORMAT_UNKNOWN;
    if (info->bmiHeader.biCompression == BI_BITFIELDS) {
        int bpp;
        Uint32 *masks;

        bpp = info->bmiHeader.biPlanes * info->bmiHeader.biBitCount;
        masks = (Uint32*)((Uint8*)info + info->bmiHeader.biSize);
        *format = SDL_MasksToPixelFormatEnum(bpp, masks[0], masks[1], masks[2], 0);
    }
    if (*format == SDL_PIXELFORMAT_UNKNOWN)
#endif
    {
        /* We'll use RGB format for now */
        *format = SDL_PIXELFORMAT_RGB888;

        /* Create a new one */
        SDL_memset(info, 0, size);
        info->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        info->bmiHeader.biPlanes = 1;
        info->bmiHeader.biBitCount = 32;
        info->bmiHeader.biCompression = BI_RGB;
    }

    /* Fill in the size information */
    *pitch = (((window->w * SDL_BYTESPERPIXEL(*format)) + 3) & ~3);
    info->bmiHeader.biWidth = window->w;
    info->bmiHeader.biHeight = -window->h;	/* negative for topdown bitmap */
    info->bmiHeader.biSizeImage = window->h * (*pitch);

    data->mdc = CreateCompatibleDC(data->hdc);
    data->hbm = CreateDIBSection(data->hdc, info, DIB_RGB_COLORS, pixels, NULL, 0);
    SDL_stack_free(info);

    if (!data->hbm) {
        WIN_SetError("Unable to create DIB");
        return -1;
    }
    SelectObject(data->mdc, data->hbm);

    return 0;
}