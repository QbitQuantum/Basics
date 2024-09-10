Matrix3f NNUtilities::calcInverseTransformation(const Vector2i& center, const Vector2i& inSize, const Vector2i& outSize, const Angle rotation)
{
  const Vector2i upperLeft = (center.array() - inSize.array() / 2).matrix();
  const Vector2f transformationFactor = (inSize.cast<float>().array() / outSize.cast<float>().array()).matrix();
  //float sin = std::sin(rotation);
  //float cos = std::cos(rotation);

  Matrix3f inverseTransformation; //TODO check rotation
  inverseTransformation(0, 0) = transformationFactor.x();// *cos;
  inverseTransformation(0, 1) = 0;// transformationFactor.x() * (-sin);
  inverseTransformation(1, 0) = 0;// transformationFactor.y() * sin;
  inverseTransformation(1, 1) = transformationFactor.y();// *cos;

  inverseTransformation(0, 2) = upperLeft.x();// +outSize.x() * (1 - cos + sin) / 2 * transformationFactor.x();
  inverseTransformation(1, 2) = upperLeft.y();// +outSize.y() * (1 - sin - cos) / 2 * transformationFactor.y();
  return inverseTransformation;
}