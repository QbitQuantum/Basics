Matrix4 Movable::matrixInverse() const {
  Matrix4 result;
  result=matrix();
  result.invert();
  return result;
}