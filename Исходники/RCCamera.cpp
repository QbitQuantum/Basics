void RCViewableTransform::setPosition(const Eks::Vector3D &point)
  {
  Eks::Transform t = transform();
  t.translation() = point;
  transform = t;
  }