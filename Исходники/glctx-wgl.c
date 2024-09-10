void glctx_flip(GlctxHandle ctx)
{
    SwapBuffers(ctx->dpy);
}