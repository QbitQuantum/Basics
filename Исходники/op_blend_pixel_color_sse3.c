/* blend pixel x color --> dst */

#ifdef BUILD_SSE3

static void
_op_blend_p_c_dp_sse3(DATA32 *s, DATA8 *m EINA_UNUSED, DATA32 c, DATA32 *d, int l) {

   DATA32 alpha;

   const __m128i c_packed = _mm_set_epi32(c, c, c, c);

   LOOP_ALIGNED_U1_A48(d, l,
      { /* UOP */

         DATA32 sc = MUL4_SYM(c, *s);
         alpha = 256 - (sc >> 24);
         *d = sc + MUL_256(alpha, *d);
         d++; s++; l--;
      },
      { /* A4OP */

         __m128i s0 = _mm_lddqu_si128((__m128i *)s);
         __m128i d0 = _mm_load_si128((__m128i *)d);

         __m128i sc0 = mul4_sym_sse3(c_packed, s0);
         __m128i a0  = sub4_alpha_sse3(sc0);
         __m128i mul0 = mul_256_sse3(a0, d0);

         d0 = _mm_add_epi32(sc0, mul0);

         _mm_store_si128((__m128i *)d, d0);