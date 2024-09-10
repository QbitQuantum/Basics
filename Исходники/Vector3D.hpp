 inline Vector3D reflect(const Vector3D &v, const Vector3D &n) {
   return v - 2*dot(n, v)*n;
 }