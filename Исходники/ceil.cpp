NT2_TEST_CASE_TPL ( ceil_real__1_0,  BOOST_SIMD_REAL_TYPES)
{
  
  using nt2::ceil;
  using nt2::tag::ceil_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<ceil_(T)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;
  typedef typename std::complex<T> cT;
  typedef typename nt2::meta::as_dry<T>::type dT;
  typedef typename nt2::meta::as_imaginary<T>::type ciT;



  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
//   double ulpd;
//   ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(ceil(cT(-1.1)), T(-1));
  NT2_TEST_EQUAL(ceil(cT(1.1)), T(2));
  NT2_TEST_EQUAL(ceil(nt2::Inf<cT>()), nt2::Inf<cT>());
  NT2_TEST_EQUAL(ceil(nt2::Minf<cT>()), nt2::Minf<cT>());
  NT2_TEST_EQUAL(ceil(nt2::Mone<cT>()), nt2::Mone<cT>());
  NT2_TEST_EQUAL(ceil(nt2::Nan<cT>()), nt2::Nan<cT>());
  NT2_TEST_EQUAL(ceil(nt2::One<cT>()), nt2::One<cT>());
  NT2_TEST_EQUAL(ceil(nt2::Zero<cT>()), nt2::Zero<cT>());
  NT2_TEST_EQUAL(ceil(dT(-1.1)), T(-1));
  NT2_TEST_EQUAL(ceil(dT(1.1)), T(2));
  NT2_TEST_EQUAL(ceil(dT(nt2::Inf<T>())), dT(nt2::Inf<T>()));
  NT2_TEST_EQUAL(ceil(dT(nt2::Minf<T>())), dT(nt2::Minf<T>()));
  NT2_TEST_EQUAL(ceil(dT(nt2::Mone<T>())), dT(nt2::Mone<T>()));
  NT2_TEST_EQUAL(ceil(dT(nt2::Nan<T>())), dT(nt2::Nan<T>()));
  NT2_TEST_EQUAL(ceil(dT(nt2::One<T>())), dT(nt2::One<T>()));
  NT2_TEST_EQUAL(ceil(dT(nt2::Zero<T>())), dT(nt2::Zero<T>()));
  NT2_TEST_EQUAL(ceil(ciT(-1.1)), ciT(-1));
  NT2_TEST_EQUAL(ceil(ciT(1.1)), ciT(2));
  NT2_TEST_EQUAL(ceil(nt2::Inf<ciT>()), nt2::Inf<ciT>());
  NT2_TEST_EQUAL(ceil(nt2::Minf<ciT>()), nt2::Minf<ciT>());
  NT2_TEST_EQUAL(ceil(nt2::Mone<ciT>()), nt2::Mone<ciT>());
  NT2_TEST_EQUAL(ceil(nt2::Nan<ciT>()), nt2::Nan<ciT>());
  NT2_TEST_EQUAL(ceil(nt2::One<ciT>()), nt2::One<ciT>());
  NT2_TEST_EQUAL(ceil(nt2::Zero<ciT>()), nt2::Zero<ciT>());
} // end of test for floating_