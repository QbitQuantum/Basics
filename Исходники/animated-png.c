static inline int clzll(unsigned long long input_num) {
    unsigned long index;
#ifdef _WIN64
    _BitScanReverse64(&index, input_num);
#else  // if we must support 32-bit Windows
    if (input_num > 0xFFFFFFF) {
        _BitScanReverse(&index, (uint32_t)(input_num >> 32));
    } else {