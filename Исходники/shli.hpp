#include <nt2/sdk/meta/strip.hpp>

#include <nt2/include/functions/details/simd/sse/sse4_1/shli.hpp>

namespace nt2 { namespace functors
{
  //  no special validate for shli

  template<class Extension,class Info>
  struct call<shli_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0,A1)> : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::scalar_of<A0>::type sctype;
      typedef typename meta::as_integer<sctype>::type sitype; 
      typedef typename simd::native<sitype, tag::sse_ >  isvtype;		
      typedef typename meta::as_integer<A0>::type  itype;

      isvtype a00 = { _mm256_extractf128_si256(simd::native_cast<itype>(a0), 0)};			
      isvtype a01 = { _mm256_extractf128_si256(simd::native_cast<itype>(a0), 1)};			
      itype that = { _mm256_insertf128_si256(that,nt2::shli( a00, a1), 0)};	
      return  simd::native_cast<A0>(_mm256_insertf128_si256(that, nt2::shli(a01, a1), 1)); 		
     }
  };
} }

#endif