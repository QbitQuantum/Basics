void assert_vec_p(const Vec<T> &ref, const Vec<T> &act, int line)
{
  static const double tol = 1e-3;
  ASSERT_EQ(ref.length(), ref.length()) << line;
  for (int n = 0; n < ref.length(); ++n) {
    ASSERT_NEAR(ref(n), act(n), tol) << line;
  }
}