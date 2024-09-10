template<typename Scalar> void
initSPD(double density,
        Matrix<Scalar,Dynamic,Dynamic>& refMat,
        SparseMatrix<Scalar>& sparseMat)
{
  Matrix<Scalar,Dynamic,Dynamic> aux(refMat.rows(),refMat.cols());
  initSparse(density,refMat,sparseMat);
  refMat = refMat * refMat.adjoint();
  for (int k=0; k<2; ++k)
  {
    initSparse(density,aux,sparseMat,ForceNonZeroDiag);
    refMat += aux * aux.adjoint();
  }
  sparseMat.setZero();
  for (int j=0 ; j<sparseMat.cols(); ++j)
    for (int i=j ; i<sparseMat.rows(); ++i)
      if (refMat(i,j)!=Scalar(0))
        sparseMat.insert(i,j) = refMat(i,j);
  sparseMat.finalize();
}