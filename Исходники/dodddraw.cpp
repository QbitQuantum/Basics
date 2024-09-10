int DDInitWindowed(int width, int height, int bpp, HWND hwnd)
{
    HRESULT ret;
    
    // create object and test for error
    if (DirectDrawCreate(NULL, &lpDD, NULL) != DD_OK) {
        return(0);
    }
    
    // set cooperation level to windowed mode normal
    if (lpDD->SetCooperativeLevel(hwnd, DDSCL_NORMAL) != DD_OK) {
        return(0);
    }
    
    // set globals
    screen_height = height;
    screen_width = width;
    screen_bpp = bpp;
    
    // Create the primary surface
    memset(&ddsd, 0, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS;
    
    // all we need for windowed mode is access to the primary surface
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
    
    // create the primary surface
    ret = lpDD->CreateSurface(&ddsd, &lpDDSPrimary, NULL);
    
    // create an offscreen and system mem back surface
    lpDDSBack = DDCreateSurface(width, height, NULL);
    
    lpDD->CreateClipper(0, &lpDDClipper, NULL);
    lpDDClipper->SetHWnd(0, hwnd);
    lpDDSPrimary->SetClipper(lpDDClipper);
    
    // clear out both primary and secondary surfaces
    DDFillSurface(lpDDSPrimary, 0);
    DDFillSurface(lpDDSBack, 0);
    
    DDGetRGB16();
    
    return 1;
}