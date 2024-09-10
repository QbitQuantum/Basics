NT2_TEST_CASE_TPL ( j0_real__1_0,  NT2_REAL_TYPES)
{

  using nt2::j0;
  using nt2::tag::j0_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<j0_(T)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename boost::dispatch::meta::as_floating<T>::type wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;
  double ulpd;
  ulpd=0.0;
  boost::dispatch::ignore_unused(ulpd);

  // specific values tests
  NT2_TEST_ULP_EQUAL(j0(nt2::Inf<T>()), nt2::Zero<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(j0(nt2::One<T>()), r_t( 7.651976865579666e-01), 0.5);
  NT2_TEST_ULP_EQUAL(j0(nt2::Zero<T>()), nt2::One<r_t>(), 0);
} // end of test for real_