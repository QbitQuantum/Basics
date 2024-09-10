std::tuple<bool, Ray> a4_reflect_perturbed(const Ray& reflected, const Vector3D& normal, double glossiness, const std::function<double()>& uniform)
{
  Vector3D r = reflected.direction();
  Vector3D na = -r;
  Vector3D U, V;

  // Get the basis vectors for the square of size <glossiness>x<glossiness>
  if(na[2] > na[0] && na[2] > na[1]) U = Vector3D(-na[1], na[0], 0.0);
  else if(na[1] > na[0]) U = Vector3D(-na[2], 0.0, na[0]);
  else U = Vector3D(0.0, -na[2], na[1]);
  U.normalized();

  V = na.cross(U).normalized();

  // Randomly generate a 2D point on the square
  double u = -(glossiness * 0.5) + uniform() * glossiness;
  double v = -(glossiness * 0.5) + uniform() * glossiness;

  // Use the 2D point and the basis vectors for the square to perturb the reflection ray to point to a location on the square
  Point3D rp = Point3D(r[0], r[1], r[2]) + u * U + v * V;

  // Set the new perturbed direction vector for the ray
  r = Vector3D(rp[0], rp[1], rp[2]);

  // Check if the perturbed ray is below the surface
  return std::tuple<bool, Ray>(normal.dot(r) < 0, Ray(reflected.origin(), r)); 
}