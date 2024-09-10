IGL_INLINE void igl::PolyVectorFieldFinder<DerivedV, DerivedF>::
minQuadWithKnownMini(const Eigen::SparseMatrix<std::complex<typename DerivedV::Scalar> > &Q,
                          const Eigen::SparseMatrix<std::complex<typename DerivedV::Scalar> > &f,
                     const Eigen::VectorXi isConstrained,
                          const Eigen::Matrix<std::complex<typename DerivedV::Scalar>, Eigen::Dynamic, 1> &xknown,
                          Eigen::Matrix<std::complex<typename DerivedV::Scalar>, Eigen::Dynamic, 1> &x)
{
  int N = Q.rows();

  int nc = xknown.rows();
  Eigen::VectorXi known; known.setZero(nc,1);
  Eigen::VectorXi unknown; unknown.setZero(N-nc,1);

  int indk = 0, indu = 0;
  for (int i = 0; i<N; ++i)
    if (isConstrained[i])
    {
      known[indk] = i;
      indk++;
    }
    else
    {
      unknown[indu] = i;
      indu++;
    }

  Eigen::SparseMatrix<std::complex<typename DerivedV::Scalar>> Quu, Quk;

  igl::slice(Q,unknown, unknown, Quu);
  igl::slice(Q,unknown, known, Quk);


  std::vector<typename Eigen::Triplet<std::complex<typename DerivedV::Scalar> > > tripletList;

  Eigen::SparseMatrix<std::complex<typename DerivedV::Scalar> > fu(N-nc,1);

  igl::slice(f,unknown, Eigen::VectorXi::Zero(1,1), fu);

  Eigen::SparseMatrix<std::complex<typename DerivedV::Scalar> > rhs = (Quk*xknown).sparseView()+.5*fu;

  Eigen::SparseLU< Eigen::SparseMatrix<std::complex<typename DerivedV::Scalar>>> solver;
  solver.compute(-Quu);
  if(solver.info()!=Eigen::Success)
  {
    std::cerr<<"Decomposition failed!"<<std::endl;
    return;
  }
  Eigen::SparseMatrix<std::complex<typename DerivedV::Scalar>>  b  = solver.solve(rhs);
  if(solver.info()!=Eigen::Success)
  {
    std::cerr<<"Solving failed!"<<std::endl;
    return;
  }

  indk = 0, indu = 0;
  x.setZero(N,1);
  for (int i = 0; i<N; ++i)
    if (isConstrained[i])
      x[i] = xknown[indk++];
    else
      x[i] = b.coeff(indu++,0);

}