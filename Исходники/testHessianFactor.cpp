/* ************************************************************************* */
TEST(HessianFactor, Constructor1)
{
  Matrix G = Matrix_(2,2, 3.0, 5.0, 0.0, 6.0);
  Vector g = Vector_(2, -8.0, -9.0);
  double f = 10.0;

  Vector dxv = Vector_(2, 1.5, 2.5);

  vector<size_t> dims;
  dims.push_back(2);
  VectorValues dx(dims);

  dx[0] = dxv;

  HessianFactor factor(0, G, g, f);

  // extract underlying parts
  Matrix info_matrix = factor.info_.range(0, 1, 0, 1);
  EXPECT(assert_equal(Matrix(G), info_matrix));
  EXPECT_DOUBLES_EQUAL(f, factor.constantTerm(), 1e-10);
  EXPECT(assert_equal(g, Vector(factor.linearTerm()), 1e-10));
  EXPECT_LONGS_EQUAL(1, factor.size());

  // error 0.5*(f - 2*x'*g + x'*G*x)
  double expected = 80.375;
  double actual = factor.error(dx);
  double expected_manual = 0.5 * (f - 2.0 * dxv.dot(g) + dxv.transpose() * G.selfadjointView<Eigen::Upper>() * dxv);
  EXPECT_DOUBLES_EQUAL(expected, expected_manual, 1e-10);
  DOUBLES_EQUAL(expected, actual, 1e-10);
}