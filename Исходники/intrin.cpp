void convert_dword_to_double(double* result, UINT32 i) {
    __m128d mmin, mmout;
    mmin  = _mm_setzero_pd();
    mmout = _mm_cvtsi32_sd(mmin,i);
    _mm_store_sd(result, mmout);
}