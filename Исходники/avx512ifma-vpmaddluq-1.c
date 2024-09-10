void extern
avx512ifma_test (void)
{
  _x3 = _mm_madd52lo_epu64 (_x3, _y3, _z3);
  _x3 = _mm_mask_madd52lo_epu64 (_x3, 2, _y3, _z3);
  _x3 = _mm_maskz_madd52lo_epu64 (2, _x3, _y3, _z3);
  _x2 = _mm256_madd52lo_epu64 (_x2, _y2, _z2);
  _x2 = _mm256_mask_madd52lo_epu64 (_x2, 3, _y2, _z2);
  _x2 = _mm256_maskz_madd52lo_epu64 (3, _x2, _y2, _z2);
  _x1 = _mm512_madd52lo_epu64 (_x1, _y1, _z1);
  _x1 = _mm512_mask_madd52lo_epu64 (_x1, 3, _y1, _z1);
  _x1 = _mm512_maskz_madd52lo_epu64 (3, _x1, _y1, _z1);
}