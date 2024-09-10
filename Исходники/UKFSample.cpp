Matrix2x2f UKFSample::getCovOfPointInWorld(const Vector2<>& pointInWorld2, float pointZInWorld, const MotionInfo& motionInfo,
                                           const CameraMatrix& cameraMatrix, const SelfLocatorParameters& parameters) const
{
  Vector3<> unscaledVectorToPoint = cameraMatrix.invert() * Vector3<>(pointInWorld2.x, pointInWorld2.y, pointZInWorld);
  const Vector3<> unscaledWorld = cameraMatrix.rotation * unscaledVectorToPoint;
  const float h = cameraMatrix.translation.z - pointZInWorld;
  const float scale = h / -unscaledWorld.z;
  Vector2f pointInWorld(unscaledWorld.x * scale, unscaledWorld.y * scale);
  const float distance = pointInWorld.abs();
  Vector2f cossin = distance == 0.f ? Vector2f(1.f, 0.f) : pointInWorld * (1.f / distance);
  Matrix2x2f rot(cossin, Vector2f(-cossin.y, cossin.x));
  const Vector2<>& robotRotationDeviation = motionInfo.motion == MotionRequest::stand
    ? parameters.robotRotationDeviationInStand : parameters.robotRotationDeviation;
  Matrix2x2f cov(Vector2f(sqr(h / tan((distance == 0.f ? pi_2 : atan(h / distance)) - robotRotationDeviation.x) - distance), 0.f),
                  Vector2f(0.f, sqr(tan(robotRotationDeviation.y) * distance)));
  return rot * cov * rot.transpose();
}