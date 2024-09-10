void extern
avx512dq_test (void)
{
  _x3 = _mm_mullo_epi64 (_y3, _z3);
  _x3 = _mm_mask_mullo_epi64 (_x3, 2, _y3, _z3);
  _x3 = _mm_maskz_mullo_epi64 (2, _y3, _z3);
  _x2 = _mm256_mullo_epi64 (_y2, _z2);
  _x2 = _mm256_mask_mullo_epi64 (_x2, 3, _y2, _z2);
  _x2 = _mm256_maskz_mullo_epi64 (3, _y2, _z2);
  _x1 = _mm512_mullo_epi64 (_y1, _z1);
  _x1 = _mm512_mask_mullo_epi64 (_x1, 3, _y1, _z1);
  _x1 = _mm512_maskz_mullo_epi64 (3, _y1, _z1);
}