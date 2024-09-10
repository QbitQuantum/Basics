/* ************************************************************************* */
TEST(GaussianBayesNet, ComputeSteepestDescentPoint) {

  // Create an arbitrary Bayes Net
  GaussianBayesNet gbn;
  gbn += GaussianConditional::shared_ptr(new GaussianConditional(
    0, Vector2(1.0,2.0), (Matrix(2, 2) << 3.0,4.0,0.0,6.0).finished(),
    3, (Matrix(2, 2) << 7.0,8.0,9.0,10.0).finished(),
    4, (Matrix(2, 2) << 11.0,12.0,13.0,14.0).finished()));
  gbn += GaussianConditional::shared_ptr(new GaussianConditional(
    1, Vector2(15.0,16.0), (Matrix(2, 2) << 17.0,18.0,0.0,20.0).finished(),
    2, (Matrix(2, 2) << 21.0,22.0,23.0,24.0).finished(),
    4, (Matrix(2, 2) << 25.0,26.0,27.0,28.0).finished()));
  gbn += GaussianConditional::shared_ptr(new GaussianConditional(
    2, Vector2(29.0,30.0), (Matrix(2, 2) << 31.0,32.0,0.0,34.0).finished(),
    3, (Matrix(2, 2) << 35.0,36.0,37.0,38.0).finished()));
  gbn += GaussianConditional::shared_ptr(new GaussianConditional(
    3, Vector2(39.0,40.0), (Matrix(2, 2) << 41.0,42.0,0.0,44.0).finished(),
    4, (Matrix(2, 2) << 45.0,46.0,47.0,48.0).finished()));
  gbn += GaussianConditional::shared_ptr(new GaussianConditional(
    4, Vector2(49.0,50.0), (Matrix(2, 2) << 51.0,52.0,0.0,54.0).finished()));

  // Compute the Hessian numerically
  Matrix hessian = numericalHessian<Vector10>(
      boost::bind(&computeError, gbn, _1), Vector10::Zero());

  // Compute the gradient numerically
  Vector gradient = numericalGradient<Vector10>(
      boost::bind(&computeError, gbn, _1), Vector10::Zero());

  // Compute the gradient using dense matrices
  Matrix augmentedHessian = GaussianFactorGraph(gbn).augmentedHessian();
  LONGS_EQUAL(11, (long)augmentedHessian.cols());
  Vector denseMatrixGradient = -augmentedHessian.col(10).segment(0,10);
  EXPECT(assert_equal(gradient, denseMatrixGradient, 1e-5));

  // Compute the steepest descent point
  double step = -gradient.squaredNorm() / (gradient.transpose() * hessian * gradient)(0);
  Vector expected = gradient * step;

  // Compute the steepest descent point with the dogleg function
  VectorValues actual = gbn.optimizeGradientSearch();

  // Check that points agree
  FastVector<Key> keys = list_of(0)(1)(2)(3)(4);
  Vector actualAsVector = actual.vector(keys);
  EXPECT(assert_equal(expected, actualAsVector, 1e-5));

  // Check that point causes a decrease in error
  double origError = GaussianFactorGraph(gbn).error(VectorValues::Zero(actual));
  double newError = GaussianFactorGraph(gbn).error(actual);
  EXPECT(newError < origError);
}