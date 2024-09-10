Eigen::Isometry3d toIsometry(const Eigen::Affine3d& pose)
{
  Eigen::Isometry3d p(pose.rotation());
  p.translation() = pose.translation();

  return p;
}