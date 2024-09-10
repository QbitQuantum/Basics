inline bitcount_t flog2(uint64_t v)
{
#if defined(_M_X64) || defined(_M_ARM) || defined(_M_ARM64)
    unsigned long i;
    _BitScanReverse64(&i, v);
    return i;
#else
    // 32-bit x86
    uint32_t high = v >> 32;
    uint32_t low  = uint32_t(v);
    return high ? 32+flog2(high) : flog2(low);
#endif
}