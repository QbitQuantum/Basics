IGL_INLINE void igl::per_face_normals(
  const Eigen::MatrixBase<DerivedV>& V,
  const Eigen::MatrixBase<DerivedF>& F,
  const Eigen::MatrixBase<DerivedZ> & Z,
  Eigen::PlainObjectBase<DerivedN> & N)
{
  N.resize(F.rows(),3);
  // loop over faces
  int Frows = F.rows();
#pragma omp parallel for if (Frows>10000)
  for(int i = 0; i < Frows;i++)
  {
    const Eigen::Matrix<typename DerivedV::Scalar, 1, 3> v1 = V.row(F(i,1)) - V.row(F(i,0));
    const Eigen::Matrix<typename DerivedV::Scalar, 1, 3> v2 = V.row(F(i,2)) - V.row(F(i,0));
    N.row(i) = v1.cross(v2);//.normalized();
    typename DerivedV::Scalar r = N.row(i).norm();
    if(r == 0)
    {
      N.row(i) = Z;
    }else
    {
      N.row(i) /= r;
    }
  }
}