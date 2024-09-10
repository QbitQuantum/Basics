template<> void momentsInTile<uchar, int, int>( const cv::Mat& img, double* moments )
{
    typedef uchar T;
    typedef int WT;
    typedef int MT;
    Size size = img.size();
    int y;
    MT mom[10] = {0,0,0,0,0,0,0,0,0,0};
    bool useSIMD = checkHardwareSupport(CV_CPU_SSE2);

    for( y = 0; y < size.height; y++ )
    {
        const T* ptr = img.ptr<T>(y);
        int x0 = 0, x1 = 0, x2 = 0, x3 = 0, x = 0;

        if( useSIMD )
        {
            __m128i qx_init = _mm_setr_epi16(0, 1, 2, 3, 4, 5, 6, 7);
            __m128i dx = _mm_set1_epi16(8);
            __m128i z = _mm_setzero_si128(), qx0 = z, qx1 = z, qx2 = z, qx3 = z, qx = qx_init;

            for( ; x <= size.width - 8; x += 8 )
            {
                __m128i p = _mm_unpacklo_epi8(_mm_loadl_epi64((const __m128i*)(ptr + x)), z);
                qx0 = _mm_add_epi32(qx0, _mm_sad_epu8(p, z));
                __m128i px = _mm_mullo_epi16(p, qx);
                __m128i sx = _mm_mullo_epi16(qx, qx);
                qx1 = _mm_add_epi32(qx1, _mm_madd_epi16(p, qx));
                qx2 = _mm_add_epi32(qx2, _mm_madd_epi16(p, sx));
                qx3 = _mm_add_epi32(qx3, _mm_madd_epi16(px, sx));

                qx = _mm_add_epi16(qx, dx);
            }
            int CV_DECL_ALIGNED(16) buf[4];
            _mm_store_si128((__m128i*)buf, qx0);
            x0 = buf[0] + buf[1] + buf[2] + buf[3];
            _mm_store_si128((__m128i*)buf, qx1);
            x1 = buf[0] + buf[1] + buf[2] + buf[3];
            _mm_store_si128((__m128i*)buf, qx2);
            x2 = buf[0] + buf[1] + buf[2] + buf[3];
            _mm_store_si128((__m128i*)buf, qx3);
            x3 = buf[0] + buf[1] + buf[2] + buf[3];
        }

        for( ; x < size.width; x++ )
        {
            WT p = ptr[x];
            WT xp = x * p, xxp;

            x0 += p;
            x1 += xp;
            xxp = xp * x;
            x2 += xxp;
            x3 += xxp * x;
        }

        WT py = y * x0, sy = y*y;

        mom[9] += ((MT)py) * sy;  // m03
        mom[8] += ((MT)x1) * sy;  // m12
        mom[7] += ((MT)x2) * y;  // m21
        mom[6] += x3;             // m30
        mom[5] += x0 * sy;        // m02
        mom[4] += x1 * y;         // m11
        mom[3] += x2;             // m20
        mom[2] += py;             // m01
        mom[1] += x1;             // m10
        mom[0] += x0;             // m00
    }

    for(int x = 0; x < 10; x++ )
        moments[x] = (double)mom[x];
}