void extern
avx512vbmi_test (void)
{
  _x3 = _mm_multishift_epi64_epi8 (_y3, _z3);
  _x3 = _mm_mask_multishift_epi64_epi8 (_x3, 2, _y3, _z3);
  _x3 = _mm_maskz_multishift_epi64_epi8 (2, _y3, _z3);
  _x2 = _mm256_multishift_epi64_epi8 (_y2, _z2);
  _x2 = _mm256_mask_multishift_epi64_epi8 (_x2, 3, _y2, _z2);
  _x2 = _mm256_maskz_multishift_epi64_epi8 (3, _y2, _z2);
  _x1 = _mm512_multishift_epi64_epi8 (_y1, _z1);
  _x1 = _mm512_mask_multishift_epi64_epi8 (_x1, 3, _y1, _z1);
  _x1 = _mm512_maskz_multishift_epi64_epi8 (3, _y1, _z1);
}