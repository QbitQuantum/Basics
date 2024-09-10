int xm_popcount(XMM x)
{
    return _mm_popcnt_u64(((uint64_t const*)&x)[0])
         + _mm_popcnt_u64(((uint64_t const*)&x)[0]);
}