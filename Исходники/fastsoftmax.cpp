static void 
mexsoftmax(float* y, float* shift, mwSize m, mwSize n) {
  __m128 i1, i2;
  __m128 o1, o2;
 
  while (m>0)
    {
      mwSize curn = n;
      float sum = 0.0f;
      declconst128(zero, 0.0f);
      
      while (curn>0 && ((unsigned long)(y+curn) & 15) != 0)
        {
          --curn;
          y[curn]=fastexp(y[curn]-*shift);
          sum += y[curn];
        }

      __m128 s1 = _mm_load1_ps (shift);
      __m128 sum1 = zero;

      while (curn>7) {
        i1 = _mm_load_ps (y+curn-4);
        i2 = _mm_load_ps (y+curn-8);
        i1 = _mm_sub_ps (i1, s1);
        i2 = _mm_sub_ps (i2, s1);
        o1 = vfastexp(i1);
        o2 = vfastexp(i2);
        _mm_store_ps (y+curn-4, o1);
        sum1 = _mm_add_ps (sum1, o1);
        _mm_store_ps (y+curn-8, o2);
        sum1 = _mm_add_ps (sum1, o2);
        curn-=8;
      }

      sum1 = _mm_hadd_ps (sum1, sum1);
      sum1 = _mm_hadd_ps (sum1, sum1);
      sum += _mm_cvtss_f32 (sum1);
     
      while(curn>0) {
        --curn;
        y[curn]=fastexp(y[curn]-*shift);
        sum += y[curn];
      }

      sum = 1.0f / sum;

      ptrdiff_t n_pdt = n;
      ptrdiff_t one_pdt = 1;

      sscal (&n_pdt, &sum, y, &one_pdt);

      ++shift;
      y+=n;
      --m;
    }
}