bool ExitingMethod1(VPlacedVolume const *pvol, Vector3D<Precision> const &point, Vector3D<Precision> const &dir)
{
  Vector3D<Precision> normal;
  bool valid = pvol->Normal(point, normal);
  return valid && normal.Dot(dir) > 0;
}