{
  template<class Dummy>
  struct  call< tag::is_equal_( tag::simd_<tag::double_,tag::sse_>
                              , tag::simd_<tag::double_,tag::sse_>
                              )
              , tag::cpu_, Dummy
              >
        : callable
  {
    template<class Sig>           struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> : meta::strip<A0> {};

    NT2_FUNCTOR_CALL(2)
    {
      A0 that = { _mm_cmpeq_pd(a0,a1) };
      return that;
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Overloads implementation for float
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::is_equal_, tag::cpu_, (A0)
                      , ((simd_<float_<A0>,tag::sse_>))
                        ((simd_<float_<A0>,tag::sse_>))
                      );

namespace nt2 { namespace ext
{