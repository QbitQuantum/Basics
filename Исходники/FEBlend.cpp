void FEBlend::apply()
{
    if (hasResult())
        return;
    FilterEffect* in = inputEffect(0);
    FilterEffect* in2 = inputEffect(1);
    in->apply();
    in2->apply();
    if (!in->hasResult() || !in2->hasResult())
        return;

    ASSERT(m_mode > FEBLEND_MODE_UNKNOWN);
    ASSERT(m_mode <= FEBLEND_MODE_LIGHTEN);

    ByteArray* dstPixelArray = createPremultipliedImageResult();
    if (!dstPixelArray)
        return;

    IntRect effectADrawingRect = requestedRegionOfInputImageData(in->absolutePaintRect());
    RefPtr<ByteArray> srcPixelArrayA = in->asPremultipliedImage(effectADrawingRect);

    IntRect effectBDrawingRect = requestedRegionOfInputImageData(in2->absolutePaintRect());
    RefPtr<ByteArray> srcPixelArrayB = in2->asPremultipliedImage(effectBDrawingRect);

    // Keep synchronized with BlendModeType
    static const BlendType callEffect[] = {unknown, normal, multiply, screen, darken, lighten};

    unsigned pixelArrayLength = srcPixelArrayA->length();
    ASSERT(pixelArrayLength == srcPixelArrayB->length());
    for (unsigned pixelOffset = 0; pixelOffset < pixelArrayLength; pixelOffset += 4) {
        unsigned char alphaA = srcPixelArrayA->get(pixelOffset + 3);
        unsigned char alphaB = srcPixelArrayB->get(pixelOffset + 3);
        for (unsigned channel = 0; channel < 3; ++channel) {
            unsigned char colorA = srcPixelArrayA->get(pixelOffset + channel);
            unsigned char colorB = srcPixelArrayB->get(pixelOffset + channel);

            unsigned char result = (*callEffect[m_mode])(colorA, colorB, alphaA, alphaB);
            dstPixelArray->set(pixelOffset + channel, result);
        }
        unsigned char alphaR = 255 - ((255 - alphaA) * (255 - alphaB)) / 255;
        dstPixelArray->set(pixelOffset + 3, alphaR);
    }
}