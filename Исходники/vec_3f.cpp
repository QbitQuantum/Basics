BVH_REAL quadraticForm(const Vec3f M[3], const Vec3f& v)
{
  return v.dot(Vec3f(M[0].dot(v), M[1].dot(v), M[2].dot(v)));
}