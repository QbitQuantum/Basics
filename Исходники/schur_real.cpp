template<typename MatrixType> void schur(int size = MatrixType::ColsAtCompileTime)
{
  // Test basic functionality: T is quasi-triangular and A = U T U*
  for(int counter = 0; counter < g_repeat; ++counter) {
    MatrixType A = MatrixType::Random(size, size);
    RealSchur<MatrixType> schurOfA(A);
    VERIFY_IS_EQUAL(schurOfA.info(), Success);
    MatrixType U = schurOfA.matrixU();
    MatrixType T = schurOfA.matrixT();
    verifyIsQuasiTriangular(T);
    VERIFY_IS_APPROX(A, U * T * U.transpose());
  }

  // Test asserts when not initialized
  RealSchur<MatrixType> rsUninitialized;
  VERIFY_RAISES_ASSERT(rsUninitialized.matrixT());
  VERIFY_RAISES_ASSERT(rsUninitialized.matrixU());
  VERIFY_RAISES_ASSERT(rsUninitialized.info());

  // Test whether compute() and constructor returns same result
  MatrixType A = MatrixType::Random(size, size);
  RealSchur<MatrixType> rs1;
  rs1.compute(A);
  RealSchur<MatrixType> rs2(A);
  VERIFY_IS_EQUAL(rs1.info(), Success);
  VERIFY_IS_EQUAL(rs2.info(), Success);
  VERIFY_IS_EQUAL(rs1.matrixT(), rs2.matrixT());
  VERIFY_IS_EQUAL(rs1.matrixU(), rs2.matrixU());

  // Test computation of only T, not U
  RealSchur<MatrixType> rsOnlyT(A, false);
  VERIFY_IS_EQUAL(rsOnlyT.info(), Success);
  VERIFY_IS_EQUAL(rs1.matrixT(), rsOnlyT.matrixT());
  VERIFY_RAISES_ASSERT(rsOnlyT.matrixU());

  if (size > 2)
  {
    // Test matrix with NaN
    A(0,0) = std::numeric_limits<typename MatrixType::Scalar>::quiet_NaN();
    RealSchur<MatrixType> rsNaN(A);
    VERIFY_IS_EQUAL(rsNaN.info(), NoConvergence);
  }
}