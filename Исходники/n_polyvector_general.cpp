IGL_INLINE void igl::GeneralPolyVectorFieldFinder<DerivedV, DerivedF>::getGeneralCoeffConstraints(const Eigen::VectorXi &isConstrained,
                                                       const Eigen::Matrix<typename DerivedV::Scalar, Eigen::Dynamic, Eigen::Dynamic> &cfW,
                                                       int k,
                                                       const Eigen::VectorXi &rootsIndex,
                                                       Eigen::Matrix<std::complex<typename DerivedV::Scalar>, Eigen::Dynamic,1> &Ck)
{
  int numConstrained = isConstrained.sum();
  Ck.resize(numConstrained,1);
  // int n = rootsIndex.cols();

  Eigen::MatrixXi allCombs;
  {
    Eigen::VectorXi V = Eigen::VectorXi::LinSpaced(n,0,n-1);
    igl::nchoosek(V,k+1,allCombs);
  }

  int ind = 0;
  for (int fi = 0; fi <numF; ++fi)
  {
    const Eigen::Matrix<typename DerivedV::Scalar, 1, 3> &b1 = B1.row(fi);
    const Eigen::Matrix<typename DerivedV::Scalar, 1, 3> &b2 = B2.row(fi);
    if(isConstrained[fi])
    {
      std::complex<typename DerivedV::Scalar> ck(0);

      for (int j = 0; j < allCombs.rows(); ++j)
      {
        std::complex<typename DerivedV::Scalar> tk(1.);
        //collect products
        for (int i = 0; i < allCombs.cols(); ++i)
        {
          int index = allCombs(j,i);

          int ri = rootsIndex[index];
          Eigen::Matrix<typename DerivedV::Scalar, 1, 3> w;
          if (ri>0)
            w = cfW.block(fi,3*(ri-1),1,3);
          else
            w = -cfW.block(fi,3*(-ri-1),1,3);
          typename DerivedV::Scalar w0 = w.dot(b1);
          typename DerivedV::Scalar w1 = w.dot(b2);
          std::complex<typename DerivedV::Scalar> u(w0,w1);
          tk*= u;
        }
        //collect sum
        ck += tk;
      }
      Ck(ind) = ck;
      ind ++;
    }
  }


}