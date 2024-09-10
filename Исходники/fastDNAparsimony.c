static inline unsigned int populationCount(INT_TYPE v_N)
{
#ifdef __AVX
  {
    unsigned long int
      res[4] __attribute__ ((aligned (BYTE_ALIGNMENT)));
    unsigned int a, b;
    
    _mm256_store_pd((double*)res, v_N);
    
    a = __builtin_popcountl(res[0]) + __builtin_popcountl(res[1]);
    b = __builtin_popcountl(res[2]) + __builtin_popcountl(res[3]);
    
    return (a + b);	   
  }
#else	  
  return (vectorCount(v_N)); 
#endif
}