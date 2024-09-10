unsigned long long ComputeMandelbrot_SSE(float *srcReal, float *srcImag, uint32_t *dst, int strideSrc, int strideDst, int x, int y, int yIncr, int w, int h, float left, float top, float incrX, float incrY, unsigned int numItersBefore, unsigned int numIters)
{
  for(int Y = y; Y < h; Y += yIncr)
  {
    float *sr = (float*)((uintptr_t)srcReal + strideSrc * Y) + x;
    float *si = (float*)((uintptr_t)srcImag + strideSrc * Y) + x;
    uint32_t *d = (uint32_t*)((uintptr_t)dst + strideDst * Y) + x;
    float imag = top + Y * incrY;
    __m128 Imag = _mm_set1_ps(imag);
    __m128 four = _mm_set1_ps(4.f);
    for(int X = 0; X < w; X += 4)
    {
      float real = left + (x + X) * incrX;
      __m128 Real = _mm_set_ps(real + 3*incrX, real + 2*incrX, real + incrX, real);
      __m128 v_real = _mm_loadu_ps(sr+X);
//      float v_real = sr[X];
//      if (v_real != INFINITY)
      {
        __m128 v_imag = _mm_loadu_ps(si+X);
//        float v_imag = si[X];

        __m128 oldColor = _mm_loadu_ps((float*)d+X);
        if (anyzero_ps(oldColor))
        //if (d[X] == 0 || d[X+1] == 0 || d[X+2] == 0 || d[X+3] == 0)
        {
          __m128 oldIterating = _mm_cmpeq_ps(oldColor, _mm_setzero_ps());
          for(unsigned int i = 0; i < numIters; ++i)
          {
            // (x+yi)^2 = x^2 - y^2 + 2xyi
            // ||x_+yi||^2 = x^2+y^2
            //float new_real = v_real*v_real - v_imag*v_imag + real;
            __m128 new_real = _mm_add_ps(_mm_sub_ps(_mm_mul_ps(v_real, v_real), _mm_mul_ps(v_imag, v_imag)), Real);
            //v_imag = 2.f * v_real * v_imag + imag;
            __m128 v_ri = _mm_mul_ps(v_real, v_imag);
            v_imag = _mm_add_ps(_mm_add_ps(v_ri, v_ri), Imag);
            v_real = new_real;

  /*
            new_real = v_real*v_real - v_imag*v_imag + real;
            v_imag = 2.f * v_real * v_imag + imag;
            v_real = new_real;
  */
            __m128 len = _mm_add_ps(_mm_mul_ps(v_real, v_real), _mm_mul_ps(v_imag, v_imag));
            __m128 diverged = _mm_cmpgt_ps(len, four);
            __m128 divergedNow = _mm_and_ps(diverged, oldIterating);
            oldIterating = _mm_andnot_ps(divergedNow, oldIterating);
            //__m128 diverged = _mm_cmpge_ps(len, _mm_set1_ps(0)); 
            //__m128 old = _mm_loadu_ps((float*)d+X);

            if (any_ps(divergedNow))
            {
              uint32_t color = ColorMap(numItersBefore + i);
              if (xnotzero_ss(divergedNow)) d[X] = color;
              if (ynotzero_ss(divergedNow)) d[X+1] = color;
              if (znotzero_ss(divergedNow)) d[X+2] = color;
              if (wnotzero_ss(divergedNow)) d[X+3] = color;
//              _mm_storeu_ps((float*)d+X, _mm_or_ps(old, diverged));
            }
            /*
            if (v_real*v_real + v_imag*v_imag > 4.f)
            {
              d[X] = ColorMap(numItersBefore + i);
              v_real = INFINITY;
              break;
            }
            */
          }
          //sr[X] = v_real;
          //si[X] = v_imag;
          _mm_storeu_ps(sr+X, v_real);
          _mm_storeu_ps(si+X, v_imag);
        }
      }
//      real += incrX*4;
//      Real = _mm_set_ps(real + 3*incrX, real + 2*incrX, real + incrX, real);
    }
  }
  return (unsigned long long)((h-y)/yIncr)*w*numIters;
}