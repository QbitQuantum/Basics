void gf2x_mul2(unsigned long * t, unsigned long const * s1,
        unsigned long const * s2)
#endif
#endif
{
    typedef union {
        __v2di s;
        unsigned long x[2];
    } __v2di_proxy;

    __v2di ss1, ss2, s1s, s2s;
    __v2di_proxy t00, tk;
#ifndef BORROW
    __v2di_proxy t11;
#endif
    ss1 = _mm_loadu_si128((__v2di *)s1);
    ss2 = _mm_loadu_si128((__v2di *)s2);


    t00.s = _mm_clmulepi64_si128(ss1, ss2, 0);
#ifndef BORROW
    t11.s = _mm_clmulepi64_si128(ss1, ss2, 17);
#endif

    s1s = _mm_shuffle_epi32(ss1, 78);
    ss1 ^= s1s;
    s2s = _mm_shuffle_epi32(ss2, 78);
    ss2 ^= s2s;

    tk.s = _mm_clmulepi64_si128(ss1, ss2, 0);

#ifndef BORROW
    tk.s ^= t00.s ^ t11.s;
#endif

    /* store result */
    t[0] = t00.x[0];
#ifdef BORROW
    t[1] = t00.x[1] ^ tk.x[0] ^ t00.x[0] ^ c[0];
    t[2] = c[0] ^ tk.x[1] ^ t00.x[1] ^ c[1];
    t[3] = c[1];
#else
    t[1] = t00.x[1] ^ tk.x[0];
    t[2] = t11.x[0] ^ tk.x[1];
    t[3] = t11.x[1];
#endif
#ifdef CARRY
    c[0] = t11.x[0];
    c[1] = t11.x[1];
#endif
}