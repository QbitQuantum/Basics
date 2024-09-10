Eigen::Matrix3f
ElementHex::GetDeformationGrad(const Eigen::Vector3f & p,
    const std::vector<Eigen::Vector3f> & X,
    const std::vector<Eigen::Vector3f> & u)
{
  Eigen::Matrix3f F = Eigen::Matrix3f::Identity();
  for(int ii = 0;ii<8;ii++){
    int idx = GetNodeIndex(ii);
    Eigen::Vector3f gradN = ShapeFunGrad(ii,p,X);
    //outer product
    F += u[idx] * gradN.transpose();
  }
  return F;
}