Vector2f LIP3D::requiredVelocity(const Vector2f& pos, float time)
{
  const Array2f sinhkt(std::sinh(k.x() * time), std::sinh(k.y() * time));
  const Array2f coshkt(std::cosh(k.x() * time), std::cosh(k.y() * time));

  return k.array() * (pos.array() - position.array() * coshkt) / sinhkt;
}