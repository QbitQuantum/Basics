/* TODO: if somebody comes up with a neat way to improve the interface so
 * as to remove the false dependency on pclmul, that would be nice.
 */
static inline __v2di
GF2X_FUNC(mul4cl1_mul1) (unsigned long a, unsigned long b)
{
    __v2di aa = (__v2di) { a, 0 };
    __v2di bb = (__v2di) { b, 0 };
    return _mm_clmulepi64_si128(aa, bb, 0);
}