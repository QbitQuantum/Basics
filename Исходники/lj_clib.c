static void *clib_getsym(CLibrary *cl, const char *name)
{
    void *p = NULL;
    if (cl->handle == CLIB_DEFHANDLE) {  /* Search default libraries. */
        MSize i;
        for (i = 0; i < CLIB_HANDLE_MAX; i++) {
            HINSTANCE h = (HINSTANCE)clib_def_handle[i];
            if (!(void *)h) {  /* Resolve default library handles (once). */
                switch (i) {
                case CLIB_HANDLE_EXE:
                    GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, NULL, &h);
                    break;
                case CLIB_HANDLE_DLL:
                    GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS|GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                                       (const char *)clib_def_handle, &h);
                    break;
                case CLIB_HANDLE_CRT:
                    GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS|GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                                       (const char *)&_fmode, &h);
                    break;
                case CLIB_HANDLE_KERNEL32:
                    h = LoadLibraryExA("kernel32.dll", NULL, 0);
                    break;
                case CLIB_HANDLE_USER32:
                    h = LoadLibraryExA("user32.dll", NULL, 0);
                    break;
                case CLIB_HANDLE_GDI32:
                    h = LoadLibraryExA("gdi32.dll", NULL, 0);
                    break;
                }
                if (!h) continue;
                clib_def_handle[i] = (void *)h;
            }
            p = (void *)GetProcAddress(h, name);
            if (p) break;
        }
    } else {
        p = (void *)GetProcAddress((HINSTANCE)cl->handle, name);
    }
    return p;
}