NT2_TEST_CASE_TPL ( copysign_real__2_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::copysign;
  using nt2::tag::copysign_;
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::call<copysign_(T,T)>::type sr_t;



  // specific values tests
  NT2_TEST_EQUAL(copysign(nt2::Inf<vT>(), nt2::Inf<vT>())[0], nt2::Inf<sr_t>());
  NT2_TEST_EQUAL(copysign(nt2::Minf<vT>(), nt2::Minf<vT>())[0], nt2::Minf<sr_t>());
  NT2_TEST_EQUAL(copysign(nt2::Mone<vT>(), nt2::Mone<vT>())[0], nt2::Mone<sr_t>());
  NT2_TEST_EQUAL(copysign(nt2::Nan<vT>(), nt2::Nan<vT>())[0], nt2::Nan<sr_t>());
  NT2_TEST_EQUAL(copysign(nt2::One<vT>(), nt2::One<vT>())[0], nt2::One<sr_t>());
  NT2_TEST_EQUAL(copysign(nt2::One<vT>(), -nt2::Zero<vT>())[0], -nt2::One<sr_t>());
  NT2_TEST_EQUAL(copysign(nt2::One<vT>(), nt2::Zero<vT>())[0], nt2::One<sr_t>());
  NT2_TEST_EQUAL(copysign(nt2::Zero<vT>(), nt2::Zero<vT>())[0], nt2::Zero<sr_t>());
} // end of test for floating_