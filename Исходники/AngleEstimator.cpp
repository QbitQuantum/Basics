Vector2<double> AngleEstimator::RotationMatrix::operator-(const RotationMatrix& other) const
{
  //return ((const RotationMatrix&)(other.invert() * *this)).getAngleAxis();
  const Vector3<double>& result(other * ((const RotationMatrix&)(other.invert() * *this)).getAngleAxis());
  return Vector2<double>(result.x, result.y);
}