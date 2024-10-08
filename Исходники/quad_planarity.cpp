IGL_INLINE void igl::quad_planarity(
  const Eigen::PlainObjectBase<DerivedV>& V,
  const Eigen::PlainObjectBase<DerivedF>& F,
  Eigen::PlainObjectBase<DerivedP> & P)
{
  int nf = F.rows();
  P.setZero(nf,1);
  for (int i =0; i<nf; ++i)
  {
    const Eigen::Matrix<typename DerivedV::Scalar,1,3> &v1 = V.row(F(i,0));
    const Eigen::Matrix<typename DerivedV::Scalar,1,3> &v2 = V.row(F(i,1));
    const Eigen::Matrix<typename DerivedV::Scalar,1,3> &v3 = V.row(F(i,2));
    const Eigen::Matrix<typename DerivedV::Scalar,1,3> &v4 = V.row(F(i,3));
    Eigen::Matrix<typename DerivedV::Scalar,1,3> diagCross=(v3-v1).cross(v4-v2);
    typename Eigen::PlainObjectBase<DerivedV>::Scalar denom = diagCross.norm()*(((v3-v1).norm()+(v4-v2).norm())/2);
    if (fabs(denom)<1e-8)
      //degenerate quad is still planar
      P[i] = 0;
    else
      P[i] = (diagCross.dot(v2-v1)/denom);
  }
}