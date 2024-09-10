static CYTHON_INLINE struct ZZ* mat_ZZ_determinant(const mat_ZZ* x, long deterministic)
{
    ZZ* d = new ZZ();
    determinant(*d, *x, deterministic);
    return d;
}