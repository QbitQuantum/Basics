//
// This is meant to be called only by CONS_Printf() while game startup
//
void I_LoadingScreen(LPCSTR msg)
{
    RECT rect;

    // paranoia
    if (!hDCMain || !bmiMain || !vid.buffer)
        return;

    GetClientRect(vid.WndParent, &rect);

    SetDIBitsToDevice(hDCMain, 0, 0, vid.width, vid.height, 0, 0, 0, vid.height, vid.buffer, bmiMain, DIB_RGB_COLORS);

    if (msg)
    {
        if (rect.bottom - rect.top > 32)
            rect.top = rect.bottom - 32; // put msg on bottom of window
        SetBkMode(hDCMain, TRANSPARENT);
        SetTextColor(hDCMain, RGB(0x00, 0x00, 0x00));
        DrawTextA(hDCMain, msg, -1, &rect, DT_WORDBREAK|DT_CENTER);
    }
}