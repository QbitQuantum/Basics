{
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
    : meta::scalar_of<typename meta::strip<A0>::type> {};

    NT2_FUNCTOR_CALL_DISPATCH(
        1,
        typename nt2::meta::scalar_of<A0>::type,
        (6, (float,double,int64_,int32_,int16_,int8_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(1,       float)
{
    A0 min  = {_mm_min_ps(a0, _mm_movehl_ps(a0,a0))};
    A0 that = {_mm_min_ss(min, _mm_shuffle_ps(min,min,0x01))};
    return that[0];
}
NT2_FUNCTOR_CALL_EVAL_IF(1,      double)
{
    A0 that = {_mm_min_sd(a0, _mm_unpackhi_pd(a0,a0))};
    return that[0];
}
NT2_FUNCTOR_CALL_EVAL_IF(1,     int64_)
{
    return nt2::min(a0[0], a0[1]);
}
NT2_FUNCTOR_CALL_EVAL_IF(1,     int32_)
{
    A0 min1 = {min(a0,simd::native_cast<A0>(_mm_shuffle_epi32(a0, _MM_SHUFFLE(1, 0, 3, 2))))};
    A0 that = {min(min1, simd::native_cast<A0>(_mm_shuffle_epi32(min1, _MM_SHUFFLE(2, 3, 0, 1))))};