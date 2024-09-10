        // 按 bit 数前面 0 的个数
        int Clz(size_t x)
        {
#ifdef _MSC_VER
            unsigned long r = 0;
# ifdef XXLIB_64BIT
            _BitScanReverse64(&r, x);
            return 63 - r;
# else
            _BitScanReverse(&r, x);
            return 31 - r;
# endif
#else
# ifdef XXLIB_64BIT
            return __builtin_clzl(x);
# else
            return __builtin_clz(x);
# endif
#endif
        }