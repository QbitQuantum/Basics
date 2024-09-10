static void IDCT_1D_Multi(int16 *in_coeff, T *out_coeff)
{
#if defined(__SSE2__)
{
 for(unsigned col = 0; col < 8; col++)
 {
  __m128i c =  _mm_load_si128((__m128i *)&in_coeff[(col * 8)]);

  for(unsigned x = 0; x < 8; x++)
  {
   __m128i sum;
   __m128i m;
   int32 tmp[4] MDFN_ALIGN(16);

   m = _mm_load_si128((__m128i *)&IDCTMatrix[(x * 8)]);
   sum = _mm_madd_epi16(m, c);
   sum = _mm_add_epi32(sum, _mm_shuffle_epi32(sum, (3 << 0) | (2 << 2) | (1 << 4) | (0 << 6)));
   sum = _mm_add_epi32(sum, _mm_shuffle_epi32(sum, (1 << 0) | (0 << 2)));

   //_mm_store_ss((float *)&tmp[0], (__m128)sum);
   _mm_store_si128((__m128i*)tmp, sum);

   if(sizeof(T) == 1)
    out_coeff[(col * 8) + x] = Mask9ClampS8((tmp[0] + 0x4000) >> 15);
   else
    out_coeff[(x * 8) + col] = (tmp[0] + 0x4000) >> 15;
  }
 }
}