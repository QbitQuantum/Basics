bool SurfaceTexture::conversionIsNeeded(const sp<GraphicBuffer>& graphicBuffer) {
    int fmt = graphicBuffer->getPixelFormat();
    return (fmt == PIXEL_FORMAT_YCBCR42XMBN) || (fmt == PIXEL_FORMAT_YCbCr_420_P);
}