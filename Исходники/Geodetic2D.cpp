Angle Geodetic2D::angleTo(const Geodetic2D& other) const
{
  const double cos1 = _latitude.cosinus();
  const Vector3D normal1(cos1 * _longitude.cosinus(),
                         cos1 * _longitude.sinus(),
                         _latitude.sinus());
  const double cos2 = other._latitude.cosinus();
  const Vector3D normal2(cos2 * other._longitude.cosinus(),
                         cos2 * other._longitude.sinus(),
                         other._latitude.sinus());
  return Angle::fromRadians(asin(normal1.cross(normal2).squaredLength()));

}