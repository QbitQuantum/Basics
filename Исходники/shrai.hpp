                        ((simd_<arithmetic_<A0>,tag::avx_>))
                        ((simd_<arithmetic_<A0>,tag::avx_>))
                       );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::shrai_(tag::simd_<tag::arithmetic_, tag::avx_),
                          tag::simd_<tag::arithmetic_, tag::avx_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0,A1)> : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::scalar_of<A0>::type sctype;
      typedef typename simd::native<sctype, tag::sse_ >  svtype;
      svtype a00 = { _mm256_extractf128_si256(a0, 0)};
      svtype a01 = { _mm256_extractf128_si256(a0, 1)};
      A0 that = { _mm256_insertf128_si256(that,nt2::shrai( a00, a1), 0)};
      that =  _mm256_insertf128_si256(that, nt2::shrai(a01, a1), 1);
      return that;
     }

  };
} }

#endif
// modified by jt the 04/01/2011