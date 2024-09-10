void FEDisplacementMap::applySoftware()
{
    FilterEffect* in = inputEffect(0);
    FilterEffect* in2 = inputEffect(1);

    ASSERT(m_xChannelSelector != CHANNEL_UNKNOWN);
    ASSERT(m_yChannelSelector != CHANNEL_UNKNOWN);

    Uint8ClampedArray* dstPixelArray = createPremultipliedImageResult();
    if (!dstPixelArray)
        return;

    IntRect effectADrawingRect = requestedRegionOfInputImageData(in->absolutePaintRect());
    RefPtr<Uint8ClampedArray> srcPixelArrayA = in->asPremultipliedImage(effectADrawingRect);

    IntRect effectBDrawingRect = requestedRegionOfInputImageData(in2->absolutePaintRect());
    RefPtr<Uint8ClampedArray> srcPixelArrayB = in2->asUnmultipliedImage(effectBDrawingRect);

    ASSERT(srcPixelArrayA->length() == srcPixelArrayB->length());

    Filter* filter = this->filter();
    IntSize paintSize = absolutePaintRect().size();
    float scaleX = filter->applyHorizontalScale(m_scale);
    float scaleY = filter->applyVerticalScale(m_scale);
    float scaleForColorX = scaleX / 255.0;
    float scaleForColorY = scaleY / 255.0;
    float scaledOffsetX = 0.5 - scaleX * 0.5;
    float scaledOffsetY = 0.5 - scaleY * 0.5;
    int stride = paintSize.width() * 4;
    for (int y = 0; y < paintSize.height(); ++y) {
        int line = y * stride;
        for (int x = 0; x < paintSize.width(); ++x) {
            int dstIndex = line + x * 4;
            int srcX = x + static_cast<int>(scaleForColorX * srcPixelArrayB->item(dstIndex + m_xChannelSelector - 1) + scaledOffsetX);
            int srcY = y + static_cast<int>(scaleForColorY * srcPixelArrayB->item(dstIndex + m_yChannelSelector - 1) + scaledOffsetY);
            for (unsigned channel = 0; channel < 4; ++channel) {
                if (srcX < 0 || srcX >= paintSize.width() || srcY < 0 || srcY >= paintSize.height()) {
                    dstPixelArray->set(dstIndex + channel, static_cast<unsigned char>(0));
                } else {
                    unsigned char pixelValue = srcPixelArrayA->item(srcY * stride + srcX * 4 + channel);
                    dstPixelArray->set(dstIndex + channel, pixelValue);
                }
            }
        }
    }
}