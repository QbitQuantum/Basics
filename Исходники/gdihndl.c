PPH_STRING PhpGetGdiHandleInformation(
    _In_ ULONG Handle
    )
{
    HGDIOBJ handle;

    handle = (HGDIOBJ)UlongToPtr(Handle);

    switch (GDI_CLIENT_TYPE_FROM_HANDLE(Handle))
    {
    case GDI_CLIENT_BITMAP_TYPE:
    case GDI_CLIENT_DIBSECTION_TYPE:
        {
            BITMAP bitmap;

            if (GetObject(handle, sizeof(BITMAP), &bitmap))
            {
                return PhFormatString(
                    L"Width: %u, Height: %u, Depth: %u",
                    bitmap.bmWidth,
                    bitmap.bmHeight,
                    bitmap.bmBitsPixel
                    );
            }
        }
        break;
    case GDI_CLIENT_BRUSH_TYPE:
        {
            LOGBRUSH brush;

            if (GetObject(handle, sizeof(LOGBRUSH), &brush))
            {
                return PhFormatString(
                    L"Style: %u, Color: 0x%08x, Hatch: 0x%Ix",
                    brush.lbStyle,
                    _byteswap_ulong(brush.lbColor),
                    brush.lbHatch
                    );
            }
        }
        break;
    case GDI_CLIENT_EXTPEN_TYPE:
        {
            EXTLOGPEN pen;

            if (GetObject(handle, sizeof(EXTLOGPEN), &pen))
            {
                return PhFormatString(
                    L"Style: 0x%x, Width: %u, Color: 0x%08x",
                    pen.elpPenStyle,
                    pen.elpWidth,
                    _byteswap_ulong(pen.elpColor)
                    );
            }
        }
        break;
    case GDI_CLIENT_FONT_TYPE:
        {
            LOGFONT font;

            if (GetObject(handle, sizeof(LOGFONT), &font))
            {
                return PhFormatString(
                    L"Face: %s, Height: %d",
                    font.lfFaceName,
                    font.lfHeight
                    );
            }
        }
        break;
    case GDI_CLIENT_PALETTE_TYPE:
        {
            USHORT count;

            if (GetObject(handle, sizeof(USHORT), &count))
            {
                return PhFormatString(
                    L"Entries: %u",
                    (ULONG)count
                    );
            }
        }
        break;
    case GDI_CLIENT_PEN_TYPE:
        {
            LOGPEN pen;

            if (GetObject(handle, sizeof(LOGPEN), &pen))
            {
                return PhFormatString(
                    L"Style: %u, Width: %u, Color: 0x%08x",
                    pen.lopnStyle,
                    pen.lopnWidth.x,
                    _byteswap_ulong(pen.lopnColor)
                    );
            }
        }
        break;
    }

    return NULL;
}