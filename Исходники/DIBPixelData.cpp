void DIBPixelData::setRGBABitmapAlpha(HDC hdc, const IntRect& dstRect, unsigned char level)
{
    HBITMAP bitmap = static_cast<HBITMAP>(GetCurrentObject(hdc, OBJ_BITMAP));
    DIBPixelData pixelData(bitmap);
    ASSERT(pixelData.bitsPerPixel() == 32);

    IntRect drawRect(dstRect);
    XFORM trans;
    GetWorldTransform(hdc, &trans);
    IntSize transformedPosition(trans.eDx, trans.eDy);
    drawRect.move(transformedPosition);

    int pixelDataWidth = pixelData.size().width();
    int pixelDataHeight = pixelData.size().height();
    IntRect bitmapRect(0, 0, pixelDataWidth, pixelDataHeight);
    drawRect.intersect(bitmapRect);
    if (drawRect.isEmpty())
        return;

    RGBQUAD* bytes = reinterpret_cast<RGBQUAD*>(pixelData.buffer());
    bytes += drawRect.y() * pixelDataWidth;

    size_t width = drawRect.width();
    size_t height = drawRect.height();
    int x = drawRect.x();
    for (size_t i = 0; i < height; i++) {
        RGBQUAD* p = bytes + x;
        for (size_t j = 0; j < width; j++) {
            p->rgbReserved = level;
            p++;
        }
        bytes += pixelDataWidth;
    }
}