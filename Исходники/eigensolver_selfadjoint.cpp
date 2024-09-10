template<typename MatrixType> void selfadjointeigensolver(const MatrixType& m)
{
  typedef typename MatrixType::Index Index;
  /* this test covers the following files:
     EigenSolver.h, SelfAdjointEigenSolver.h (and indirectly: Tridiagonalization.h)
  */
  Index rows = m.rows();
  Index cols = m.cols();

  typedef typename MatrixType::Scalar Scalar;
  typedef typename NumTraits<Scalar>::Real RealScalar;

  RealScalar largerEps = 10*test_precision<RealScalar>();

  MatrixType a = MatrixType::Random(rows,cols);
  MatrixType a1 = MatrixType::Random(rows,cols);
  MatrixType symmA =  a.adjoint() * a + a1.adjoint() * a1;
  MatrixType symmC = symmA;
  
  svd_fill_random(symmA,Symmetric);

  symmA.template triangularView<StrictlyUpper>().setZero();
  symmC.template triangularView<StrictlyUpper>().setZero();

  MatrixType b = MatrixType::Random(rows,cols);
  MatrixType b1 = MatrixType::Random(rows,cols);
  MatrixType symmB = b.adjoint() * b + b1.adjoint() * b1;
  symmB.template triangularView<StrictlyUpper>().setZero();
  
  CALL_SUBTEST( selfadjointeigensolver_essential_check(symmA) );

  SelfAdjointEigenSolver<MatrixType> eiSymm(symmA);
  // generalized eigen pb
  GeneralizedSelfAdjointEigenSolver<MatrixType> eiSymmGen(symmC, symmB);

  SelfAdjointEigenSolver<MatrixType> eiSymmNoEivecs(symmA, false);
  VERIFY_IS_EQUAL(eiSymmNoEivecs.info(), Success);
  VERIFY_IS_APPROX(eiSymm.eigenvalues(), eiSymmNoEivecs.eigenvalues());
  
  // generalized eigen problem Ax = lBx
  eiSymmGen.compute(symmC, symmB,Ax_lBx);
  VERIFY_IS_EQUAL(eiSymmGen.info(), Success);
  VERIFY((symmC.template selfadjointView<Lower>() * eiSymmGen.eigenvectors()).isApprox(
          symmB.template selfadjointView<Lower>() * (eiSymmGen.eigenvectors() * eiSymmGen.eigenvalues().asDiagonal()), largerEps));

  // generalized eigen problem BAx = lx
  eiSymmGen.compute(symmC, symmB,BAx_lx);
  VERIFY_IS_EQUAL(eiSymmGen.info(), Success);
  VERIFY((symmB.template selfadjointView<Lower>() * (symmC.template selfadjointView<Lower>() * eiSymmGen.eigenvectors())).isApprox(
         (eiSymmGen.eigenvectors() * eiSymmGen.eigenvalues().asDiagonal()), largerEps));

  // generalized eigen problem ABx = lx
  eiSymmGen.compute(symmC, symmB,ABx_lx);
  VERIFY_IS_EQUAL(eiSymmGen.info(), Success);
  VERIFY((symmC.template selfadjointView<Lower>() * (symmB.template selfadjointView<Lower>() * eiSymmGen.eigenvectors())).isApprox(
         (eiSymmGen.eigenvectors() * eiSymmGen.eigenvalues().asDiagonal()), largerEps));


  eiSymm.compute(symmC);
  MatrixType sqrtSymmA = eiSymm.operatorSqrt();
  VERIFY_IS_APPROX(MatrixType(symmC.template selfadjointView<Lower>()), sqrtSymmA*sqrtSymmA);
  VERIFY_IS_APPROX(sqrtSymmA, symmC.template selfadjointView<Lower>()*eiSymm.operatorInverseSqrt());

  MatrixType id = MatrixType::Identity(rows, cols);
  VERIFY_IS_APPROX(id.template selfadjointView<Lower>().operatorNorm(), RealScalar(1));

  SelfAdjointEigenSolver<MatrixType> eiSymmUninitialized;
  VERIFY_RAISES_ASSERT(eiSymmUninitialized.info());
  VERIFY_RAISES_ASSERT(eiSymmUninitialized.eigenvalues());
  VERIFY_RAISES_ASSERT(eiSymmUninitialized.eigenvectors());
  VERIFY_RAISES_ASSERT(eiSymmUninitialized.operatorSqrt());
  VERIFY_RAISES_ASSERT(eiSymmUninitialized.operatorInverseSqrt());

  eiSymmUninitialized.compute(symmA, false);
  VERIFY_RAISES_ASSERT(eiSymmUninitialized.eigenvectors());
  VERIFY_RAISES_ASSERT(eiSymmUninitialized.operatorSqrt());
  VERIFY_RAISES_ASSERT(eiSymmUninitialized.operatorInverseSqrt());

  // test Tridiagonalization's methods
  Tridiagonalization<MatrixType> tridiag(symmC);
  VERIFY_IS_APPROX(tridiag.diagonal(), tridiag.matrixT().diagonal());
  VERIFY_IS_APPROX(tridiag.subDiagonal(), tridiag.matrixT().template diagonal<-1>());
  Matrix<RealScalar,Dynamic,Dynamic> T = tridiag.matrixT();
  if(rows>1 && cols>1) {
    // FIXME check that upper and lower part are 0:
    //VERIFY(T.topRightCorner(rows-2, cols-2).template triangularView<Upper>().isZero());
  }
  VERIFY_IS_APPROX(tridiag.diagonal(), T.diagonal());
  VERIFY_IS_APPROX(tridiag.subDiagonal(), T.template diagonal<1>());
  VERIFY_IS_APPROX(MatrixType(symmC.template selfadjointView<Lower>()), tridiag.matrixQ() * tridiag.matrixT().eval() * MatrixType(tridiag.matrixQ()).adjoint());
  VERIFY_IS_APPROX(MatrixType(symmC.template selfadjointView<Lower>()), tridiag.matrixQ() * tridiag.matrixT() * tridiag.matrixQ().adjoint());
  
  // Test computation of eigenvalues from tridiagonal matrix
  if(rows > 1)
  {
    SelfAdjointEigenSolver<MatrixType> eiSymmTridiag;
    eiSymmTridiag.computeFromTridiagonal(tridiag.matrixT().diagonal(), tridiag.matrixT().diagonal(-1), ComputeEigenvectors);
    VERIFY_IS_APPROX(eiSymm.eigenvalues(), eiSymmTridiag.eigenvalues());
    VERIFY_IS_APPROX(tridiag.matrixT(), eiSymmTridiag.eigenvectors().real() * eiSymmTridiag.eigenvalues().asDiagonal() * eiSymmTridiag.eigenvectors().real().transpose());
  }

  if (rows > 1 && rows < 20)
  {
    // Test matrix with NaN
    symmC(0,0) = std::numeric_limits<typename MatrixType::RealScalar>::quiet_NaN();
    SelfAdjointEigenSolver<MatrixType> eiSymmNaN(symmC);
    VERIFY_IS_EQUAL(eiSymmNaN.info(), NoConvergence);
  }

  // regression test for bug 1098
  {
    SelfAdjointEigenSolver<MatrixType> eig(a.adjoint() * a);
    eig.compute(a.adjoint() * a);
  }

  // regression test for bug 478
  {
    a.setZero();
    SelfAdjointEigenSolver<MatrixType> ei3(a);
    VERIFY_IS_EQUAL(ei3.info(), Success);
    VERIFY_IS_MUCH_SMALLER_THAN(ei3.eigenvalues().norm(),RealScalar(1));
    VERIFY((ei3.eigenvectors().transpose()*ei3.eigenvectors().transpose()).eval().isIdentity());
  }
}