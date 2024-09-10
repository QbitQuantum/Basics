inline void igl::PlanarizerShapeUp<DerivedV, DerivedF>::assembleP()
{
  P.setZero(3*ni*numF);
  for (int fi = 0; fi< numF; fi++)
  {
    // todo: this can be made faster by omitting the selector matrix
    Eigen::SparseMatrix<typename DerivedV::Scalar > Sfi;
    assembleSelector(fi, Sfi);
    Eigen::SparseMatrix<typename DerivedV::Scalar > NSi = Ni*Sfi;
    
    Eigen::Matrix<typename DerivedV::Scalar, Eigen::Dynamic, 1> Vi = NSi*Vv;
    Eigen::Matrix<typename DerivedV::Scalar, Eigen::Dynamic, Eigen::Dynamic> CC(3,ni);
    for (int i = 0; i <ni; ++i)
      CC.col(i) = Vi.segment(3*i, 3);
    Eigen::Matrix<typename DerivedV::Scalar, 3, 3> C = CC*CC.transpose();
    
    // Alec: Doesn't compile
    Eigen::EigenSolver<Eigen::Matrix<typename DerivedV::Scalar, 3, 3>> es(C);
    // the real() is for compilation purposes
    Eigen::Matrix<typename DerivedV::Scalar, 3, 1> lambda = es.eigenvalues().real();
    Eigen::Matrix<typename DerivedV::Scalar, 3, 3> U = es.eigenvectors().real();
    int min_i;
    lambda.cwiseAbs().minCoeff(&min_i);
    U.col(min_i).setZero();
    Eigen::Matrix<typename DerivedV::Scalar, Eigen::Dynamic, Eigen::Dynamic> PP = U*U.transpose()*CC;
    for (int i = 0; i <ni; ++i)
     P.segment(3*ni*fi+3*i, 3) =  weightsSqrt[fi]*PP.col(i);
    
  }
}