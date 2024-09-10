  template<class Dummy>
  struct call<tag::sort_(tag::simd_<tag::type32_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_real<A0>::type flt;
      A0 a =  {a0};
      A0 b =  {NT2_CAST(A0, _mm_movehl_ps(NT2_CAST(flt, a0), NT2_CAST(flt, a0)))};
      comp(a, b);
      a = NT2_CAST(A0, _mm_movelh_ps(NT2_CAST(flt, a), NT2_CAST(flt, b)));
      b = NT2_CAST(A0, _mm_shuffle_ps(NT2_CAST(flt, a), NT2_CAST(flt, b), NT2_SH(1, 3, 1, 3)));
      comp(a, b);
      A0 c = {NT2_CAST(A0, _mm_movelh_ps(NT2_CAST(flt, b), NT2_CAST(flt, b)))};
      A0 d = {a};
      comp(c, d);
      a = NT2_CAST(A0, _mm_shuffle_ps(NT2_CAST(flt, c), NT2_CAST(flt, a), NT2_SH(3, 2, 0, 0)));
      b = NT2_CAST(A0, _mm_movehl_ps(NT2_CAST(flt, b), NT2_CAST(flt, d)));
      b = NT2_CAST(A0, _mm_shuffle_ps(NT2_CAST(flt, a), NT2_CAST(flt, b), NT2_SH(3, 1, 0, 2)));
      return b;
    }
  private :
    template < class T > static inline void comp(T & a,T & b)
    {
      T c =  nt2::min(a, b);
      b = nt2::max(a, b);