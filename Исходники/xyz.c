// return norm(vec)
double
xyz_norm( const xyz_t * const vec)
{
  return sqrt(xyz_norm_squared(vec));
}