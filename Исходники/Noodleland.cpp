static GraphicBuffer*
create_composible_buffer(int width, int height) {
    uint32_t bufferFlags = GraphicBuffer::USAGE_SW_WRITE_RARELY | GraphicBuffer::USAGE_HW_COMPOSER;
    GraphicBuffer* buffer = new GraphicBuffer(width, height, PIXEL_FORMAT_RGBA_8888, bufferFlags);

    status_t err = buffer->initCheck();
    if (err) {
        LOGE("error creating GraphicBuffer: %s", strerror(-err));
        return NULL;
    }

    Rect rect = buffer->getBounds();
    LOGE("GraphicBuffer information");
    LOGE("width : %d", buffer->getWidth());
    LOGE("height: %d", buffer->getHeight());
    LOGE("stride: %d", buffer->getStride());
    LOGE("usage : 0x%08x", buffer->getUsage());
    LOGE("format: %d", buffer->getPixelFormat());
    LOGE("bounds: (%d,%d) - (%d,%d)", rect.left, rect.top, rect.right, rect.bottom);

    return buffer;
}