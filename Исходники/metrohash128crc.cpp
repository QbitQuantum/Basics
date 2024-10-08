void metrohash128crc_2(const uint8_t * key, uint64_t len, uint32_t seed, uint8_t * out)
{
    static const uint64_t k0 = 0xEE783E2F;
    static const uint64_t k1 = 0xAD07C493;
    static const uint64_t k2 = 0x797A90BB;
    static const uint64_t k3 = 0x2E4B2E1B;

    const uint8_t * ptr = reinterpret_cast<const uint8_t*>(key);
    const uint8_t * const end = ptr + len;
    
    uint64_t v[4];
    
    v[0] = ((static_cast<uint64_t>(seed) - k0) * k3) + len;
    v[1] = ((static_cast<uint64_t>(seed) + k1) * k2) + len;
    
    if (len >= 32)
    {        
        v[2] = ((static_cast<uint64_t>(seed) + k0) * k2) + len;
        v[3] = ((static_cast<uint64_t>(seed) - k1) * k3) + len;

        do
        {
            v[0] ^= _mm_crc32_u64(v[0], read_u64(ptr)); ptr += 8;
            v[1] ^= _mm_crc32_u64(v[1], read_u64(ptr)); ptr += 8;
            v[2] ^= _mm_crc32_u64(v[2], read_u64(ptr)); ptr += 8;
            v[3] ^= _mm_crc32_u64(v[3], read_u64(ptr)); ptr += 8;
        }
        while (ptr <= (end - 32));

        v[2] ^= rotate_right(((v[0] + v[3]) * k0) + v[1], 12) * k1;
        v[3] ^= rotate_right(((v[1] + v[2]) * k1) + v[0], 19) * k0;
        v[0] ^= rotate_right(((v[0] + v[2]) * k0) + v[3], 12) * k1;
        v[1] ^= rotate_right(((v[1] + v[3]) * k1) + v[2], 19) * k0;
    }
    
    if ((end - ptr) >= 16)
    {
        v[0] += read_u64(ptr) * k2; ptr += 8; v[0] = rotate_right(v[0],41) * k3;
        v[1] += read_u64(ptr) * k2; ptr += 8; v[1] = rotate_right(v[1],41) * k3;
        v[0] ^= rotate_right((v[0] * k2) + v[1], 10) * k1;
        v[1] ^= rotate_right((v[1] * k3) + v[0], 10) * k0;
    }
    
    if ((end - ptr) >= 8)
    {
        v[0] += read_u64(ptr) * k2; ptr += 8; v[0] = rotate_right(v[0],34) * k3;
        v[0] ^= rotate_right((v[0] * k2) + v[1], 22) * k1;
    }
    
    if ((end - ptr) >= 4)
    {
        v[1] ^= _mm_crc32_u64(v[0], read_u32(ptr)); ptr += 4;
        v[1] ^= rotate_right((v[1] * k3) + v[0], 14) * k0;
    }
    
    if ((end - ptr) >= 2)
    {
        v[0] ^= _mm_crc32_u64(v[1], read_u16(ptr)); ptr += 2;
        v[0] ^= rotate_right((v[0] * k2) + v[1], 15) * k1;
    }
    
    if ((end - ptr) >= 1)
    {
        v[1] ^= _mm_crc32_u64(v[0], read_u8 (ptr));
        v[1] ^= rotate_right((v[1] * k3) + v[0],  18) * k0;
    }
    
    v[0] += rotate_right((v[0] * k0) + v[1], 15);
    v[1] += rotate_right((v[1] * k1) + v[0], 27);
    v[0] += rotate_right((v[0] * k0) + v[1], 15);
    v[1] += rotate_right((v[1] * k1) + v[0], 27);

    memcpy(out, v, 16);
}