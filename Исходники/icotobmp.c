static VOID PhpConvertToPArgb32IfNeeded(
    _In_ HPAINTBUFFER PaintBuffer,
    _In_ HDC hdc,
    _In_ HICON Icon,
    _In_ ULONG Width,
    _In_ ULONG Height
    )
{
    RGBQUAD *quad;
    ULONG rowWidth;

    if (SUCCEEDED(GetBufferedPaintBits_I(PaintBuffer, &quad, &rowWidth)))
    {
        PULONG argb = (PULONG)quad;

        if (!PhpHasAlpha(argb, Width, Height, rowWidth))
        {
            ICONINFO iconInfo;

            if (GetIconInfo(Icon, &iconInfo))
            {
                if (iconInfo.hbmMask)
                {
                    PhpConvertToPArgb32(hdc, argb, iconInfo.hbmMask, Width, Height, rowWidth);
                }

                DeleteObject(iconInfo.hbmColor);
                DeleteObject(iconInfo.hbmMask);
            }
        }
    }
}