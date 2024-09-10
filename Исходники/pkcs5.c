void _stdcall sha512_pkcs5_2(int i_count, const void *pwd, size_t pwd_len, const char *salt, size_t salt_len, char *dk, size_t dklen)
{
    unsigned char buff[128];
    unsigned char blk[SHA512_DIGEST_SIZE];
    unsigned char hmac[SHA512_DIGEST_SIZE];
    unsigned long block = 1;
    size_t c_len;
    int    j, i;

    while (dklen != 0)
    {
        // first interation
        memcpy(buff, salt, salt_len);
        ((unsigned long*)(buff + salt_len))[0] = _byteswap_ulong(block);
        sha512_hmac(pwd, pwd_len, buff, salt_len + 4, (char*)hmac);
        memcpy(blk, hmac, SHA512_DIGEST_SIZE);

        // next interations
        for (i = 1; i < i_count; i++)
        {
            sha512_hmac(pwd, pwd_len, hmac, SHA512_DIGEST_SIZE, (char*)hmac);

            for (j = 0; j < (SHA512_DIGEST_SIZE / 4); j++) {
                ((unsigned long*)blk)[j] ^= ((unsigned long*)hmac)[j];
            }
        }

        memcpy(dk, blk, (c_len = dklen < SHA512_DIGEST_SIZE ? dklen : SHA512_DIGEST_SIZE));
        dk += c_len;
        dklen -= c_len;
        block++;
    }

    // test buffers size alignment at compile-time
    static_assert( !(sizeof(buff) % sizeof(unsigned long)), "sizeof must be 4 byte aligned");
    static_assert( !(sizeof(blk) % sizeof(unsigned long)), "sizeof must be 4 byte aligned");
    static_assert( !(sizeof(hmac) % sizeof(unsigned long)), "sizeof must be 4 byte aligned");

    // prevent leaks
    __stosd((unsigned long*)&buff, 0, (sizeof(buff) / sizeof(unsigned long)));
    __stosd((unsigned long*)&blk, 0, (sizeof(blk) / sizeof(unsigned long)));
    __stosd((unsigned long*)&hmac, 0, (sizeof(hmac) / sizeof(unsigned long)));
}