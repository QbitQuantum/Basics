void test_grad(const F& fun,
               const std::vector<double>& args) {
  using std::fabs;
  std::vector<double> diffs_finite = finite_diffs(fun,args);
  std::vector<double> diffs_var = grad(fun,args);
  EXPECT_EQ(diffs_finite.size(), diffs_var.size());
  for (size_t i = 0; i < args.size(); ++i) {
    double tolerance = 1e-6 * fmax(fabs(diffs_finite[i]), fabs(diffs_var[i])) + 1e-14;
    EXPECT_NEAR(diffs_finite[i], diffs_var[i], tolerance);
  }
}