void CRC32C_Update_SSE42(const byte *s, size_t n, word32& c)
{
    for(; !IsAligned<word32>(s) && n > 0; s++, n--)
        c = _mm_crc32_u8(c, *s);

    for(; n > 4; s+=4, n-=4)
        c = _mm_crc32_u32(c, *(const word32 *)(void*)s);

    for(; n > 0; s++, n--)
        c = _mm_crc32_u8(c, *s);
}