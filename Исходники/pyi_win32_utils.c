int
CreateActContext(const char *manifestpath)
{
    wchar_t * manifestpath_w;
    ACTCTXW ctx;
    BOOL activated;
    HANDLE k32;

    HANDLE (WINAPI * CreateActCtx)(PACTCTXW pActCtx);
    BOOL (WINAPI * ActivateActCtx)(HANDLE hActCtx, ULONG_PTR * lpCookie);

    /* Setup activation context */
    VS("LOADER: manifestpath: %s\n", manifestpath);
    manifestpath_w = pyi_win32_utils_from_utf8(NULL, manifestpath, 0);

    k32 = LoadLibraryA("kernel32");
    CreateActCtx = (void*)GetProcAddress(k32, "CreateActCtxW");
    ActivateActCtx = (void*)GetProcAddress(k32, "ActivateActCtx");

    if (!CreateActCtx || !ActivateActCtx) {
        VS("LOADER: Cannot find CreateActCtx/ActivateActCtx exports in kernel32.dll\n");
        return 0;
    }

    ZeroMemory(&ctx, sizeof(ctx));
    ctx.cbSize = sizeof(ACTCTX);
    ctx.lpSource = manifestpath_w;
    ctx.dwFlags = ACTCTX_FLAG_SET_PROCESS_DEFAULT;

    hCtx = CreateActCtx(&ctx);
    free(manifestpath_w);

    if (hCtx != INVALID_HANDLE_VALUE) {
        VS("LOADER: Activation context created\n");
        activated = ActivateActCtx(hCtx, &actToken);

        if (activated) {
            VS("LOADER: Activation context activated\n");
            return 1;
        }
    }

    hCtx = INVALID_HANDLE_VALUE;
    VS("LOADER: Error activating the context: ActivateActCtx: \n%s\n", GetWinErrorString(0));
    return 0;
}