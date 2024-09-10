Isometry3d RollPitchYawFloatingJoint::jointTransform(double* const q) const
{
  Isometry3d ret;
  Map<Vector3d> pos(&q[0]);
  Map<Vector3d> rpy(&q[3]);
  ret.linear() = rpy2rotmat(rpy);
  ret.translation() = pos;
  ret.makeAffine();
  return ret;
}