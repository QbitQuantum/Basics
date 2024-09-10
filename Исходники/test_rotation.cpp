TEST(Rotation, TestEulerAnglesAndMatrices) {
  // Randomly generate euler angles, convert to a matrix, then convert back.
  // Check that (1) the rotation matrix has det(R)==1, and (2), that we get the
  // same angles back.
  math::RandomGenerator rng(0);
  for (int ii = 0; ii < 1000; ++ii) {
    Vector3d e1;
    e1.setRandom();

    // Converting from rotation matrices to euler angles is only valid when phi,
    // theta, and psi are all < 0.5*PI. Otherwise the problem has multiple
    // solutions, and we can only return one of them with our function.
    e1 *= 0.5 * M_PI;

    Matrix3d R = EulerAnglesToMatrix(e1);
    EXPECT_NEAR(1.0, R.determinant(), 1e-8);

    Vector3d e2 = MatrixToEulerAngles(R);
    EXPECT_NEAR(0.0, S1Distance(e1(0), e2(0)), 1e-8);
    EXPECT_NEAR(0.0, S1Distance(e1(1), e2(1)), 1e-8);
    EXPECT_NEAR(0.0, S1Distance(e1(2), e2(2)), 1e-8);

    EXPECT_TRUE(R.isApprox(EulerAnglesToMatrix(e2), 1e-4));
  }
}