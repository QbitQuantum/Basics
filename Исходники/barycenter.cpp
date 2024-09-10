IGL_INLINE void igl::barycenter(
    const Eigen::PlainObjectBase<DerivedV> & V,
    const Eigen::PlainObjectBase<DerivedF> & F,
    Eigen::PlainObjectBase<DerivedBC> & BC)
{
  BC.setZero(F.rows(),V.cols());
  // Loop over faces
  for(int i = 0;i<F.rows();i++)
  {
    // loop around face
    for(int j = 0;j<F.cols();j++)
    {
      // Accumulate
      BC.row(i) += V.row(F(i,j));
    }
    // average
    BC.row(i) /= double(F.cols());
  }
}