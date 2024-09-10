void test_grad_multi_student_t(const F& fun,
               const std::vector<T_y> & vec_y,
               const std::vector<T_mu> & vec_mu,
               const std::vector<T_sigma> & vec_sigma,
               const T_nu & nu) {
  using std::fabs;
  std::vector<double> diffs_finite = finite_diffs_multi_normal(fun,vec_y,vec_mu,vec_sigma,nu);
  std::vector<double> diffs_var = grad_multi_normal(fun,vec_y,vec_mu,vec_sigma,nu);
  EXPECT_EQ(diffs_finite.size(), diffs_var.size());
  for (size_t i = 0; i < diffs_finite.size(); ++i) {
    double tolerance = 1e-6 * fmax(fabs(diffs_finite[i]), fabs(diffs_var[i])) + 1e-14;
    EXPECT_NEAR(diffs_finite[i], diffs_var[i], tolerance);
  }
}