void
dt_gaussian_blur_4c(
    dt_gaussian_t *g,
    float    *in,
    float    *out)
{

  const int width = g->width;
  const int height = g->height;
  const int ch = 4;

  assert(g->channels == 4);

  float a0, a1, a2, a3, b1, b2, coefp, coefn;

  compute_gauss_params(g->sigma, g->order, &a0, &a1, &a2, &a3, &b1, &b2, &coefp, &coefn);

  const __m128 Labmax = _mm_set_ps(g->max[3], g->max[2], g->max[1], g->max[0]);
  const __m128 Labmin = _mm_set_ps(g->min[3], g->min[2], g->min[1], g->min[0]);

  float *temp = g->buf;


  // vertical blur column by column
#ifdef _OPENMP
  #pragma omp parallel for default(none) shared(in,out,temp,a0,a1,a2,a3,b1,b2,coefp,coefn) schedule(static)
#endif
  for(int i=0; i<width; i++)
  {
    __m128 xp = _mm_setzero_ps();
    __m128 yb = _mm_setzero_ps();
    __m128 yp = _mm_setzero_ps();
    __m128 xc = _mm_setzero_ps();
    __m128 yc = _mm_setzero_ps();
    __m128 xn = _mm_setzero_ps();
    __m128 xa = _mm_setzero_ps();
    __m128 yn = _mm_setzero_ps();
    __m128 ya = _mm_setzero_ps();

    // forward filter
    xp = MMCLAMPPS(_mm_load_ps(in+i*ch), Labmin, Labmax);
    yb = _mm_mul_ps(_mm_set_ps1(coefp), xp);
    yp = yb;

 
    for(int j=0; j<height; j++)
    {
      int offset = (i + j * width)*ch;

      xc = MMCLAMPPS(_mm_load_ps(in+offset), Labmin, Labmax);


      yc = _mm_add_ps(_mm_mul_ps(xc, _mm_set_ps1(a0)),
           _mm_sub_ps(_mm_mul_ps(xp, _mm_set_ps1(a1)),
           _mm_add_ps(_mm_mul_ps(yp, _mm_set_ps1(b1)), _mm_mul_ps(yb, _mm_set_ps1(b2)))));

      _mm_store_ps(temp+offset, yc);

      xp = xc;
      yb = yp;
      yp = yc;

    }

    // backward filter
    xn = MMCLAMPPS(_mm_load_ps(in+((height - 1) * width + i)*ch), Labmin, Labmax);
    xa = xn;
    yn = _mm_mul_ps(_mm_set_ps1(coefn), xn);
    ya = yn;

    for(int j=height - 1; j > -1; j--)
    {
      int offset = (i + j * width)*ch;

      xc = MMCLAMPPS(_mm_load_ps(in+offset), Labmin, Labmax);

      yc = _mm_add_ps(_mm_mul_ps(xn, _mm_set_ps1(a2)),
           _mm_sub_ps(_mm_mul_ps(xa, _mm_set_ps1(a3)),
           _mm_add_ps(_mm_mul_ps(yn, _mm_set_ps1(b1)), _mm_mul_ps(ya, _mm_set_ps1(b2)))));


      xa = xn; 
      xn = xc; 
      ya = yn; 
      yn = yc;

      _mm_store_ps(temp+offset, _mm_add_ps(_mm_load_ps(temp+offset), yc));
    }
  }

  // horizontal blur line by line
#ifdef _OPENMP
  #pragma omp parallel for default(none) shared(out,temp,a0,a1,a2,a3,b1,b2,coefp,coefn) schedule(static)
#endif
  for(int j=0; j<height; j++)
  {
    __m128 xp = _mm_setzero_ps();
    __m128 yb = _mm_setzero_ps();
    __m128 yp = _mm_setzero_ps();
    __m128 xc = _mm_setzero_ps();
    __m128 yc = _mm_setzero_ps();
    __m128 xn = _mm_setzero_ps();
    __m128 xa = _mm_setzero_ps();
    __m128 yn = _mm_setzero_ps();
    __m128 ya = _mm_setzero_ps();

    // forward filter
    xp = MMCLAMPPS(_mm_load_ps(temp+j*width*ch), Labmin, Labmax);
    yb = _mm_mul_ps(_mm_set_ps1(coefp), xp);
    yp = yb;

 
    for(int i=0; i<width; i++)
    {
      int offset = (i + j * width)*ch;

      xc = MMCLAMPPS(_mm_load_ps(temp+offset), Labmin, Labmax);

      yc = _mm_add_ps(_mm_mul_ps(xc, _mm_set_ps1(a0)),
           _mm_sub_ps(_mm_mul_ps(xp, _mm_set_ps1(a1)),
           _mm_add_ps(_mm_mul_ps(yp, _mm_set_ps1(b1)), _mm_mul_ps(yb, _mm_set_ps1(b2)))));

      _mm_store_ps(out+offset, yc);

      xp = xc;
      yb = yp;
      yp = yc;
    }

    // backward filter
    xn = MMCLAMPPS(_mm_load_ps(temp+((j + 1)*width - 1)*ch), Labmin, Labmax);
    xa = xn;
    yn = _mm_mul_ps(_mm_set_ps1(coefn), xn);
    ya = yn;


    for(int i=width - 1; i > -1; i--)
    {
      int offset = (i + j * width)*ch;

      xc = MMCLAMPPS(_mm_load_ps(temp+offset), Labmin, Labmax);

      yc = _mm_add_ps(_mm_mul_ps(xn, _mm_set_ps1(a2)),
           _mm_sub_ps(_mm_mul_ps(xa, _mm_set_ps1(a3)),
           _mm_add_ps(_mm_mul_ps(yn, _mm_set_ps1(b1)), _mm_mul_ps(ya, _mm_set_ps1(b2)))));


      xa = xn; 
      xn = xc; 
      ya = yn; 
      yn = yc;

      _mm_store_ps(out+offset, _mm_add_ps(_mm_load_ps(out+offset), yc));
    }
  }
}