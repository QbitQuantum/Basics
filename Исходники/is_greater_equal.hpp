{
  template<class Info>
  struct call<is_greater_equal_,tag::simd_(tag::arithmetic_,tag::sse_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A>
    struct result<This(A,A)> : meta::strip<A> {};

    NT2_FUNCTOR_CALL_DISPATCH( 2
                             , typename nt2::meta::scalar_of<A0>::type
                             , (3,(double,float,arithmetic_))
                             )

    NT2_FUNCTOR_CALL_EVAL_IF(2,double)
    {
      A0 that = { _mm_cmpge_pd(a0,a1) };
      return that;
    }

    NT2_FUNCTOR_CALL_EVAL_IF(2,float )
    {
      A0 that = { _mm_cmpge_ps(a0,a1) };
      return that;
    }

    NT2_FUNCTOR_CALL_EVAL_IF(2,arithmetic_)
    {
      A0 that = { complement(is_less(a0,a1) ) };
      return that;
    }
  };