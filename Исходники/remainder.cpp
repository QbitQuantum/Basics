NT2_TEST_CASE_TPL ( remainder_real__2_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::remainder;
  using nt2::tag::remainder_;
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;



  // specific values tests
  NT2_TEST_ULP_EQUAL(remainder(nt2::Inf<vT>(), nt2::Inf<vT>())[0], nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(remainder(nt2::Minf<vT>(), nt2::Minf<vT>())[0], nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(remainder(nt2::Mone<vT>(), nt2::Mone<vT>())[0], nt2::Zero<T>(), 0);
  NT2_TEST_ULP_EQUAL(remainder(nt2::Nan<vT>(), nt2::Nan<vT>())[0], nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(remainder(nt2::One<vT>(), nt2::One<vT>())[0], nt2::Zero<T>(), 0);
  NT2_TEST_ULP_EQUAL(remainder(nt2::One<vT>(),nt2::Zero<vT>())[0], nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(remainder(nt2::Zero<vT>(),nt2::Zero<vT>())[0], nt2::Nan<T>(), 0);
} // end of test for floating_