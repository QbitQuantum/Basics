//Return the number of bits including the first non-zero bit.  Undefined if value == 0
inline unsigned getMostSignificantBit(unsigned value)
{
    dbgassertex(value != 0);
#if defined(__GNUC__)
    return (sizeof(unsigned)*8) - __builtin_clz(value);
#elif defined (_WIN32)
    unsigned long index;
    _BitScanReverse(&index, value);
    return (unsigned)index+1;
#else
    unsigned mask = 1U << ((sizeof(unsigned)*8)-1);
    unsigned i;
    for (i=0; i < sizeof(unsigned)*8; i++)
    {
        if (value & mask)
            return sizeof(unsigned)*8-i;
        mask = mask >> 1;
    }
    return 0;
#endif
}