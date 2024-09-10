void computeDensitySSE(const double * const currentCell, double *density)
{
    __m128d vsum = _mm_set1_pd(0.0);
    int i;
    for (i = 0; i < PARAMQ - 1; i += 2)
    {
        __m128d v = _mm_loadu_pd(&currentCell[i]);
        vsum = _mm_add_pd(vsum, v);
    }
    vsum = _mm_hadd_pd(vsum, vsum);
    _mm_storeh_pd(density, vsum);
    if (i < PARAMQ)
    {
        *density += currentCell[i];
    }
}