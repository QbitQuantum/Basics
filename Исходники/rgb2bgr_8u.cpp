// =============================================================
// ====================== RGBX2BGRX_32F ========================
// =============================================================
void _rgbx2bgrx_32f(const float* _src, float* _dest, unsigned int _width,
                    unsigned int _pitchs, unsigned int _pitchd,
                    unsigned int _start, unsigned int _stop) {

#ifdef USE_SSE

    const unsigned int widthz = (_pitchs/8);

    // Get start positions for buffers
    const float* tsrc;
    float* tdest;

    for( unsigned int y=_start; y<=_stop; ++y ) {
        tsrc = _src+(y*_pitchs);
        tdest = _dest+(y*_pitchd);
        for( unsigned int x=0; x<widthz; ++x ) {

#ifdef USE_AVX1
            const __m256 v0 = _mm256_load_ps(tsrc);
            tsrc+=8;

            __m256 r0 = _mm256_permute_ps(v0,0xc6);

            _mm256_store_ps(tdest, r0 );
            tdest+=8;
#else // NOT TESTED

            const __m128 v0 = _mm_load_ps(tsrc);
            tsrc+=4;
            const __m128 v1 = _mm_load_ps(tsrc);
            tsrc+=4;

            //__m128 r0 = _mm_shuffle_ps(v0,0xc6);
            //__m128 r1 = _mm_shuffle_ps(v1,0xc6);

            //_mm_store_ps(tdest, r0 ); tdest+=4;
            //_mm_store_ps(tdest, r1 ); tdest+=4;
#endif

        }
    }

#else
    const float* tsrc;
    float* tdest;

    for( unsigned int y=_start; y<=_stop; ++y ) {
        tsrc = _src+(y*_pitchs);
        tdest = _dest+(y*_pitchd);
        for( unsigned int x=0; x<_width; ++x ) {
            float t = tsrc[4*x];
            tdest[4*x] = tsrc[4*x+2];
            tdest[4*x+2] = t;
        }
    }
#endif
}