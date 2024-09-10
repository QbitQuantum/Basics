QT_BEGIN_NAMESPACE

bool convert_ARGB_to_ARGB_PM_inplace_sse2(QImageData *data, Qt::ImageConversionFlags)
{
    Q_ASSERT(data->format == QImage::Format_ARGB32);

    // extra pixels on each line
    const int spare = data->width & 3;
    // width in pixels of the pad at the end of each line
    const int pad = (data->bytes_per_line >> 2) - data->width;
    const int iter = data->width >> 2;
    int height = data->height;

    const __m128i alphaMask = _mm_set1_epi32(0xff000000);
    const __m128i nullVector = _mm_setzero_si128();
    const __m128i half = _mm_set1_epi16(0x80);
    const __m128i colorMask = _mm_set1_epi32(0x00ff00ff);

    __m128i *d = reinterpret_cast<__m128i*>(data->data);
    while (height--) {
        const __m128i *end = d + iter;

        for (; d != end; ++d) {
            const __m128i srcVector = _mm_loadu_si128(d);
            const __m128i srcVectorAlpha = _mm_and_si128(srcVector, alphaMask);
            if (_mm_movemask_epi8(_mm_cmpeq_epi32(srcVectorAlpha, alphaMask)) == 0xffff) {
                // opaque, data is unchanged
            } else if (_mm_movemask_epi8(_mm_cmpeq_epi32(srcVectorAlpha, nullVector)) == 0xffff) {
                // fully transparent
                _mm_storeu_si128(d, nullVector);
            } else {
                __m128i alphaChannel = _mm_srli_epi32(srcVector, 24);
                alphaChannel = _mm_or_si128(alphaChannel, _mm_slli_epi32(alphaChannel, 16));

                __m128i result;
                BYTE_MUL_SSE2(result, srcVector, alphaChannel, colorMask, half);
                result = _mm_or_si128(_mm_andnot_si128(alphaMask, result), srcVectorAlpha);
                _mm_storeu_si128(d, result);
            }
        }

        QRgb *p = reinterpret_cast<QRgb*>(d);
        QRgb *pe = p+spare;
        for (; p != pe; ++p) {
            if (*p < 0x00ffffff)
                *p = 0;
            else if (*p < 0xff000000)
                *p = PREMUL(*p);
        }

        d = reinterpret_cast<__m128i*>(p+pad);
    }

    data->format = QImage::Format_ARGB32_Premultiplied;
    return true;
}