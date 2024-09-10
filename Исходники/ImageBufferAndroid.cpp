PassRefPtr<ByteArray> ImageBuffer::getUnmultipliedImageData(const IntRect& rect) const
{
    GraphicsContext* gc = this->context();
    if (!gc) {
        return 0;
    }

    const SkBitmap& src = imageBufferCanvas(this)->getDevice()->accessBitmap(false);
    SkAutoLockPixels alp(src);
    if (!src.getPixels()) {
        return 0;
    }

    RefPtr<ByteArray> result = ByteArray::create(rect.width() * rect.height() * 4);
    unsigned char* data = result->data();

    if (rect.x() < 0 || rect.y() < 0 || rect.maxX() > m_size.width() || rect.maxY() > m_size.height())
        memset(data, 0, result->length());

    int originx = rect.x();
    int destx = 0;
    if (originx < 0) {
        destx = -originx;
        originx = 0;
    }
    int endx = rect.x() + rect.width();
    if (endx > m_size.width())
        endx = m_size.width();
    int numColumns = endx - originx;

    int originy = rect.y();
    int desty = 0;
    if (originy < 0) {
        desty = -originy;
        originy = 0;
    }
    int endy = rect.y() + rect.height();
    if (endy > m_size.height())
        endy = m_size.height();
    int numRows = endy - originy;

    unsigned srcPixelsPerRow = src.rowBytesAsPixels();
    unsigned destBytesPerRow = 4 * rect.width();

    /// M: change process to read pixel @{
    /* fix w3c pixel manipulation relative test case */
    SkBitmap destBitmap;
    destBitmap.setConfig(SkBitmap::kARGB_8888_Config, rect.width(), rect.height(), destBytesPerRow);
    destBitmap.setPixels(data);

    SkCanvas* canvas = imageBufferCanvas(this);
    canvas->readPixels(&destBitmap, rect.x(), rect.y(), SkCanvas::kRGBA_Unpremul_Config8888);
    return result.release();
    /// @}
}