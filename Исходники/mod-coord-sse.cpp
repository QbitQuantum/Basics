void lfModifier::ModifyCoord_Dist_Poly3_SSE (void *data, float *iocoord, int count)
{
  // See "Note about PT-based distortion models" at the top of mod-coord.cpp.
  /*
   * If buffer is not aligned, fall back to plain code
   */
  if((uintptr_t)(iocoord) & 0xf)
  {
    return ModifyCoord_Dist_Poly3(data, iocoord, count);
  }

  lfCoordDistCallbackData* cddata = (lfCoordDistCallbackData*) data;

  // Rd = Ru * (1 + k1 * Ru^2)
  __m128 k1_ = _mm_set_ps1 (cddata->Terms [0]);
  __m128 cx = _mm_set_ps1 (cddata->centerX);
  __m128 cy = _mm_set_ps1 (cddata->centerY);
  __m128 cc = _mm_set_ps1 (cddata->coordinate_correction);
  __m128 one = _mm_set_ps1 (1.0f);

  // SSE Loop processes 4 pixels/loop
  int loop_count = count / 4;
  for (int i = 0; i < loop_count ; i++)
  {
    __m128 c0 = _mm_load_ps (&iocoord [8 * i]);
    __m128 c1 = _mm_load_ps (&iocoord [8 * i + 4]);
    __m128 x = _mm_shuffle_ps (c0, c1, _MM_SHUFFLE (2, 0, 2, 0));
    __m128 y = _mm_shuffle_ps (c0, c1, _MM_SHUFFLE (3, 1, 3, 1));
    x = _mm_sub_ps(_mm_mul_ps(x, cc), cx);
    y = _mm_sub_ps(_mm_mul_ps(y, cc), cy);

    // Calculate poly3 = k1_ * ru * ru + 1;
    __m128 poly3 = _mm_add_ps (_mm_mul_ps (_mm_add_ps (_mm_mul_ps (x, x), _mm_mul_ps (y, y)), k1_), one);

    x = _mm_add_ps(_mm_mul_ps (x, poly3), cx);
    y = _mm_add_ps(_mm_mul_ps (y, poly3), cy);
    x = _mm_div_ps (x, cc);
    y = _mm_div_ps (y, cc);

    c0 = _mm_unpacklo_ps(x, y);
    c1 = _mm_unpackhi_ps(x, y);

    _mm_store_ps (&iocoord [8 * i], c0);
    _mm_store_ps (&iocoord [8 * i + 4], c1);
  }

  loop_count *= 4;
  int remain = count - loop_count;
  if (remain)
    ModifyCoord_Dist_Poly3 (data, &iocoord [loop_count * 2], remain);
}