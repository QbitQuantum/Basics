/* compute chi2 distance between two vectors */
static float vec_chi2 (const float *a, const float *b, int n) 
{
  int i=0;
  __v4sf accu={0,0,0,0};
  __v4sf *av=(void*)a,*bv=(void*)b;
  n/=4;

  for (i = 0 ; i < n ; i++) {
    __v4sf ai = av[i],bi=bv[i];
    __v4sf sum = ai+bi,diff=ai-bi;
    __v4sf mask = _mm_cmpneq_ps(ai,bi);
    accu+=_mm_and_ps (_mm_div_ps(_mm_mul_ps(diff,diff),sum),mask);
  }

  float *af=(void*)&accu;
      
  return af[0] + af[1] + af[2] + af[3];
}