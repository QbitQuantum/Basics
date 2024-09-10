void extern
avx512f_test (void)
{
  x = _mm512_roundscale_pd (x, 0x42);
  x = _mm512_ceil_pd (x);
  x = _mm512_floor_pd (x);
  x = _mm512_mask_roundscale_pd (x, 2, x, 0x42);
  x = _mm512_mask_ceil_pd (x, 2, x);
  x = _mm512_mask_floor_pd (x, 2, x);
  x = _mm512_maskz_roundscale_pd (2, x, 0x42);

  x = _mm512_roundscale_round_pd (x, 0x42, _MM_FROUND_NO_EXC);
  x = _mm512_mask_roundscale_round_pd (x, 2, x, 0x42, _MM_FROUND_NO_EXC);
  x = _mm512_maskz_roundscale_round_pd (2, x, 0x42, _MM_FROUND_NO_EXC);
}