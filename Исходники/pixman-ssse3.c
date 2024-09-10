static void
ssse3_fetch_horizontal (bits_image_t *image, line_t *line,
			int y, pixman_fixed_t x, pixman_fixed_t ux, int n)
{
    uint32_t *bits = image->bits + y * image->rowstride;
    __m128i vx = _mm_set_epi16 (
	- (x + 1), x, - (x + 1), x,
	- (x + ux + 1), x + ux,  - (x + ux + 1), x + ux);
    __m128i vux = _mm_set_epi16 (
	- 2 * ux, 2 * ux, - 2 * ux, 2 * ux,
	- 2 * ux, 2 * ux, - 2 * ux, 2 * ux);
    __m128i vaddc = _mm_set_epi16 (1, 0, 1, 0, 1, 0, 1, 0);
    __m128i *b = (__m128i *)line->buffer;
    __m128i vrl0, vrl1;

    while ((n -= 2) >= 0)
    {
	__m128i vw, vr, s;

	vrl1 = _mm_loadl_epi64 (
	    (__m128i *)(bits + pixman_fixed_to_int (x + ux)));
	/* vrl1: R1, L1 */

    final_pixel:
	vrl0 = _mm_loadl_epi64 (
	    (__m128i *)(bits + pixman_fixed_to_int (x)));
	/* vrl0: R0, L0 */

	/* The weights are based on vx which is a vector of 
	 *
	 *    - (x + 1), x, - (x + 1), x,
	 *          - (x + ux + 1), x + ux, - (x + ux + 1), x + ux
	 *
	 * so the 16 bit weights end up like this:
	 *
	 *    iw0, w0, iw0, w0, iw1, w1, iw1, w1
	 *
	 * and after shifting and packing, we get these bytes:
	 *
	 *    iw0, w0, iw0, w0, iw1, w1, iw1, w1,
	 *        iw0, w0, iw0, w0, iw1, w1, iw1, w1,
	 *
	 * which means the first and the second input pixel 
	 * have to be interleaved like this:
	 *
	 *    la0, ra0, lr0, rr0, la1, ra1, lr1, rr1,
	 *        lg0, rg0, lb0, rb0, lg1, rg1, lb1, rb1
	 *
	 * before maddubsw can be used.
	 */

	vw = _mm_add_epi16 (
	    vaddc, _mm_srli_epi16 (vx, 16 - BILINEAR_INTERPOLATION_BITS));
	/* vw: iw0, w0, iw0, w0, iw1, w1, iw1, w1
	 */

	vw = _mm_packus_epi16 (vw, vw);
	/* vw: iw0, w0, iw0, w0, iw1, w1, iw1, w1,
	 *         iw0, w0, iw0, w0, iw1, w1, iw1, w1
	 */
	vx = _mm_add_epi16 (vx, vux);

	x += 2 * ux;

	vr = _mm_unpacklo_epi16 (vrl1, vrl0);
	/* vr: rar0, rar1, rgb0, rgb1, lar0, lar1, lgb0, lgb1 */

	s = _mm_shuffle_epi32 (vr, _MM_SHUFFLE (1, 0, 3, 2));
	/* s:  lar0, lar1, lgb0, lgb1, rar0, rar1, rgb0, rgb1 */

	vr = _mm_unpackhi_epi8 (vr, s);
	/* vr: la0, ra0, lr0, rr0, la1, ra1, lr1, rr1,
	 *         lg0, rg0, lb0, rb0, lg1, rg1, lb1, rb1
	 */

	vr = _mm_maddubs_epi16 (vr, vw);

	/* When the weight is 0, the inverse weight is
	 * 128 which can't be represented in a signed byte.
	 * As a result maddubsw computes the following:
	 *
	 *     r = l * -128 + r * 0
	 *
	 * rather than the desired
	 *
	 *     r = l * 128 + r * 0
	 *
	 * We fix this by taking the absolute value of the
	 * result.
	 */
	vr = _mm_abs_epi16 (vr);

	/* vr: A0, R0, A1, R1, G0, B0, G1, B1 */
	_mm_store_si128 (b++, vr);
    }

    if (n == -1)
    {
	vrl1 = _mm_setzero_si128();
	goto final_pixel;
    }

    line->y = y;
}