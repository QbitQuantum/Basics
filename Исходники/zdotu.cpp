 double zdotu_soa(
                const int    N,
                const double* da,
                const double* db,
                const int    ix,
                const double* dc,
                const double* dd,
                const int    iy,
                double*  res
                )
{
        __m256d ymm0;
        __m256d ymm1;
        __m256d ymm2;
        __m256d ymm3;
        __m256d ymm4 = _mm256_setzero_pd();
        __m256d ymm5 = _mm256_setzero_pd();
        //
        int ii;
//#pragma unroll
        for(ii = 0; ii < N/4; ii++)
        {
		_mm_prefetch((const char*) da + 0x200, 1);
		_mm_prefetch((const char*) db + 0x200, 1);
		_mm_prefetch((const char*) dc + 0x200, 1);
		_mm_prefetch((const char*) dd + 0x200, 1);
                //IACA_START;
                // 8*4*4 = 128 bytes
                ymm0 = _mm256_loadu_pd(da + 4*ii);
                ymm1 = _mm256_loadu_pd(db + 4*ii);
                ymm2 = _mm256_loadu_pd(dc + 4*ii);
                ymm3 = _mm256_loadu_pd(dd + 4*ii);
                // 2*4*4 = 32 flops
                ymm4 = _mm256_fmsub_pd(ymm0, ymm2, _mm256_fmsub_pd(ymm1, ymm3, ymm4));
                ymm5 = _mm256_fmadd_pd(ymm0, ymm3, _mm256_fmadd_pd(ymm1, ymm2, ymm5));
		// flops/bute ratio = 1/4
                //IACA_END
        }
        double* re = (double*)&ymm4;
        double* im = (double*)&ymm5;
	//
        res[0] = re[0] + re[1] + re[2] + re[3];
        res[1] = im[0] + im[1] + im[2] + im[3];
}