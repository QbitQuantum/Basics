inline Vector2D Vector2D::reflect(const Vector2D &other) const
{
  Vector2D n = other;
  n.normalize();
  Vector2D w = *this - n * dot(n) * 2;
  return w;
}