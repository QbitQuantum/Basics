static void
PluginDraw(InstanceData* id)
{
    NPP npp = id->npp;

    HDC hdc = (HDC) id->window.window;

    int savedDCID = SaveDC(hdc);

    const RECT fill = { id->window.x, id->window.y, id->window.x + id->window.width, id->window.y + id->window.height };
    SetBkMode(hdc, TRANSPARENT);
    HBRUSH brush = ::CreateSolidBrush(RGB(192, 120, 50));
    FillRect(hdc, &fill, brush);
    DeleteObject(brush);

    if (id->window.width > 2 && id->window.height > 2) {
        brush = CreateSolidBrush(RGB(212, 192, 150));
        const RECT inset = { id->window.x + 1, id->window.y + 1, id->window.x + id->window.width - 1, id->window.y + id->window.height - 1 };
        FillRect(hdc, &inset, brush);
        DeleteObject(brush);
    }

    if (id->window.width > 6 && id->window.height > 6) {
        HFONT font = CreateFont(20, 0, 0, 0, 400, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS, 5, DEFAULT_PITCH, L"Arial");
        SelectObject(hdc, font);
        RECT inset = { id->window.x + 3, id->window.y + 3, id->window.x + id->window.width - 3, id->window.y + id->window.height - 3 };
        DrawText(hdc, L"Hello, world.", -1, &inset, DT_LEFT | DT_TOP | DT_NOPREFIX | DT_WORDBREAK);
        DeleteObject(font);
    }

    RestoreDC(hdc, savedDCID);
}