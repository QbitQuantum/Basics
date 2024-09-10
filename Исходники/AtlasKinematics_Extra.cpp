/**
 * @function KState
 */
Eigen::Affine3d KState::xform() const {

  Eigen::Affine3d xform = Eigen::Affine3d::Identity();
  xform.linear() = body_rot.toRotationMatrix();
  xform.translation() = body_pos;
  
  return xform;
}