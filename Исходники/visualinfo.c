void DestroyContext (GLContext* ctx)
{
  if (NULL == ctx) return;
  if (NULL != ctx->rc) wglMakeCurrent(NULL, NULL);
  if (NULL != ctx->rc) wglDeleteContext(wglGetCurrentContext());
  if (NULL != ctx->wnd && NULL != ctx->dc) ReleaseDC(ctx->wnd, ctx->dc);
  if (NULL != ctx->wnd) DestroyWindow(ctx->wnd);
  UnregisterClass(L"GLEW", GetModuleHandle(NULL));
}