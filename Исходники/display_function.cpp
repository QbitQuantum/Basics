v4sf DisplayFunctionGGBA::display( v4sf pix )
{
  return _mm_pow_ps(pix, _mm_set1_ps(gamma)) * (_mm_set1_ps(L_max)-_mm_set1_ps(L_black)) + _mm_set1_ps(L_offset);
}