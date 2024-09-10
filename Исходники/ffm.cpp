float FFM::wTx(const ffm_node *instance, const unsigned int & size, float kappa, float eta, float lambda, bool do_update)
{
  long long align0 = (long long)parameters.num_factors*2;
  long long align1 = (long long)num_fields*align0;

  __m128 XMMkappa = _mm_set1_ps(kappa);
  __m128 XMMeta = _mm_set1_ps(eta);
  __m128 XMMlambda = _mm_set1_ps(lambda);

  __m128 XMMt = _mm_setzero_ps();

  for( unsigned int n1 = 0; n1 < size; n1++ )
  {
    int j1 = instance[n1].index;
    int f1 = instance[n1].field_index;
    float v1 = instance[n1].value;
    if(j1 >= num_features || f1 >= num_fields)
	continue;

    for( unsigned int n2 = n1 + 1; n2 < size; n2++ )
    {
      int j2 = instance[n2].index;
      int f2 = instance[n2].field_index;
      float v2 = instance[n2].value;
      if(j2 >= num_features || f2 >= num_fields)
	  continue;

      float *w1 = W + j1*align1 + f2*align0;
      float *w2 = W + j2*align1 + f1*align0;

      __m128 XMMv = _mm_set1_ps(v1*v2);

      if(do_update)
      {
	__m128 XMMkappav = _mm_mul_ps(XMMkappa, XMMv);

	float *wg1 = w1 + parameters.num_factors;
	float *wg2 = w2 + parameters.num_factors;
	for(int d = 0; d < parameters.num_factors; d += 4)
	{
	  __m128 XMMw1 = _mm_load_ps(w1+d);
	  __m128 XMMw2 = _mm_load_ps(w2+d);

	  __m128 XMMwg1 = _mm_load_ps(wg1+d);
	  __m128 XMMwg2 = _mm_load_ps(wg2+d);

	  __m128 XMMg1 = _mm_add_ps(_mm_mul_ps(XMMlambda, XMMw1), _mm_mul_ps(XMMkappav, XMMw2));
	  __m128 XMMg2 = _mm_add_ps(_mm_mul_ps(XMMlambda, XMMw2), _mm_mul_ps(XMMkappav, XMMw1));

	  XMMwg1 = _mm_add_ps(XMMwg1, _mm_mul_ps(XMMg1, XMMg1));
	  XMMwg2 = _mm_add_ps(XMMwg2, _mm_mul_ps(XMMg2, XMMg2));

	  XMMw1 = _mm_sub_ps(XMMw1, _mm_mul_ps(XMMeta, _mm_mul_ps(_mm_rsqrt_ps(XMMwg1), XMMg1)));
	  XMMw2 = _mm_sub_ps(XMMw2, _mm_mul_ps(XMMeta, _mm_mul_ps(_mm_rsqrt_ps(XMMwg2), XMMg2)));

	  _mm_store_ps(w1+d, XMMw1);
	  _mm_store_ps(w2+d, XMMw2);

	  _mm_store_ps(wg1+d, XMMwg1);
	  _mm_store_ps(wg2+d, XMMwg2);
	}
      }
      else
      {
	for(int d = 0; d < parameters.num_factors; d += 4)
	{
	  __m128  XMMw1 = _mm_load_ps(w1+d);
	  __m128  XMMw2 = _mm_load_ps(w2+d);

	  XMMt = _mm_add_ps(XMMt, _mm_mul_ps(_mm_mul_ps(XMMw1, XMMw2), XMMv));
	}
      }
    }
  }

  if(do_update)
      return 0;

  XMMt = _mm_hadd_ps(XMMt, XMMt);
  XMMt = _mm_hadd_ps(XMMt, XMMt);
  float t;
  _mm_store_ss(&t, XMMt);

  return t;
}