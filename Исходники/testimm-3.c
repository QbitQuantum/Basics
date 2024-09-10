void
test8bit (void)
{
  i1 = _mm_cmpistrm (i2, i3, k4);	  /* { dg-error "the third argument must be an 8-bit immediate" } */
  k1 = _mm_cmpistri (i2, i3, k4);	  /* { dg-error "the third argument must be an 8-bit immediate" } */
  k1 = _mm_cmpistra (i2, i3, k4);	  /* { dg-error "the third argument must be an 8-bit immediate" } */
  k1 = _mm_cmpistrc (i2, i3, k4);	  /* { dg-error "the third argument must be an 8-bit immediate" } */
  k1 = _mm_cmpistro (i2, i3, k4);	  /* { dg-error "the third argument must be an 8-bit immediate" } */
  k1 = _mm_cmpistrs (i2, i3, k4);	  /* { dg-error "the third argument must be an 8-bit immediate" } */
  k1 = _mm_cmpistrz (i2, i3, k4);	  /* { dg-error "the third argument must be an 8-bit immediate" } */
  i1 = _mm_cmpestrm (i2, k2, i3, k3, k4); /* { dg-error "the fifth argument must be an 8-bit immediate" } */
  k1 = _mm_cmpestri (i2, k2, i3, k3, k4); /* { dg-error "the fifth argument must be an 8-bit immediate" } */
  k1 = _mm_cmpestra (i2, k2, i3, k3, k4); /* { dg-error "the fifth argument must be an 8-bit immediate" } */
  k1 = _mm_cmpestrc (i2, k2, i3, k3, k4); /* { dg-error "the fifth argument must be an 8-bit immediate" } */
  k1 = _mm_cmpestro (i2, k2, i3, k3, k4); /* { dg-error "the fifth argument must be an 8-bit immediate" } */
  k1 = _mm_cmpestrs (i2, k2, i3, k3, k4); /* { dg-error "the fifth argument must be an 8-bit immediate" } */
  k1 = _mm_cmpestrz (i2, k2, i3, k3, k4); /* { dg-error "the fifth argument must be an 8-bit immediate" } */
  b1 = _mm256_blend_ps (b2, b3, k4);	  /* { dg-error "the last argument must be an 8-bit immediate" } */
  k1 = _cvtss_sh (f1, k4);		  /* { dg-error "the last argument must be an 8-bit immediate" } */
  i1 = _mm256_cvtps_ph (b2, k4);	  /* { dg-error "the last argument must be an 8-bit immediate" } */
  b1 = _mm256_dp_ps (b2, b3, k4);	  /* { dg-error "the last argument must be an 8-bit immediate" } */
  e1 = _mm256_permute2f128_pd (e2, e3, k4);/* { dg-error "the last argument must be an 8-bit immediate" } */
  b1 = _mm256_permute2f128_ps (b2, b3, k4);/* { dg-error "the last argument must be an 8-bit immediate" } */
  l1 = _mm256_permute2f128_si256 (l2, l3, k4);/* { dg-error "the last argument must be an 8-bit immediate" } */
  b1 = _mm256_permute_ps (b2, k4);	  /* { dg-error "the last argument must be an 8-bit immediate" } */
  i1 = _mm_aeskeygenassist_si128 (i2, k4);/* { dg-error "the last argument must be an 8-bit immediate" } */
  i1 = _mm_blend_epi16 (i2, i3, k4);	  /* { dg-error "the last argument must be an 8-bit immediate" } */
  i1 = _mm_clmulepi64_si128 (i2, i3, k4); /* { dg-error "the last argument must be an 8-bit immediate" } */
  i1 = _mm_cvtps_ph (a1, k4);		  /* { dg-error "the last argument must be an 8-bit immediate" } */
  d1 = _mm_dp_pd (d2, d3, k4);		  /* { dg-error "the last argument must be an 8-bit immediate" } */
  a1 = _mm_dp_ps (a2, a3, k4);		  /* { dg-error "the last argument must be an 8-bit immediate" } */
  a1 = _mm_insert_ps (a2, a3, k4);	  /* { dg-error "the last argument must be an 8-bit immediate" } */
  i1 = _mm_mpsadbw_epu8 (i2, i3, k4);	  /* { dg-error "the last argument must be an 8-bit immediate" } */
  a1 = _mm_permute_ps (a2, k4);		  /* { dg-error "the last argument must be an 8-bit immediate" } */
  i1 = _mm_slli_si128 (i2, k4);		  /* { dg-error "the last argument must be an 8-bit immediate" } */
  i1 = _mm_srli_si128 (i2, k4);		  /* { dg-error "the last argument must be an 8-bit immediate" } */
}