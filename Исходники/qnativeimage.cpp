QNativeImage::QNativeImage(int width, int height, QImage::Format format, bool isTextBuffer, QWidget *)
{
#ifndef Q_WS_WINCE
    Q_UNUSED(isTextBuffer);
#endif
    BITMAPINFO_MASK bmi;
    memset(&bmi, 0, sizeof(bmi));
    bmi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth       = width;
    bmi.bmiHeader.biHeight      = -height;
    bmi.bmiHeader.biPlanes      = 1;
    bmi.bmiHeader.biSizeImage   = 0;

    if (format == QImage::Format_RGB16) {
        bmi.bmiHeader.biBitCount = 16;
#ifdef Q_WS_WINCE
        if (isTextBuffer) {
            bmi.bmiHeader.biCompression = BI_RGB;
            bmi.redMask = 0;
            bmi.greenMask = 0;
            bmi.blueMask = 0;
        } else
#endif
        {
            bmi.bmiHeader.biCompression = BI_BITFIELDS;
            bmi.redMask = 0xF800;
            bmi.greenMask = 0x07E0;
            bmi.blueMask = 0x001F;
        }
    } else {
        bmi.bmiHeader.biBitCount    = 32;
        bmi.bmiHeader.biCompression = BI_RGB;
        bmi.redMask = 0;
        bmi.greenMask = 0;
        bmi.blueMask = 0;
    }

    HDC display_dc = GetDC(0);
    hdc = CreateCompatibleDC(display_dc);
    ReleaseDC(0, display_dc);
    Q_ASSERT(hdc);

    uchar *bits = 0;
    bitmap = CreateDIBSection(hdc, reinterpret_cast<BITMAPINFO *>(&bmi), DIB_RGB_COLORS, (void**) &bits, 0, 0);
    Q_ASSERT(bitmap);
    Q_ASSERT(bits);

    null_bitmap = (HBITMAP)SelectObject(hdc, bitmap);
    image = QImage(bits, width, height, format);

    Q_ASSERT(image.paintEngine()->type() == QPaintEngine::Raster);
    static_cast<QRasterPaintEngine *>(image.paintEngine())->setDC(hdc);

#ifndef Q_WS_WINCE
    GdiFlush();
#endif
}