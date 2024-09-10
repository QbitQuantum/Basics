    float avx_dot_product(std::vector<float> &av, std::vector<float> &bv)
    {

      /* Get SIMD-vector pointers to the start of each vector */
      unsigned int niters = av.size() / 8;

      float *a = (float *) aligned_alloc(32, av.size()*sizeof(float));
      float *b = (float *) aligned_alloc(32, av.size()*sizeof(float));
      memcpy(a,&av[0],av.size()*sizeof(float));
      memcpy(b,&bv[0],bv.size()*sizeof(float));

      __m256 *ptrA = (__m256*) &a[0], *ptrB = (__m256*) &b[0];
      __m256 res = _mm256_set1_ps(0.0);

      for (unsigned int i = 0; i < niters; i++, ptrA++,ptrB++)
        res = _mm256_add_ps(_mm256_dp_ps(*ptrA, *ptrB, 255), res);

      /* Get result back from the SIMD vector */
      float fres[8];
      _mm256_storeu_ps (fres, res);
      int q = 8 * niters;

      for (unsigned int i = 0; i < av.size() % 8; i++)
        fres[0] += (a[i+q]*b[i+q]);

      free(a);
      free(b);

      return fres[0] + fres[4];
    }