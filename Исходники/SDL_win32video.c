static SDL_VideoDevice *
WIN_CreateDevice(int devindex)
{
    SDL_VideoDevice *device;
    SDL_VideoData *data;

    SDL_RegisterApp(NULL, 0, NULL);

    /* Initialize all variables that we clean on shutdown */
    device = (SDL_VideoDevice *) SDL_calloc(1, sizeof(SDL_VideoDevice));
    if (device) {
        data = (struct SDL_VideoData *) SDL_calloc(1, sizeof(SDL_VideoData));
    }
    if (!device || !data) {
        SDL_OutOfMemory();
        if (device) {
            SDL_free(device);
        }
        return NULL;
    }
    device->driverdata = data;

#if SDL_VIDEO_RENDER_D3D
    data->d3dDLL = LoadLibrary(TEXT("D3D9.DLL"));
    if (data->d3dDLL) {
        IDirect3D9 *(WINAPI * D3DCreate) (UINT SDKVersion);

        D3DCreate =
            (IDirect3D9 * (WINAPI *) (UINT)) GetProcAddress(data->d3dDLL,
                                                            "Direct3DCreate9");
        if (D3DCreate) {
            data->d3d = D3DCreate(D3D_SDK_VERSION);
        }
        if (!data->d3d) {
            FreeLibrary(data->d3dDLL);
            data->d3dDLL = NULL;
        }
    }
#endif /* SDL_VIDEO_RENDER_D3D */

    data->wintabDLL = LoadLibrary(TEXT("WINTAB32.DLL"));
    if (data->wintabDLL) {
#define PROCNAME(X) #X
        data->WTInfoA =
            (UINT(*)(UINT, UINT, LPVOID)) GetProcAddress(data->wintabDLL,
                                                         PROCNAME(WTInfoA));
        data->WTOpenA =
            (HCTX(*)(HWND, LPLOGCONTEXTA, BOOL)) GetProcAddress(data->
                                                                wintabDLL,
                                                                PROCNAME
                                                                (WTOpenA));
        data->WTPacket =
            (int (*)(HCTX, UINT, LPVOID)) GetProcAddress(data->wintabDLL,
                                                         PROCNAME(WTPacket));
        data->WTClose =
            (BOOL(*)(HCTX)) GetProcAddress(data->wintabDLL,
                                           PROCNAME(WTClose));
#undef PROCNAME

        if (!data->WTInfoA || !data->WTOpenA || !data->WTPacket
            || !data->WTClose) {
            FreeLibrary(data->wintabDLL);
            data->wintabDLL = NULL;
        }
    }

    /* Set the function pointers */
    device->VideoInit = WIN_VideoInit;
    device->VideoQuit = WIN_VideoQuit;
    device->GetDisplayModes = WIN_GetDisplayModes;
    device->SetDisplayMode = WIN_SetDisplayMode;
    device->SetDisplayGammaRamp = WIN_SetDisplayGammaRamp;
    device->GetDisplayGammaRamp = WIN_GetDisplayGammaRamp;
    device->PumpEvents = WIN_PumpEvents;

#undef CreateWindow
    device->CreateWindow = WIN_CreateWindow;
    device->CreateWindowFrom = WIN_CreateWindowFrom;
    device->SetWindowTitle = WIN_SetWindowTitle;
    device->SetWindowIcon = WIN_SetWindowIcon;
    device->SetWindowPosition = WIN_SetWindowPosition;
    device->SetWindowSize = WIN_SetWindowSize;
    device->ShowWindow = WIN_ShowWindow;
    device->HideWindow = WIN_HideWindow;
    device->RaiseWindow = WIN_RaiseWindow;
    device->MaximizeWindow = WIN_MaximizeWindow;
    device->MinimizeWindow = WIN_MinimizeWindow;
    device->RestoreWindow = WIN_RestoreWindow;
    device->SetWindowGrab = WIN_SetWindowGrab;
    device->DestroyWindow = WIN_DestroyWindow;
    device->GetWindowWMInfo = WIN_GetWindowWMInfo;
#ifdef SDL_VIDEO_OPENGL_WGL
    device->GL_LoadLibrary = WIN_GL_LoadLibrary;
    device->GL_GetProcAddress = WIN_GL_GetProcAddress;
    device->GL_UnloadLibrary = WIN_GL_UnloadLibrary;
    device->GL_CreateContext = WIN_GL_CreateContext;
    device->GL_MakeCurrent = WIN_GL_MakeCurrent;
    device->GL_SetSwapInterval = WIN_GL_SetSwapInterval;
    device->GL_GetSwapInterval = WIN_GL_GetSwapInterval;
    device->GL_SwapWindow = WIN_GL_SwapWindow;
    device->GL_DeleteContext = WIN_GL_DeleteContext;
#endif

    device->free = WIN_DeleteDevice;

    return device;
}