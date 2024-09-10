  struct call<is_not_greater_equal_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL_DISPATCH(
      2,
      typename nt2::meta::scalar_of<A0>::type,
      (3, (float,double,arithmetic_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(2,  float)
    {
      A0 that = {_mm256_cmp_ps(a0,a1, _CMP_NGE_UQ)};
      return that; 
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2, double)
    {
      A0 that = {_mm256_cmp_pd(a0,a1, _CMP_NGE_UQ)};
      return that; 
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2, arithmetic_)
    {
      return ~nt2::is_ge(a0, a1);
    }
  };
} }

#endif