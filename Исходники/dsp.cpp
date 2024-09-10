    //----------------------------------------------------------------------------
    void conv_Short1ToFloat1(void* dst, const void* s, s32 numSamples)
    {
        LSfloat* d = reinterpret_cast<LSfloat*>(dst);
        const LSshort* src = reinterpret_cast<const LSshort*>(s);

        s32 num = numSamples >> 3; //8個のshortをまとめて処理
        s32 offset = num << 3;
        s32 rem = numSamples - offset;

        const __m128i izero = _mm_setzero_si128();
        const __m128 fcoff = _mm_set1_ps(1.0f/32767.0f);

        const LSshort* p = src;
        LSfloat* q = d;
        for(s32 i=0; i<num; ++i){
            //32bit浮動小数点r0, r1に変換
            __m128i t0 = _mm_loadu_si128((const __m128i*)p);
            __m128i t1 = _mm_cmpgt_epi16(izero, t0);
            __m128 r0 = _mm_cvtepi32_ps(_mm_unpackhi_epi16(t0, t1));
            __m128 r1 = _mm_cvtepi32_ps(_mm_unpacklo_epi16(t0, t1));

            r0 = _mm_mul_ps(r0, fcoff);
            r1 = _mm_mul_ps(r1, fcoff);
            _mm_storeu_ps((q+0), r1);
            _mm_storeu_ps((q+4), r0);
            p += 8;
            q += 8;
        }

        for(s32 i=0; i<rem; ++i){
            q[i] = toFloat(p[i]);
        }
    }