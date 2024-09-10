//==============================================================================
btTransform convertTransform(const Eigen::Isometry3d& _T)
{
  btTransform trans;
  trans.setOrigin(convertVector3(_T.translation()));
  trans.setBasis(convertMatrix3x3(_T.linear()));
  return trans;
}