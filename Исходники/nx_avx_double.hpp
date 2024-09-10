    inline vector4d fma(const vector4d& x, const vector4d& y, const vector4d& z)
    {
#ifdef __FMA__
        return _mm256_fmadd_pd(x, y, z);
#else
        return x * y + z;
#endif
    }