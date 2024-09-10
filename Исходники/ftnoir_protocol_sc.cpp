 ~ActivationContext() {
     if (hactctx != INVALID_HANDLE_VALUE)
     {
         DeactivateActCtx(0, actctx_cookie);
         ReleaseActCtx(hactctx);
     }
 }