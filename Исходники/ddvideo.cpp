//! Init DirectDraw Stuff
bool DDInit()
{
    HRESULT hRet;
    g_rcSrc.right = g_sizex;
    g_rcSrc.bottom = g_sizey;

    hRet = DirectDrawCreateEx(NULL, (VOID**)&g_pDD, IID_IDirectDraw7, NULL);
    if (hRet != DD_OK)
        return DisplayError("Can't create DirectDraw7 instance", hRet);

    // Set cooperation level with other windows to be normal (ie. not full screen)
    // You MUST set the cooperation level to be SOMETHING, for windowed apps use
    // DDSCL_NORMAL, for full screen use: DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN.
    hRet = g_pDD->SetCooperativeLevel(g_hAppWnd, DDSCL_NORMAL);
    if (hRet != DD_OK)
        return DisplayError("Can't set cooperative level", hRet);
    return DDPrimaryInit();
}