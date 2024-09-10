  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      { typedef typename meta::as_integer<A0>::type type; };

    NT2_FUNCTOR_CALL_DISPATCH(
      1,
      typename nt2::meta::scalar_of<A0>::type,
      (3, (float,double,arithmetic_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(1,  float)
    {
      typedef typename NT2_CALL_RETURN_TYPE(1)::type type;
      type that =  {_mm256_cvttps_epi32(a0)};
      return  that; 
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1, double)
    {
      typedef typename NT2_CALL_RETURN_TYPE(1)::type type;
      const type v = {{a0[0],a0[1], a0[2],a0[3]}}; //TODO with _mm_cvttpd_epi32 
      return v;
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1, arithmetic_)
    {
      return a0;
    }
  };
} }
