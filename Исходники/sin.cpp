NT2_TEST_CASE_TPL ( sin_signed_int__1_0,  NT2_INTEGRAL_SIGNED_TYPES)
{

  using nt2::sin;
  using nt2::tag::sin_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<sin_(T)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename boost::dispatch::meta::as_floating<T>::type wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;

  // specific values tests
  NT2_TEST_ULP_EQUAL(sin(nt2::Zero<T>()), nt2::Zero<r_t>(), 0.5);
} // end of test for signed_int_