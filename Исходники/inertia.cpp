//==============================================================================
// Note: Taken from Springer Handbook, chapter 2.2.11
void Inertia::computeSpatialTensor()
{
  Eigen::Matrix3d C = math::makeSkewSymmetric(mCenterOfMass);

  // Top left
  mSpatialTensor.block<3,3>(0,0) = getMoment() + mMass*C*C.transpose();

  // Bottom left
  mSpatialTensor.block<3,3>(3,0) = mMass*C.transpose();

  // Top right
  mSpatialTensor.block<3,3>(0,3) = mMass*C;

  // Bottom right
  mSpatialTensor.block<3,3>(3,3) = mMass*Eigen::Matrix3d::Identity();
}