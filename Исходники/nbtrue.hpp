  template<class Extension,class Info>
  struct call<nbtrue_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    typedef int32_t result_type; 

    NT2_FUNCTOR_CALL_DISPATCH(
      1,
      typename nt2::meta::scalar_of<A0>::type,
      (3, (float,double,arithmetic_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(1,       float)
    {
      typedef typename meta::as_real<A0>::type type; 
      int32_t  r = _mm256_movemask_ps(isnez(a0));
      return   (r&1)+((r>>1)&1)+((r>>2)&1)+(r>>3&1)+((r>>4)&1)+((r>>5)&1)+(r>>6&1)+(r>>7);
      //      return __builtin_popcount(_mm_movemask_ps(isnez(cast<type>(a0))));
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,      double)
    {
      int32_t  r = _mm256_movemask_pd(isnez(a0));
      return   (r&1)+(r>>1&1)+((r>>2)&1)+(r>>3); 
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1, arithmetic_)
    {
      typedef typename meta::scalar_of<A0>::type sctype;		
      typedef typename simd::native<sctype, tag::sse_ >  svtype;	
      svtype a00 = { _mm256_extractf128_si256(a0, 0)};			
      svtype a01 = { _mm256_extractf128_si256(a0, 1)};
      return nbtrue(a00)+nbtrue(a01); 