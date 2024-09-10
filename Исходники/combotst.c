HWND
CreatePushButton(const char* lpWindowName, DWORD xSize, DWORD id,DWORD Style)
    {

    HWND h = CreateWindow("BUTTON",
        lpWindowName,
        WS_CHILD | BS_PUSHBUTTON | Style,
        xButPos, /* x */
        yButPos, /* y */
        xSize,   /* nWidth */
        20,      /* nHeight */
        g_hwnd,
        LongToHandle(id),
        g_hInst,
        NULL
        );

    yButPos += 21;
    return h;
    }