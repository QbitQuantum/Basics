static void swapGlBuffers_w32(MPGLContext *ctx)
{
    HDC vo_hdc = GetDC(ctx->vo->w32->window);
    SwapBuffers(vo_hdc);
    ReleaseDC(ctx->vo->w32->window, vo_hdc);
}