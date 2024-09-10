void avx2_csr_spmv( float *A, int32_t *nIdx, int32_t **indices, float *x, int32_t n, float *y)
{
  int32_t A_offset = 0;
  for(int32_t i = 0; i < n; i++)
    {
      int32_t nElem = nIdx[i]; 
      float t = 0.0f;
      
      __m256 vT = _mm256_setzero_ps();
      int32_t smLen = nElem - (nElem & 7);

      for(int32_t j = 0; j < smLen; j+=8)
	{
	  __m256i vIdx = _mm256_load_si256((__m256i*)&(indices[i][j]));
	  __m256 vX = _mm256_i32gather_ps((float const*)x,vIdx,4);
	  __m256 vA = _mm256_loadu_ps(&A[A_offset + j]);
	  vT = _mm256_add_ps(vT, _mm256_mul_ps(vX,vA));

	}

      t += sum8(vT);
      for(int32_t j = smLen; j < nElem; j++)
	{
	  int32_t idx = indices[i][j];
	  t += x[idx]*A[A_offset + j];
	}

      y[i] = t;
      A_offset += nElem;
    }
} 