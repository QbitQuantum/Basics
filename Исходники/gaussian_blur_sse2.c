static void GF_FUNC_ALIGN VS_CC
proc_8bit(int radius, float *kernel, const uint8_t *srcp, float *buff,
          float *dstp, int width, int height, int src_stride, int dst_stride)
{
    int length = radius * 2 + 1;
    const uint8_t *p[17];
    for (int i = -radius; i <= radius; i++) {
        p[i + radius] = srcp + abs(i) * src_stride;
    }

    __m128i zero = _mm_setzero_si128();

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x += 16) {
            __m128 sum[4];
            sum[0] = _mm_setzero_ps();
            sum[1] = _mm_setzero_ps();
            sum[2] = _mm_setzero_ps();
            sum[3] = _mm_setzero_ps();
            
            for (int i = 0; i < length; i++) {
                __m128 f[4];
                __m128i xmm0 = _mm_load_si128((__m128i *)(p[i] + x));
                __m128i xmm1 = _mm_unpackhi_epi8(xmm0, zero);
                xmm0 = _mm_unpacklo_epi8(xmm0, zero);
                f[0] = _mm_cvtepi32_ps(_mm_unpacklo_epi16(xmm0, zero));
                f[1] = _mm_cvtepi32_ps(_mm_unpackhi_epi16(xmm0, zero));
                f[2] = _mm_cvtepi32_ps(_mm_unpacklo_epi16(xmm1, zero));
                f[3] = _mm_cvtepi32_ps(_mm_unpackhi_epi16(xmm1, zero));
                __m128 k = _mm_set1_ps(kernel[i]);
                
                for (int j = 0; j < 4; j++) {
                    sum[j] = _mm_add_ps(sum[j], _mm_mul_ps(k, f[j]));
                }
            }
            _mm_store_ps(buff + x,      sum[0]);
            _mm_store_ps(buff + x +  4, sum[1]);
            _mm_store_ps(buff + x +  8, sum[2]);
            _mm_store_ps(buff + x + 12, sum[3]);
        }
        proc_horizontal(buff, radius, length, width, kernel, dstp);
        
        for (int i = 0; i < length - 1; i++) {
            p[i] = p[i + 1];
        }
        p[length - 1] += (y < height - radius - 1 ? 1 : -1) * src_stride;
        dstp += dst_stride;
    }
}