void FEMorphology::platformApplyGeneric(PaintingData* paintingData, int yStart, int yEnd)
{
    Uint8ClampedArray* srcPixelArray = paintingData->srcPixelArray;
    Uint8ClampedArray* dstPixelArray = paintingData->dstPixelArray;
    const int width = paintingData->width;
    const int height = paintingData->height;
    const int effectWidth = width * 4;
    const int radiusX = paintingData->radiusX;
    const int radiusY = paintingData->radiusY;

    Vector<unsigned char> extrema;
    for (int y = yStart; y < yEnd; ++y) {
        int extremaStartY = std::max(0, y - radiusY);
        int extremaEndY = std::min(height - 1, y + radiusY);
        for (unsigned int clrChannel = 0; clrChannel < 4; ++clrChannel) {
            extrema.clear();
            // Compute extremas for each columns
            for (int x = 0; x <= radiusX; ++x) {
                unsigned char columnExtrema = srcPixelArray->item(extremaStartY * effectWidth + 4 * x + clrChannel);
                for (int eY = extremaStartY + 1; eY < extremaEndY; ++eY) {
                    unsigned char pixel = srcPixelArray->item(eY * effectWidth + 4 * x + clrChannel);
                    if ((m_type == FEMORPHOLOGY_OPERATOR_ERODE && pixel <= columnExtrema)
                        || (m_type == FEMORPHOLOGY_OPERATOR_DILATE && pixel >= columnExtrema)) {
                        columnExtrema = pixel;
                    }
                }

                extrema.append(columnExtrema);
            }

            // Kernel is filled, get extrema of next column
            for (int x = 0; x < width; ++x) {
                const int endX = std::min(x + radiusX, width - 1);
                unsigned char columnExtrema = srcPixelArray->item(extremaStartY * effectWidth + endX * 4 + clrChannel);
                for (int i = extremaStartY + 1; i <= extremaEndY; ++i) {
                    unsigned char pixel = srcPixelArray->item(i * effectWidth + endX * 4 + clrChannel);
                    if ((m_type == FEMORPHOLOGY_OPERATOR_ERODE && pixel <= columnExtrema)
                        || (m_type == FEMORPHOLOGY_OPERATOR_DILATE && pixel >= columnExtrema))
                        columnExtrema = pixel;
                }
                if (x - radiusX >= 0)
                    extrema.remove(0);
                if (x + radiusX <= width)
                    extrema.append(columnExtrema);

                unsigned char entireExtrema = extrema[0];
                for (unsigned kernelIndex = 1; kernelIndex < extrema.size(); ++kernelIndex) {
                    if ((m_type == FEMORPHOLOGY_OPERATOR_ERODE && extrema[kernelIndex] <= entireExtrema)
                        || (m_type == FEMORPHOLOGY_OPERATOR_DILATE && extrema[kernelIndex] >= entireExtrema))
                        entireExtrema = extrema[kernelIndex];
                }
                dstPixelArray->set(y * effectWidth + 4 * x + clrChannel, entireExtrema);
            }
        }
    }
}