static int
DirectFB_RenderReadPixels(SDL_Renderer * renderer, const SDL_Rect * rect,
                     Uint32 format, void * pixels, int pitch)
{
    Uint32 sdl_format;
    unsigned char* laypixels;
    int laypitch;
    DFBSurfacePixelFormat dfb_format;
    DirectFB_RenderData *data = (DirectFB_RenderData *) renderer->driverdata;
    IDirectFBSurface *winsurf = data->target;

    DirectFB_ActivateRenderer(renderer);

    winsurf->GetPixelFormat(winsurf, &dfb_format);
    sdl_format = DirectFB_DFBToSDLPixelFormat(dfb_format);
    winsurf->Lock(winsurf, DSLF_READ, (void **) &laypixels, &laypitch);

    laypixels += (rect->y * laypitch + rect->x * SDL_BYTESPERPIXEL(sdl_format) );
    SDL_ConvertPixels(rect->w, rect->h,
                      sdl_format, laypixels, laypitch,
                      format, pixels, pitch);

    winsurf->Unlock(winsurf);

    return 0;
}