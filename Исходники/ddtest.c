BOOL DDPrimarySurfaceTest(HWND hWnd){
    UINT TimerID;
    MSG msg;

    LPDIRECTDRAW lpDD = NULL;
    LPDIRECTDRAWSURFACE lpDDSurface = NULL;
    DDSURFACEDESC DDSurfaceDesc;

    if(DirectDrawCreate(NULL, &lpDD, NULL) != DD_OK)
        return FALSE;

    if(lpDD->lpVtbl->SetCooperativeLevel(lpDD, hWnd, DDSCL_NORMAL) != DD_OK)
    {
        lpDD->lpVtbl->Release(lpDD);
        return FALSE;
    }

    /* create our primary surface */
    ZeroMemory(&DDSurfaceDesc, sizeof(DDSurfaceDesc));
    DDSurfaceDesc.dwSize = sizeof(DDSurfaceDesc);
    DDSurfaceDesc.dwFlags = DDSD_CAPS;
    DDSurfaceDesc.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_3DDEVICE;
    DDSurfaceDesc.dwBackBufferCount = 0;

    if(lpDD->lpVtbl->CreateSurface(lpDD, &DDSurfaceDesc, &lpDDSurface, NULL) != DD_OK)
    {
        lpDD->lpVtbl->Release(lpDD);
        return FALSE;
    }

    TimerID = SetTimer(hWnd, -1, (UINT)TEST_DURATION, NULL);

    while (TRUE)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_TIMER && TimerID == msg.wParam)
                break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_PAINT)
                DDRedrawFrame(lpDDSurface);
        }
    }
    KillTimer(hWnd, TimerID);
    lpDDSurface->lpVtbl->Release(lpDDSurface);
    lpDD->lpVtbl->Release(lpDD);

return TRUE;
}