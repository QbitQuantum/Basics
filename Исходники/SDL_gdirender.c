static int
GDI_LockTexture(SDL_Renderer * renderer, SDL_Texture * texture,
                const SDL_Rect * rect, int markDirty, void **pixels,
                int *pitch)
{
    GDI_TextureData *data = (GDI_TextureData *) texture->driverdata;

    if (data->yuv) {
        return SDL_SW_LockYUVTexture(data->yuv, rect, markDirty, pixels,
                                     pitch);
    } else if (data->pixels) {
#ifndef _WIN32_WCE
        /* WinCE has no GdiFlush */
        GdiFlush();
#endif
        *pixels =
            (void *) ((Uint8 *) data->pixels + rect->y * data->pitch +
                      rect->x * SDL_BYTESPERPIXEL(texture->format));
        *pitch = data->pitch;
        return 0;
    } else {
        SDL_SetError("No pixels available");
        return -1;
    }
}