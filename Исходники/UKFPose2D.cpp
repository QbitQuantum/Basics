void UKFPose2D::poseSensorUpdate(const Vector3f& reading, const Matrix3f& readingCov)
{
  generateSigmaPoints();

  // computePoseReadings
  Vector3f poseReadings[7];
  for(int i = 0; i < 7; ++i)
    poseReadings[i] = sigmaPoints[i];

  // computeMeanOfPoseReadings
  Vector3f poseReadingMean = poseReadings[0];
  for(int i = 1; i < 7; ++i)
    poseReadingMean += poseReadings[i];
  poseReadingMean *= 1.f / 7.f;

  // computeCovOfPoseReadingsAndSigmaPoints
  Matrix3f poseReadingAndMeanCov = Matrix3f::Zero();
  for(int i = 0; i < 3; ++i)
  {
    const Vector3f d1 = poseReadings[i * 2 + 1] - poseReadingMean;
    poseReadingAndMeanCov += (Matrix3f() << d1 * l(0, i), d1 * l(1, i), d1 * l(2, i)).finished();
    const Vector3f d2 = poseReadings[i * 2 + 2] - poseReadingMean;
    poseReadingAndMeanCov += (Matrix3f() << d2 * -l(0, i), d2 * -l(1, i), d2 * -l(2, i)).finished();
  }
  poseReadingAndMeanCov *= 0.5f;

  // computeCovOfPoseReadingsReadings
  Matrix3f poseReadingCov;
  const Vector3f d = poseReadings[0] - poseReadingMean;
  poseReadingCov << d * d.x(), d * d.y(), d * d.z();
  for(int i = 1; i < 7; ++i)
  {
    const Vector3f d = poseReadings[i] - poseReadingMean;
    poseReadingCov += (Matrix3f() << d * d.x(), d * d.y(), d * d.z()).finished();
  }
  poseReadingCov *= 0.5f;

  poseReadingMean.z() = Angle::normalize(poseReadingMean.z());
  const Matrix3f kalmanGain = poseReadingAndMeanCov.transpose() * (poseReadingCov + readingCov).inverse();
  Vector3f innovation = reading - poseReadingMean;
  innovation.z() = Angle::normalize(innovation.z());
  const Vector3f correction = kalmanGain * innovation;
  mean += correction;
  mean.z() = Angle::normalize(mean.z());
  cov -= kalmanGain * poseReadingAndMeanCov;
  Covariance::fixCovariance(cov);
}