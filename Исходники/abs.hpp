{
  template<class Dummy>
  struct call<tag::abs_(tag::simd_<tag::signed_, tag::avx_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<A0>::type sctype;
      typedef typename simd::native<sctype, tag::sse_ >  svtype;
      svtype a00 = { _mm256_extractf128_si256(a0, 0)};
      svtype a01 = { _mm256_extractf128_si256(a0, 1)};
      A0 that = { _mm256_insertf128_si256(that,nt2::abs(a00), 0)};
      that =  _mm256_insertf128_si256(that,nt2::abs(a01), 1);
      //       NT2_AVX_JOIN128INT1(that, nt2::abs);
      return that;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is unsigned_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::abs_, tag::cpu_,
                      (A0),
                      ((simd_<unsigned_<A0>,tag::avx_>))
                     );
