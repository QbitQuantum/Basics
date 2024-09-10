  template<class Extension,class Info>
  struct call<sqrt_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>  : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL_DISPATCH(
      1,
      typename nt2::meta::scalar_of<A0>::type,
      (7, (float,double,uint64_t,uint32_t,uint16_t,uint8_t,arithmetic_))
      )
      
    NT2_FUNCTOR_CALL_EVAL_IF(1,       float)
    {
      A0 that = { _mm256_sqrt_ps(a0)}; return that; 
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,      double)
    {
      A0 that = { _mm256_sqrt_pd(a0)}; return that; 
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,     uint64_t)
    {
      return simd::native_cast<A0>(toint(sqrt(tofloat(a0))));
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,    uint32_t)
    {
      A0 const na = isnez(a0);
      A0 const z1 = add(shri(a0, 6),    integral_constant<A0,16>());
      A0 const z2 = add(shri(a0,10),   integral_constant<A0,256>());
      A0 const z3 = add(shri(a0,13),  integral_constant<A0,2048>());