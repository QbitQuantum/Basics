Matrix3d SO3
::generator(int i)
{
  assert(i>=0 && i<3);
  Vector3d e;
  e.setZero();
  e[i] = 1.f;
  return hat(e);
}