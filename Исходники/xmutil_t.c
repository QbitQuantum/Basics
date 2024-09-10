int main(void)
{
    int i, j, k = 0, len, set, hop;
    setvbuf(stdout, NULL, _IOLBF, 0);
    plan_tests(1 + nffstests + nshltests + 5 + 128);

    XMM ones = (__v2di) {
        -1, -1
    };
    ok(xm_same(xm_ones, ones), "xm_ones produces FFFF...FFFF");

    for (i = 0; i < nffstests; ++i) {
        int act = findbit_1((uint8_t*)&ffstestv[i].inp, sizeof(XMM));
        ok(act == ffstestv[i].exp, "test %d: act:%d exp:%d", i, act, ffstestv[i].exp);
    }

    for (i = 0; i < nshltests; ++i) {
        char acts[99];
        XMM act = xm_shl(shltestv[0].exp, shltestv[i].nbits);
        xm_llx(act, acts);
        ok(0xFFFF == xm_same(act, shltestv[i].exp),
           "shl %d: %s", shltestv[i].nbits, acts);
    }

    XMM bitz = { 1,8 };
    int iact = xm_ffs(bitz);
    ok(iact == 0, "xm_ffs(bitz) = %d", iact);
    iact = xm_fls(bitz);
    ok(iact == 67, "xm_fls(bitz) = %d", iact);

    bitz = _mm_setzero_si128();
    iact = xm_ffs(bitz);
    ok(iact == -1, "xm_ffs(zero) = %d", iact);
    iact = xm_fls(bitz);
    ok(iact == -1, "xm_fls(zero) = %d", iact);

    XMM stuff = (__v2di) {
        0x07BB01426C62272EULL, 0x6295C58D62B82175ULL
    };
    char    str[48];
    xm_str(stuff, str);
    is_strncmp(str, "2E,27,62,6C,42,01,BB,07-75,21,B8,62,8D,C5,95,62", 48, "xm_str");

    XMM one = { 1, 0 }, hibit = xm_shl_177(one);
    for (i = 0; i < 128; ++i) {
        int pos = xm_ffs(xm_or(xm_shl(one, i), hibit));
        ok(pos == i, "xm_ffs(xm_shl(one,%d)) = %d", i, pos);
    }

#   define CMPSIZE 100000000L
    char *x = malloc(CMPSIZE), *y = malloc(CMPSIZE);
    memcpy(x, y, CMPSIZE);
    for (len = 20; len <= CMPSIZE; len *= 4) {
        for (i = 1; i < 17; i += i) {
            for (j = 1; j < 17; j += j) {
                for (set = 1; set < 2; set++) {
                    char *a, *b;
                    double t0 = tick();

                    for (hop = CMPSIZE / len, a = x, b = y; hop; --hop, a += len, b += len)
                        a[i+len-17] ^= set, k += cmpxm(a+i, b+j, len-17), a[i+len-17] ^= set;

                    double t1 = tick();

                    for (hop = CMPSIZE / len, a = x, b = y; hop; --hop, a += len, b += len) {
                        _mm_prefetch(a+i+448, _MM_HINT_NTA);
                        _mm_prefetch(b+j+448, _MM_HINT_NTA);
                        a[i+len-17] ^= set, k += memcmp(a+i, b+j, len-17), a[i+len-17] ^= set;
                    }
                    double t2 = tick();

                    printf("%9d %2d %2d %d %4.1f\n", len, i, j, set, (t2 - t1)/(t1 - t0));
                }
            }
        }
    }

    if (!k) puts("");
    return exit_status();
}