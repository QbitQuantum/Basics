void ShaderRenderer::screenPosToDirection(const Common::Point screen, float &pitch, float &heading) {
  double x, y, z;

  x = screen.x;
  y = kOriginalHeight - screen.y;
  z = 0.9f;

  const Math::Vector2d tl = _viewport.getTopLeft();
  x = 2 * double(x - tl.getX()) / _viewport.getWidth() - 1.0f;
  y = 2 * double(y - tl.getY()) / _viewport.getHeight() - 1.0f;
  z = 2 * z - 1.0f;

  // Screen coords to 3D coords
  Math::Vector4d point = Math::Vector4d(x, y, z, 1.0f);
  point = _mvpMatrix * point;

  // 3D coords to polar coords
  Math::Vector3d v = Math::Vector3d(point.x(), point.y(), point.z());
  v.normalize();

  Math::Vector2d horizontalProjection = Math::Vector2d(v.x(), v.z());
  horizontalProjection.normalize();

  pitch = 90 - Math::Angle::arcCosine(v.y()).getDegrees();
  heading = Math::Angle::arcCosine(horizontalProjection.getY()).getDegrees();

  if (horizontalProjection.getX() > 0.0)
    heading = 360 - heading;
}