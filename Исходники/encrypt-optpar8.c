static void AES_set_encrypt_key(const unsigned char *key,
                                __m128i *expkey)
{
    __m128i *sched = (__m128i*) expkey;
    sched[ 0] = _mm_loadu_si128((__m128i*)key);
    sched[ 1] = assist128(sched[0], _mm_aeskeygenassist_si128(sched[0],0x1));
    sched[ 2] = assist128(sched[1], _mm_aeskeygenassist_si128(sched[1],0x2));
    sched[ 3] = assist128(sched[2], _mm_aeskeygenassist_si128(sched[2],0x4));
    sched[ 4] = assist128(sched[3], _mm_aeskeygenassist_si128(sched[3],0x8));
    sched[ 5] = assist128(sched[4], _mm_aeskeygenassist_si128(sched[4],0x10));
    sched[ 6] = assist128(sched[5], _mm_aeskeygenassist_si128(sched[5],0x20));
    sched[ 7] = assist128(sched[6], _mm_aeskeygenassist_si128(sched[6],0x40));
    sched[ 8] = assist128(sched[7], _mm_aeskeygenassist_si128(sched[7],0x80));
    sched[ 9] = assist128(sched[8], _mm_aeskeygenassist_si128(sched[8],0x1b));
    sched[10] = assist128(sched[9], _mm_aeskeygenassist_si128(sched[9],0x36));
}