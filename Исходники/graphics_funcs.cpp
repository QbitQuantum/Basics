bool GraphicsHelps::setWindowIcon(SDL_Window *window, FIBITMAP *img, int iconSize)
{
#ifdef _WIN32
    struct SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);

    if(-1 == SDL_GetWindowWMInfo(window, &wmInfo))
        return false;

    if(wmInfo.subsystem != SDL_SYSWM_WINDOWS)
        return false;

    HWND windowH = wmInfo.info.win.window;
    HICON hicon = NULL;
    BYTE *icon_bmp;
    unsigned int icon_len, y;
    SDL_RWops *dst;
    unsigned int w = FreeImage_GetWidth(img);
    unsigned int h = FreeImage_GetWidth(img);
    Uint8 *bits = (Uint8 *)FreeImage_GetBits(img);
    unsigned int pitch = FreeImage_GetPitch(img);
    /* Create temporary bitmap buffer */
    icon_len = 40 + h * w * 4;
    icon_bmp = SDL_stack_alloc(BYTE, icon_len);
    dst = SDL_RWFromMem(icon_bmp, icon_len);

    if(!dst)
    {
        SDL_stack_free(icon_bmp);
        return false;
    }

    /* Write the BITMAPINFO header */
    SDL_WriteLE32(dst, 40);
    SDL_WriteLE32(dst, w);
    SDL_WriteLE32(dst, h * 2);
    SDL_WriteLE16(dst, 1);
    SDL_WriteLE16(dst, 32);
    SDL_WriteLE32(dst, BI_RGB);
    SDL_WriteLE32(dst, h * w * 4);
    SDL_WriteLE32(dst, 0);
    SDL_WriteLE32(dst, 0);
    SDL_WriteLE32(dst, 0);
    SDL_WriteLE32(dst, 0);
    y = 0;

    do
    {
        Uint8 *src = bits + y * pitch;
        SDL_RWwrite(dst, src, pitch, 1);
    }
    while(++y < h);

    hicon = CreateIconFromResource(icon_bmp, icon_len, TRUE, 0x00030000);
    SDL_RWclose(dst);
    SDL_stack_free(icon_bmp);
    /* Set the icon for the window */
    SendMessage(windowH, WM_SETICON, (iconSize < 32) ? ICON_SMALL : ICON_BIG, (LPARAM) hicon);
#else
    (void)iconSize;
    SDL_Surface *sicon = GraphicsHelps::fi2sdl(img);
    SDL_SetWindowIcon(window, sicon);
    SDL_FreeSurface(sicon);
    const char *error = SDL_GetError();

    if(*error != '\0')
        return false;

#endif
    return true;
}