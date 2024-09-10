/// SwapByteOrder_16 - This function returns a byte-swapped representation of
/// the 16-bit argument.
inline uint16_t SwapByteOrder_16(uint16_t value) {
#if defined(_MSC_VER) && !defined(_DEBUG)
    // The DLL version of the runtime lacks these functions (bug!?), but in a
    // release build they're replaced with BSWAP instructions anyway.
    return _byteswap_ushort(value);
#else
    uint16_t Hi = value << 8;
    uint16_t Lo = value >> 8;
    return Hi | Lo;
#endif
}