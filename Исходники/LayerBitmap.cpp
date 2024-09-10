status_t LayerBitmap::resize(uint32_t w, uint32_t h)
{
    int err = setBits(w, h, mAlignment, pixelFormat(), SECURE_BITS);
    return err;
}