static inline void gauss_reduce_sse2(
    const float *const input, // fine input buffer
    float *const coarse,      // coarse scale, blurred input buf
    const int wd,             // fine res
    const int ht)
{
  // blur, store only coarse res
  const int cw = (wd-1)/2+1, ch = (ht-1)/2+1;

  // this version is inspired by opencv's pyrDown_ :
  // - allocate 5 rows of ring buffer (aligned)
  // - for coarse res y
  //   - fill 5 coarse-res row buffers with 1 4 6 4 1 weights (reuse some from last time)
  //   - do vertical convolution via sse and write to coarse output buf

  const int stride = ((cw+8)&~7); // assure sse alignment of rows
  float *ringbuf = dt_alloc_align(16, sizeof(*ringbuf)*stride*5);
  float *rows[5] = {0};
  int rowj = 0; // we initialised this many rows so far

  for(int j=1;j<ch-1;j++)
  {
    // horizontal pass, convolve with 1 4 6 4 1 kernel and decimate
    for(;rowj<=2*j+2;rowj++)
    {
      float *const row = ringbuf + (rowj % 5)*stride;
      const float *const in = input + rowj*wd;
#ifdef _OPENMP
#pragma omp parallel for schedule(static) default(none)
#endif
      for(int i=1;i<cw-1;i++)
        row[i] = 6*in[2*i] + 4*(in[2*i-1]+in[2*i+1]) + in[2*i-2] + in[2*i+2];
    }

    // init row pointers
    for(int k=0;k<5;k++)
      rows[k] = ringbuf + ((2*j-2+k)%5)*stride;

    // vertical pass, convolve and decimate using SIMD:
    // note that we're ignoring the (1..cw-1) buffer limit, we'll pull in
    // garbage and fix it later by border filling.
    float *const out = coarse + j*cw;
    const float *const row0 = rows[0], *const row1 = rows[1],
                *const row2 = rows[2], *const row3 = rows[3], *const row4 = rows[4];
    const __m128 four = _mm_set1_ps(4.f), scale = _mm_set1_ps(1.f/256.f);
#ifdef _OPENMP
#pragma omp parallel for schedule(static) default(none)
#endif
    for(int i=0;i<=cw-8;i+=8)
    {
      __m128 r0, r1, r2, r3, r4, t0, t1;
      r0 = _mm_load_ps(row0 + i);
      r1 = _mm_load_ps(row1 + i);
      r2 = _mm_load_ps(row2 + i);
      r3 = _mm_load_ps(row3 + i);
      r4 = _mm_load_ps(row4 + i);
      r0 = _mm_add_ps(r0, r4);
      r1 = _mm_add_ps(_mm_add_ps(r1, r3), r2);
      r0 = _mm_add_ps(r0, _mm_add_ps(r2, r2));
      t0 = _mm_add_ps(r0, _mm_mul_ps(r1, four));

      r0 = _mm_load_ps(row0 + i + 4);
      r1 = _mm_load_ps(row1 + i + 4);
      r2 = _mm_load_ps(row2 + i + 4);
      r3 = _mm_load_ps(row3 + i + 4);
      r4 = _mm_load_ps(row4 + i + 4);
      r0 = _mm_add_ps(r0, r4);
      r1 = _mm_add_ps(_mm_add_ps(r1, r3), r2);
      r0 = _mm_add_ps(r0, _mm_add_ps(r2, r2));
      t1 = _mm_add_ps(r0, _mm_mul_ps(r1, four));

      t0 = _mm_mul_ps(t0, scale);
      t1 = _mm_mul_ps(t1, scale);

      _mm_storeu_ps(out + i, t0);
      _mm_storeu_ps(out + i + 4, t1);
    }
    // process the rest
    for(int i=cw&~7;i<cw-1;i++)
      out[i] = (6*row2[i] + 4*(row1[i] + row3[i]) + row0[i] + row4[i])*(1.0f/256.0f);
  }
  dt_free_align(ringbuf);
  ll_fill_boundary1(coarse, cw, ch);
}