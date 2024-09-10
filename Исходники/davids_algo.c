void vFindMax(__m128i *pixels, int n)
{
  __m128i vIdx,vMax;
  int i;
  vIdx = _mm_setzero_si128();
  vMax = _mm_set_epi32(INT_MIN,INT_MIN,INT_MIN,INT_MIN);
  for(i = 0; i < n; i++)
    {
      __m128i v = _mm_load_si128(pixels+i);
      __m128i vCmp = _mm_cmpgt_epi32(v, vMax);
      /* max value */
      vMax = _mm_max_epi32(vMax,v);
      
      __m128i vBdxIdx = _mm_set_epi32(i,i,i,i); 
      
      __m128 t0 = _mm_and_ps((__m128)vBdxIdx,(__m128)vCmp);
      __m128 t1 = _mm_andnot_ps((__m128)vCmp, (__m128)vIdx);
      /* max index */
      vIdx = (__m128i)_mm_or_ps(t0,t1);
    }
  int indices[4];
  int values[4];
  _mm_store_si128((__m128i*)indices, vIdx);
  _mm_store_si128((__m128i*)values, vMax);
  printf("SSE:\n");
  for(i=0;i<4;i++)
    {
      printf("%d:max=%d,idx=%d\n",i,values[i],indices[i]);
      //int idx = 4*indices[i] + i;
      //int *sArr = (int*)pixels;
      //printf("sArr[%d]=%d\n",idx,sArr[idx]);
    }
}