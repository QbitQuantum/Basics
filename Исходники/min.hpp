  struct call<min_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL_DISPATCH(
      2,
      typename nt2::meta::scalar_of<A0>::type,
      (9, (float,double,int8_t,int16_t,int32_t,uint8_t,uint16_t,uint32_t,arithmetic_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(2,       float)
    {
      A0 that =  {_mm256_min_ps(a0,a1)}; return that;
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2,      double)
    {
      A0 that =  {_mm256_min_pd(a0,a1)}; return that;
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2,     int8_t)
    {
      NT2_XOP_JOIN128INT(that, _mm_min_epi8); return that;
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2,     int16_t)
    {
      NT2_XOP_JOIN128INT(that, _mm_min_epi16); return that;
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2,     int32_t)
    {