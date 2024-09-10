template<typename MatrixType> void eigensolver(const MatrixType& m)
{
  typedef typename MatrixType::Index Index;
  /* this test covers the following files:
     ComplexEigenSolver.h, and indirectly ComplexSchur.h
  */
  Index rows = m.rows();
  Index cols = m.cols();

  typedef typename MatrixType::Scalar Scalar;
  typedef typename NumTraits<Scalar>::Real RealScalar;

  MatrixType a = MatrixType::Random(rows,cols);
  MatrixType symmA =  a.adjoint() * a;

  ComplexEigenSolver<MatrixType> ei0(symmA);
  VERIFY_IS_EQUAL(ei0.info(), Success);
  VERIFY_IS_APPROX(symmA * ei0.eigenvectors(), ei0.eigenvectors() * ei0.eigenvalues().asDiagonal());

  ComplexEigenSolver<MatrixType> ei1(a);
  VERIFY_IS_EQUAL(ei1.info(), Success);
  VERIFY_IS_APPROX(a * ei1.eigenvectors(), ei1.eigenvectors() * ei1.eigenvalues().asDiagonal());
  // Note: If MatrixType is real then a.eigenvalues() uses EigenSolver and thus
  // another algorithm so results may differ slightly
  verify_is_approx_upto_permutation(a.eigenvalues(), ei1.eigenvalues());

  ComplexEigenSolver<MatrixType> ei2;
  ei2.setMaxIterations(ComplexSchur<MatrixType>::m_maxIterationsPerRow * rows).compute(a);
  VERIFY_IS_EQUAL(ei2.info(), Success);
  VERIFY_IS_EQUAL(ei2.eigenvectors(), ei1.eigenvectors());
  VERIFY_IS_EQUAL(ei2.eigenvalues(), ei1.eigenvalues());
  if (rows > 2) {
    ei2.setMaxIterations(1).compute(a);
    VERIFY_IS_EQUAL(ei2.info(), NoConvergence);
    VERIFY_IS_EQUAL(ei2.getMaxIterations(), 1);
  }

  ComplexEigenSolver<MatrixType> eiNoEivecs(a, false);
  VERIFY_IS_EQUAL(eiNoEivecs.info(), Success);
  VERIFY_IS_APPROX(ei1.eigenvalues(), eiNoEivecs.eigenvalues());

  // Regression test for issue #66
  MatrixType z = MatrixType::Zero(rows,cols);
  ComplexEigenSolver<MatrixType> eiz(z);
  VERIFY((eiz.eigenvalues().cwiseEqual(0)).all());

  MatrixType id = MatrixType::Identity(rows, cols);
  VERIFY_IS_APPROX(id.operatorNorm(), RealScalar(1));

  if (rows > 1 && rows < 20)
  {
    // Test matrix with NaN
    a(0,0) = std::numeric_limits<typename MatrixType::RealScalar>::quiet_NaN();
    ComplexEigenSolver<MatrixType> eiNaN(a);
    VERIFY_IS_EQUAL(eiNaN.info(), NoConvergence);
  }

  // regression test for bug 1098
  {
    ComplexEigenSolver<MatrixType> eig(a.adjoint() * a);
    eig.compute(a.adjoint() * a);
  }

  // regression test for bug 478
  {
    a.setZero();
    ComplexEigenSolver<MatrixType> ei3(a);
    VERIFY_IS_EQUAL(ei3.info(), Success);
    VERIFY_IS_MUCH_SMALLER_THAN(ei3.eigenvalues().norm(),RealScalar(1));
    VERIFY((ei3.eigenvectors().transpose()*ei3.eigenvectors().transpose()).eval().isIdentity());
  }
}