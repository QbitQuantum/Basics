void mesh_core::PlaneProjection::getFrame(Eigen::Affine3d& frame) const
{
  frame.setIdentity();
  frame.translation() = origin_;
  frame.linear().col(0) = x_axis_;
  frame.linear().col(1) = y_axis_;
  frame.linear().col(2) = normal_;
}