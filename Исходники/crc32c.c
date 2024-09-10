/**
 * Calculates 32-bit CRC for the specified input string
 *
 * @return A 32-bit unsigned integer representing the CRC
 */
uint32_t calculateCRC32C(uint32_t crc, const char *buf, size_t len) {
    // If the string is empty, return 0
    if (len == 0) {
        return crc;
    }


    // XOR the initial CRC with INT_MAX
    crc ^= 0xFFFFFFFF;


    // Align the input to the word boundary
    for (; (len > 0) && ((size_t)buf & ALIGN_MASK); len--, buf++) {
        crc = _mm_crc32_u8(crc, *buf);
    }


    // Blast off the CRC32 calculation
#ifdef __x86_64__
    CALC_CRC(_mm_crc32_u64, crc, uint64_t, buf, len);
#endif
    CALC_CRC(_mm_crc32_u32, crc, uint32_t, buf, len);
    CALC_CRC(_mm_crc32_u16, crc, uint16_t, buf, len);
    CALC_CRC(_mm_crc32_u8, crc, uint8_t, buf, len);


    // Post-process the crc
    return (crc ^= 0xFFFFFFFF);
}