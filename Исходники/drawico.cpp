void DrawIconSatnHue (
    HDC hDC,
    int px,
    int py,
    HICON IconHop,
    int size_x,
    int size_y,
    UINT istepIfAniCur, // index of frame in animated cursor
    HBRUSH hbrFlickerFreeDraw,  // handle to background brush
    UINT diFlags, // icon-drawing flags
    int apply_satnhue,
    int saturationValue,
    int hueIntensity
    )
{
    if (0 == apply_satnhue || (saturationValue >= 255 && hueIntensity <= 0)) {
        DrawIconEx(hDC, px, py, IconHop, size_x, size_y, istepIfAniCur, hbrFlickerFreeDraw, diFlags);
        return;
    }

    BITMAPINFOHEADER bv4info;

    ZeroMemory(&bv4info,sizeof(bv4info));
    bv4info.biSize = sizeof(bv4info);
    bv4info.biWidth = size_x;
    bv4info.biHeight = size_y * 3;
    bv4info.biPlanes = 1;
    bv4info.biBitCount = 32;
    bv4info.biCompression = BI_RGB;

    BYTE* pixels;

    HBITMAP bufbmp = CreateDIBSection(NULL, (BITMAPINFO*)&bv4info, DIB_RGB_COLORS, (PVOID*)&pixels, NULL, 0);

    if (NULL == bufbmp)
        return;

    HDC bufdc = CreateCompatibleDC(hDC);
    HGDIOBJ other = SelectObject(bufdc, bufbmp);

    // draw the required three things side by side

    // background for hue
    BitBlt(bufdc,       0, 0,       size_x, size_y, hDC, px, py, SRCCOPY);

    // background for icon
    BitBlt(bufdc,       0, size_y,    size_x, size_y, hDC, px, py, SRCCOPY);

    // icon, in colors
    DrawIconEx(bufdc,   0, size_y,    IconHop, size_x, size_y, 0, NULL, DI_NORMAL);

    // icon mask
    DrawIconEx(bufdc,   0, size_y*2,  IconHop, size_x, size_y, 0, NULL, DI_MASK);

    perform_satnhue(pixels, size_x, size_y, saturationValue, hueIntensity);

    BitBlt(hDC, px, py, size_x, size_y, bufdc, 0, 0, SRCCOPY);

    DeleteObject(SelectObject(bufdc, other));
    DeleteDC(bufdc);
}