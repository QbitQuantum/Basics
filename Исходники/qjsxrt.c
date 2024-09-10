quaternion reciprocal(quaternion m)
{
  quaternion out;
  out = rmult(1/norm2(m),conjugate(m));
  return out;
}