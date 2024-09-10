static void init_DirectDraw() {
    /**
     * Note: if DirectDraw fails to initialize, we will use GDI to
     *  draw to do the screenBuffer->LCD copying.
     */
    HRESULT hRet;
    hRet = DirectDrawCreate(NULL, &g_pDD, NULL);
    if (hRet != DD_OK) {
        return;
    }

    hRet = g_pDD->SetCooperativeLevel(hwndMain, DDSCL_NORMAL);
    if (hRet != DD_OK) {
        g_pDD->Release();
        g_pDD = NULL;
        return;
    }

    wince_init_fonts();
}