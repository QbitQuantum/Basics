static bool compositor_active(MPGLContext *ctx)
{
    // For Windows 7.
    BOOL enabled = 0;
    if (FAILED(DwmIsCompositionEnabled(&enabled)) || !enabled)
        return false;

    // This works at least on Windows 8.1: it returns an error in fullscreen,
    // which is also when we get consistent timings without DwmFlush. Might
    // be cargo-cult.
    DWM_TIMING_INFO info = { .cbSize = sizeof(DWM_TIMING_INFO) };
    if (FAILED(DwmGetCompositionTimingInfo(0, &info)))
        return false;

    // Test if a program is running in exclusive fullscreen mode. If so, it's
    // probably this one, so it's not getting redirected by the compositor.
    if (mp_w32_is_in_exclusive_mode())
        return false;

    return true;
}

static void w32_swap_buffers(MPGLContext *ctx)
{
    struct w32_context *w32_ctx = ctx->priv;
    SwapBuffers(w32_ctx->hdc);

    // default if we don't DwmFLush
    int new_swapinterval = w32_ctx->opt_swapinterval;

    if (ctx->dwm_flush_opt >= 0) {
        if ((ctx->dwm_flush_opt == 1 && !ctx->vo->opts->fullscreen) ||
            (ctx->dwm_flush_opt == 2) ||
            (ctx->dwm_flush_opt == 0 && compositor_active(ctx)))
        {
            if (DwmFlush() == S_OK)
                new_swapinterval = 0;
        }
    }

    if (new_swapinterval != w32_ctx->current_swapinterval &&
        w32_ctx->real_wglSwapInterval)
    {
        w32_ctx->real_wglSwapInterval(new_swapinterval);
        MP_VERBOSE(ctx->vo, "set SwapInterval(%d)\n", new_swapinterval);
    }
    w32_ctx->current_swapinterval = new_swapinterval;
}

static int w32_control(MPGLContext *ctx, int *events, int request, void *arg)
{
    return vo_w32_control(ctx->vo, events, request, arg);
}

const struct mpgl_driver mpgl_driver_w32 = {
    .name           = "w32",
    .priv_size      = sizeof(struct w32_context),
    .init           = w32_init,
    .reconfig       = w32_reconfig,
    .swap_buffers   = w32_swap_buffers,
    .control        = w32_control,
    .uninit         = w32_uninit,
};