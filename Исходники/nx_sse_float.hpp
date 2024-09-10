    inline vector4f fma(const vector4f& x, const vector4f& y, const vetcor4f& z)
    {
#ifdef __FMA__
        return _mm_fmadd_ps(x, y, z);
#else
        return x * y + z;
#endif
    }