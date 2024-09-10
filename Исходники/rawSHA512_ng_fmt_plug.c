static void crypt_all (int count)
#endif
{
#if FMT_MAIN_VERSION > 10
    int count = *pcount;
#endif
    int index = 0;

#ifdef _OPENMP
#pragma omp parallel for
    for (index = 0; index < count; index += 2)
#endif
    {
        int i;

        __m128i a, b, c, d, e, f, g, h;
        __m128i w[80], tmp1, tmp2;


        for (i = 0; i < 14; i += 2) {
            GATHER (tmp1, saved_key, i);
            GATHER (tmp2, saved_key, i + 1);
            SWAP_ENDIAN (tmp1);
            SWAP_ENDIAN (tmp2);
            w[i] = tmp1;
            w[i + 1] = tmp2;
        }
        GATHER (tmp1, saved_key, 14);
        SWAP_ENDIAN (tmp1);
        w[14] = tmp1;
        GATHER (w[15], saved_key, 15);
        for (i = 16; i < 80; i++) R(i);

        a = _mm_set1_epi64x (0x6a09e667f3bcc908ULL);
        b = _mm_set1_epi64x (0xbb67ae8584caa73bULL);
        c = _mm_set1_epi64x (0x3c6ef372fe94f82bULL);
        d = _mm_set1_epi64x (0xa54ff53a5f1d36f1ULL);
        e = _mm_set1_epi64x (0x510e527fade682d1ULL);
        f = _mm_set1_epi64x (0x9b05688c2b3e6c1fULL);
        g = _mm_set1_epi64x (0x1f83d9abfb41bd6bULL);
        h = _mm_set1_epi64x (0x5be0cd19137e2179ULL);

        SHA512_STEP(a, b, c, d, e, f, g, h,  0, 0x428a2f98d728ae22ULL);
        SHA512_STEP(h, a, b, c, d, e, f, g,  1, 0x7137449123ef65cdULL);
        SHA512_STEP(g, h, a, b, c, d, e, f,  2, 0xb5c0fbcfec4d3b2fULL);
        SHA512_STEP(f, g, h, a, b, c, d, e,  3, 0xe9b5dba58189dbbcULL);
        SHA512_STEP(e, f, g, h, a, b, c, d,  4, 0x3956c25bf348b538ULL);
        SHA512_STEP(d, e, f, g, h, a, b, c,  5, 0x59f111f1b605d019ULL);
        SHA512_STEP(c, d, e, f, g, h, a, b,  6, 0x923f82a4af194f9bULL);
        SHA512_STEP(b, c, d, e, f, g, h, a,  7, 0xab1c5ed5da6d8118ULL);
        SHA512_STEP(a, b, c, d, e, f, g, h,  8, 0xd807aa98a3030242ULL);
        SHA512_STEP(h, a, b, c, d, e, f, g,  9, 0x12835b0145706fbeULL);
        SHA512_STEP(g, h, a, b, c, d, e, f, 10, 0x243185be4ee4b28cULL);
        SHA512_STEP(f, g, h, a, b, c, d, e, 11, 0x550c7dc3d5ffb4e2ULL);
        SHA512_STEP(e, f, g, h, a, b, c, d, 12, 0x72be5d74f27b896fULL);
        SHA512_STEP(d, e, f, g, h, a, b, c, 13, 0x80deb1fe3b1696b1ULL);
        SHA512_STEP(c, d, e, f, g, h, a, b, 14, 0x9bdc06a725c71235ULL);
        SHA512_STEP(b, c, d, e, f, g, h, a, 15, 0xc19bf174cf692694ULL);

        SHA512_STEP(a, b, c, d, e, f, g, h, 16, 0xe49b69c19ef14ad2ULL);
        SHA512_STEP(h, a, b, c, d, e, f, g, 17, 0xefbe4786384f25e3ULL);
        SHA512_STEP(g, h, a, b, c, d, e, f, 18, 0x0fc19dc68b8cd5b5ULL);
        SHA512_STEP(f, g, h, a, b, c, d, e, 19, 0x240ca1cc77ac9c65ULL);
        SHA512_STEP(e, f, g, h, a, b, c, d, 20, 0x2de92c6f592b0275ULL);
        SHA512_STEP(d, e, f, g, h, a, b, c, 21, 0x4a7484aa6ea6e483ULL);
        SHA512_STEP(c, d, e, f, g, h, a, b, 22, 0x5cb0a9dcbd41fbd4ULL);
        SHA512_STEP(b, c, d, e, f, g, h, a, 23, 0x76f988da831153b5ULL);
        SHA512_STEP(a, b, c, d, e, f, g, h, 24, 0x983e5152ee66dfabULL);
        SHA512_STEP(h, a, b, c, d, e, f, g, 25, 0xa831c66d2db43210ULL);
        SHA512_STEP(g, h, a, b, c, d, e, f, 26, 0xb00327c898fb213fULL);
        SHA512_STEP(f, g, h, a, b, c, d, e, 27, 0xbf597fc7beef0ee4ULL);
        SHA512_STEP(e, f, g, h, a, b, c, d, 28, 0xc6e00bf33da88fc2ULL);
        SHA512_STEP(d, e, f, g, h, a, b, c, 29, 0xd5a79147930aa725ULL);
        SHA512_STEP(c, d, e, f, g, h, a, b, 30, 0x06ca6351e003826fULL);
        SHA512_STEP(b, c, d, e, f, g, h, a, 31, 0x142929670a0e6e70ULL);

        SHA512_STEP(a, b, c, d, e, f, g, h, 32, 0x27b70a8546d22ffcULL);
        SHA512_STEP(h, a, b, c, d, e, f, g, 33, 0x2e1b21385c26c926ULL);
        SHA512_STEP(g, h, a, b, c, d, e, f, 34, 0x4d2c6dfc5ac42aedULL);
        SHA512_STEP(f, g, h, a, b, c, d, e, 35, 0x53380d139d95b3dfULL);
        SHA512_STEP(e, f, g, h, a, b, c, d, 36, 0x650a73548baf63deULL);
        SHA512_STEP(d, e, f, g, h, a, b, c, 37, 0x766a0abb3c77b2a8ULL);
        SHA512_STEP(c, d, e, f, g, h, a, b, 38, 0x81c2c92e47edaee6ULL);
        SHA512_STEP(b, c, d, e, f, g, h, a, 39, 0x92722c851482353bULL);
        SHA512_STEP(a, b, c, d, e, f, g, h, 40, 0xa2bfe8a14cf10364ULL);
        SHA512_STEP(h, a, b, c, d, e, f, g, 41, 0xa81a664bbc423001ULL);
        SHA512_STEP(g, h, a, b, c, d, e, f, 42, 0xc24b8b70d0f89791ULL);
        SHA512_STEP(f, g, h, a, b, c, d, e, 43, 0xc76c51a30654be30ULL);
        SHA512_STEP(e, f, g, h, a, b, c, d, 44, 0xd192e819d6ef5218ULL);
        SHA512_STEP(d, e, f, g, h, a, b, c, 45, 0xd69906245565a910ULL);
        SHA512_STEP(c, d, e, f, g, h, a, b, 46, 0xf40e35855771202aULL);
        SHA512_STEP(b, c, d, e, f, g, h, a, 47, 0x106aa07032bbd1b8ULL);

        SHA512_STEP(a, b, c, d, e, f, g, h, 48, 0x19a4c116b8d2d0c8ULL);
        SHA512_STEP(h, a, b, c, d, e, f, g, 49, 0x1e376c085141ab53ULL);
        SHA512_STEP(g, h, a, b, c, d, e, f, 50, 0x2748774cdf8eeb99ULL);
        SHA512_STEP(f, g, h, a, b, c, d, e, 51, 0x34b0bcb5e19b48a8ULL);
        SHA512_STEP(e, f, g, h, a, b, c, d, 52, 0x391c0cb3c5c95a63ULL);
        SHA512_STEP(d, e, f, g, h, a, b, c, 53, 0x4ed8aa4ae3418acbULL);
        SHA512_STEP(c, d, e, f, g, h, a, b, 54, 0x5b9cca4f7763e373ULL);
        SHA512_STEP(b, c, d, e, f, g, h, a, 55, 0x682e6ff3d6b2b8a3ULL);
        SHA512_STEP(a, b, c, d, e, f, g, h, 56, 0x748f82ee5defb2fcULL);
        SHA512_STEP(h, a, b, c, d, e, f, g, 57, 0x78a5636f43172f60ULL);
        SHA512_STEP(g, h, a, b, c, d, e, f, 58, 0x84c87814a1f0ab72ULL);
        SHA512_STEP(f, g, h, a, b, c, d, e, 59, 0x8cc702081a6439ecULL);
        SHA512_STEP(e, f, g, h, a, b, c, d, 60, 0x90befffa23631e28ULL);
        SHA512_STEP(d, e, f, g, h, a, b, c, 61, 0xa4506cebde82bde9ULL);
        SHA512_STEP(c, d, e, f, g, h, a, b, 62, 0xbef9a3f7b2c67915ULL);
        SHA512_STEP(b, c, d, e, f, g, h, a, 63, 0xc67178f2e372532bULL);

        SHA512_STEP(a, b, c, d, e, f, g, h, 64, 0xca273eceea26619cULL);
        SHA512_STEP(h, a, b, c, d, e, f, g, 65, 0xd186b8c721c0c207ULL);
        SHA512_STEP(g, h, a, b, c, d, e, f, 66, 0xeada7dd6cde0eb1eULL);
        SHA512_STEP(f, g, h, a, b, c, d, e, 67, 0xf57d4f7fee6ed178ULL);
        SHA512_STEP(e, f, g, h, a, b, c, d, 68, 0x06f067aa72176fbaULL);
        SHA512_STEP(d, e, f, g, h, a, b, c, 69, 0x0a637dc5a2c898a6ULL);
        SHA512_STEP(c, d, e, f, g, h, a, b, 70, 0x113f9804bef90daeULL);
        SHA512_STEP(b, c, d, e, f, g, h, a, 71, 0x1b710b35131c471bULL);
        SHA512_STEP(a, b, c, d, e, f, g, h, 72, 0x28db77f523047d84ULL);
        SHA512_STEP(h, a, b, c, d, e, f, g, 73, 0x32caab7b40c72493ULL);
        SHA512_STEP(g, h, a, b, c, d, e, f, 74, 0x3c9ebe0a15c9bebcULL);
        SHA512_STEP(f, g, h, a, b, c, d, e, 75, 0x431d67c49c100d4cULL);
        SHA512_STEP(e, f, g, h, a, b, c, d, 76, 0x4cc5d4becb3e42b6ULL);
        SHA512_STEP(d, e, f, g, h, a, b, c, 77, 0x597f299cfc657e2aULL);
        SHA512_STEP(c, d, e, f, g, h, a, b, 78, 0x5fcb6fab3ad6faecULL);
        SHA512_STEP(b, c, d, e, f, g, h, a, 79, 0x6c44198c4a475817ULL);

        _mm_store_si128 ((__m128i *) &crypt_key[0][index], a);
        _mm_store_si128 ((__m128i *) &crypt_key[1][index], b);
        _mm_store_si128 ((__m128i *) &crypt_key[2][index], c);
        _mm_store_si128 ((__m128i *) &crypt_key[3][index], d);
        _mm_store_si128 ((__m128i *) &crypt_key[4][index], e);
        _mm_store_si128 ((__m128i *) &crypt_key[5][index], f);
        _mm_store_si128 ((__m128i *) &crypt_key[6][index], g);
        _mm_store_si128 ((__m128i *) &crypt_key[7][index], h);
    }

#if FMT_MAIN_VERSION > 10
    return count;
#endif
}