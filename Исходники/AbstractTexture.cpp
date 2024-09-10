/*static*/
void
AbstractTexture::resizeData(unsigned int width,
                            unsigned int height,
                            std::vector<unsigned char>&    data,
                            unsigned int newWidth,
                            unsigned int newHeight,
                            bool resizeSmoothly,
                            std::vector<unsigned char>&    newData)
{
#ifdef DEBUG_TEXTURE
    assert(data.size() == width * height * sizeof(int));
#endif // DEBUG_TEXTURE

    newData.clear();

    if (data.empty() || newWidth == 0 || newHeight == 0)
        return;

    if (newWidth == width && newHeight == height)
    {
        newData.swap(data);
        return;
    }

    const auto    size    = newWidth * newHeight * sizeof(int);
    const float    xFactor = ((float)width - 1.0f)/((float)newWidth - 1.0f);
    const float    yFactor = ((float)height - 1.0f)/((float)newHeight - 1.0f);

    newData.resize(size);

    uint    idx    = 0;
    float    y    = 0.0f;
    for (uint q = 0; q < newHeight; ++q)
    {
        uint        j    = (uint) floorf(y);
        const float dy    = y - (float)j;
        if (j >= height)
            j = height - 1;

        float        x    = 0.0f;
        for (uint p = 0; p < newWidth; ++p)
        {
            uint        i    = (uint)floorf(x);
            if (i >= width)
                i = width - 1;

            const uint ijTL    = (i + width * j) << 2;

            if (resizeSmoothly)
            {
                // bilinear interpolation

                const float dx    = x - (float)i;
                const float dxy = dx * dy;

                const uint ijTR    = i < width - 1                        ? ijTL + 4                        : ijTL;
                const uint ijBL = j < height - 1                        ? ijTL + (width << 2)            : ijTL;
                const uint ijBR = (i < width - 1) && (j < height - 1)    ? ijTL + ((width + 1) << 2)    : ijTL;

                const float    wTL    = 1.0f - dx - dy + dxy;
                const float wTR = dx - dxy;
                const float wBL = dy - dxy;
                const float wBR = dxy;

                for (uint k = 0; k < 4; ++k)
                {
                    const float color = wTL * data[ijTL + k] +
                        wTR * data[ijTR + k] +
                        wBL * data[ijBL + k] +
                        wBR * data[ijBR + k];

                    newData[idx + k] = (unsigned char)floorf(color);
                }
            }
            else
            {
                // nearest pixel color

                for (uint k = 0; k < 4; ++k)
                    newData[idx + k] = data[ijTL + k];
            }

            idx    += 4;
            x    += xFactor;
        }
        y += yFactor;
    }

#ifdef DEBUG_TEXTURE
    assert(newData.size() == newWidth * newHeight * sizeof(int));
#endif // DEBUG_TEXTURE
}