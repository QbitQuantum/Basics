NT2_TEST_CASE_TPL ( atan_uint_convert__1_0,  NT2_SIMD_UINT_CONVERT_TYPES)
{
  using nt2::atan;
  using nt2::tag::atan_;
  using nt2::load; 
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<atan_(vT)>::type r_t;
  typedef typename nt2::meta::call<atan_(T)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_ULP_EQUAL(atan(nt2::One<vT>())[0], nt2::Pi<sr_t>()/4, 0.5);
  NT2_TEST_ULP_EQUAL(atan(nt2::Zero<vT>())[0], nt2::Zero<sr_t>(), 0.5);
} // end of test for uint_convert_