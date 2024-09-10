    void dare(const Eigen::Matrix<double,xDim,xDim> &A, const Eigen::Matrix<double,xDim,uDim> &B, Eigen::Matrix<double,xDim,xDim> &P) 
    {
      Eigen::Matrix<double,xDim,xDim> Ainv = A.inverse();
      Eigen::Matrix<double,xDim,xDim> ABRB = Ainv * B * _R.llt().solve(B.transpose());
      
      Eigen::Matrix<double,2*xDim,2*xDim> Z;
      Z.block(0,0,xDim,xDim) = Ainv;
      Z.block(0,xDim,xDim,xDim) = ABRB;
      Z.block(xDim,0,xDim,xDim) = _Q * Ainv;
      Z.block(xDim,xDim,xDim,xDim) = A.transpose() + _Q * ABRB;

      Eigen::ComplexEigenSolver <Eigen::Matrix<double,2*xDim,2*xDim> > ces;
      ces.compute(Z);

      Eigen::Matrix<std::complex<double>,2*xDim,1> eigVal = ces.eigenvalues();
      Eigen::Matrix<std::complex<double>,2*xDim,2*xDim> eigVec = ces.eigenvectors();

      Eigen::Matrix<std::complex<double>,2*xDim,xDim> unstableEigVec;
      
      int ctr = 0;
      for (int i = 0; i < 2*xDim; i++) {
        if (eigVal(i).real()*eigVal(i).real() + eigVal(i).imag()*eigVal(i).imag() > 1) {
          unstableEigVec.col(ctr) = eigVec.col(i);
          ctr++;
          if (ctr > xDim)
            break;
        }
      }
      
      Eigen::Matrix<std::complex<double>,xDim,xDim> U21inv = unstableEigVec.block(0,0,xDim,xDim).inverse();
      Eigen::Matrix<std::complex<double>,xDim,xDim> PP = unstableEigVec.block(xDim,0,xDim,xDim) * U21inv;
      
      for (int i = 0; i < xDim; i++) {
        for (int j = 0; j < xDim; j++) {
          P(i,j) = PP(i,j).real();
        }
      }
    }