/* ************************************************************************* */
TEST( testLinearContainerFactor, hessian_factor_withlinpoints ) {
  // 2 variable example, one pose, one landmark (planar)
  // Initial ordering: x1, l1

  Matrix G11 = (Matrix(3, 3) <<
      1.0, 2.0, 3.0,
      0.0, 5.0, 6.0,
      0.0, 0.0, 9.0);
  Matrix G12 = (Matrix(3, 2) <<
      1.0, 2.0,
      3.0, 5.0,
      4.0, 6.0);
  Vector g1 = (Vector(3) << 1.0,  2.0,  3.0);

  Matrix G22 = (Matrix(2, 2) <<
        0.5, 0.2,
        0.0, 0.6);

  Vector g2 = (Vector(2) << -8.0, -9.0);

  double f = 10.0;

  // Construct full matrices
  Matrix G(5,5);
  G << G11, G12, Matrix::Zero(2,3), G22;

  HessianFactor initFactor(x1, l1, G11, G12, g1, G22, g2, f);

  Values linearizationPoint, expLinPoints;
  linearizationPoint.insert(l1, landmark1);
  linearizationPoint.insert(x1, poseA1);
  expLinPoints = linearizationPoint;
  linearizationPoint.insert(x2, poseA2);

  LinearContainerFactor actFactor(initFactor, linearizationPoint);
  EXPECT(!actFactor.isJacobian());
  EXPECT(actFactor.isHessian());

  EXPECT(actFactor.hasLinearizationPoint());
  Values actLinPoint = *actFactor.linearizationPoint();
  EXPECT(assert_equal(expLinPoints, actLinPoint));

  // Create delta
  Vector delta_l1 = (Vector(2) << 1.0, 2.0);
  Vector delta_x1 = (Vector(3) << 3.0, 4.0, 0.5);
  Vector delta_x2 = (Vector(3) << 6.0, 7.0, 0.3);

  // Check error calculation
  VectorValues delta = linearizationPoint.zeroVectors();
  delta.at(l1) = delta_l1;
  delta.at(x1) = delta_x1;
  delta.at(x2) = delta_x2;
  EXPECT(assert_equal((Vector(5) << 3.0, 4.0, 0.5, 1.0, 2.0), delta.vector(initFactor.keys())));
  Values noisyValues = linearizationPoint.retract(delta);

  double expError = initFactor.error(delta);
  EXPECT_DOUBLES_EQUAL(expError, actFactor.error(noisyValues), tol);
  EXPECT_DOUBLES_EQUAL(initFactor.error(linearizationPoint.zeroVectors()), actFactor.error(linearizationPoint), tol);

  // Compute updated versions
  Vector dv = (Vector(5) << 3.0, 4.0, 0.5, 1.0, 2.0);
  Vector g(5); g << g1, g2;
  Vector g_prime = g - G.selfadjointView<Eigen::Upper>() * dv;

  // Check linearization with corrections for updated linearization point
  Vector g1_prime = g_prime.head(3);
  Vector g2_prime = g_prime.tail(2);
  double f_prime = f + dv.transpose() * G.selfadjointView<Eigen::Upper>() * dv - 2.0 * dv.transpose() * g;
  HessianFactor expNewFactor(x1, l1, G11, G12, g1_prime, G22, g2_prime, f_prime);
  EXPECT(assert_equal(*expNewFactor.clone(), *actFactor.linearize(noisyValues), tol));
}