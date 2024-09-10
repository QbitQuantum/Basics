Isometry3d PrismaticJoint::jointTransform(double* const q) const
{
  Isometry3d ret;
  ret.linear().setIdentity();
  ret.translation() = q[0] * translation_axis;
  ret.makeAffine();
  return ret;
}