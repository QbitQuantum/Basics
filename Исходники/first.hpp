                        (A0),
                        ((simd_<ints64_<A0>,tag::sse_>))
                       );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::first_(tag::simd_<tag::ints64_, tag::sse_> ),
              tag::sse4_1_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct  result<This(A0)>
          : meta::scalar_of<typename meta::strip<A0>::type> {};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<A0>::type type;
      type z = {_mm_extract_epi64(a0, 0)};
      return z;
    }
  };
} }
#endif

#endif

// /////////////////////////////////////////////////////////////////////////////
// End of first.hpp
// /////////////////////////////////////////////////////////////////////////////
