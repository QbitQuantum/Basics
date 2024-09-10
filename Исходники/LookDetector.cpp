IntersectRayBoundsResult IntersectRayBounds(const Matrix4f &centerViewMatrix,
                                            const Matrix4f &targetWorldMatrix,
                                            const GlGeometry &targetGeometry,
                                            bool axisInWorld) {

  Matrix4f worldToModelM = targetWorldMatrix.Inverted();
  Matrix4f invertedCenterViewM = centerViewMatrix.Inverted();
  Vector3f inWorldCenterViewPos = invertedCenterViewM.GetTranslation();
  Quatf centerViewRot = Quatf(invertedCenterViewM);

  const Vector3f rayStart = worldToModelM.Transform(inWorldCenterViewPos);
  const Vector3f rayDir = worldToModelM.Transform(centerViewRot.Rotate(
                              Vector3f(0.0f, 0.0f, -1.0f))) -
                          rayStart;
  const Vector3f boundingBoxMins = targetGeometry.localBounds.GetMins();
  const Vector3f boundingBoxMaxs = targetGeometry.localBounds.GetMaxs();
  float t0 = 0.0f;
  float t1 = 0.0f;

  bool intersected = Intersect_RayBounds(rayStart, rayDir, boundingBoxMins,
                                         boundingBoxMaxs, t0, t1);

  IntersectRayBoundsResult result;
  result.intersected = intersected && t0 > 0;

  if (intersected) {
    result.first = rayStart + t0 * rayDir;
    result.second = rayStart + t1 * rayDir;

    if (axisInWorld) {
      result.first = targetWorldMatrix.Transform(result.first);
      result.second = targetWorldMatrix.Transform(result.second);
    }
  }

  return result;
}