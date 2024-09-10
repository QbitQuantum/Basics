TYPED_TEST(EulerAnglesXyzDiffTest, testFiniteDifference)
{
  typedef typename TestFixture::Scalar Scalar;
  typedef typename TestFixture::Rotation Rotation;
  typedef typename TestFixture::RotationDiff RotationDiff;
  typedef  typename TestFixture::Vector3 Vector3;

 const  double dt = 1e-3;
  for (auto rotation : this->rotations) {
    for (auto angularVelocity : this->angularVelocities) {
      // Finite difference method for checking derivatives
      RotationDiff rotationDiff(rotation, angularVelocity);
      Rotation rotationNext = rotation.boxPlus(dt*angularVelocity.toImplementation());
      Vector3 dn = (rotationNext.toImplementation()-rotation.toImplementation())/dt;
      ASSERT_NEAR(rotationDiff.x(),dn(0),1e-3) << " angular velocity: " << angularVelocity << " rotation: " << rotation << " rotationNext: " << rotationNext  << " diff: " << rotationDiff  << " approxdiff: " << dn.transpose();
      ASSERT_NEAR(rotationDiff.y(),dn(1),1e-3)  << " angular velocity: " << angularVelocity  <<  "rotation: " << rotation << " rotationNext: " << rotationNext << " diff: " << rotationDiff << " approxdiff: " << dn.transpose();
      ASSERT_NEAR(rotationDiff.z(),dn(2),1e-3) << " angular velocity: " << angularVelocity << " rotation: " << rotation << " rotationNext: " << rotationNext  << " diff: " << rotationDiff << " approxdiff: " << dn.transpose();

    }
  }
}