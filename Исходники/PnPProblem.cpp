// Möller–Trumbore intersection algorithm
bool PnPProblem::intersect_MollerTrumbore(Ray &Ray, Triangle &Triangle, double *out)
{
  const double EPSILON = 0.000001;

  cv::Point3f e1, e2;
  cv::Point3f P, Q, T;
  double det, inv_det, u, v;
  double t;

  cv::Point3f V1 = Triangle.getV0();  // Triangle vertices
  cv::Point3f V2 = Triangle.getV1();
  cv::Point3f V3 = Triangle.getV2();

  cv::Point3f O = Ray.getP0(); // Ray origin
  cv::Point3f D = Ray.getP1(); // Ray direction

  //Find vectors for two edges sharing V1
  e1 = SUB(V2, V1);
  e2 = SUB(V3, V1);

  // Begin calculation determinant - also used to calculate U parameter
  P = CROSS(D, e2);

  // If determinant is near zero, ray lie in plane of triangle
  det = DOT(e1, P);

  //NOT CULLING
  if(det > -EPSILON && det < EPSILON) return false;
  inv_det = 1.f / det;

  //calculate distance from V1 to ray origin
  T = SUB(O, V1);

  //Calculate u parameter and test bound
  u = DOT(T, P) * inv_det;

  //The intersection lies outside of the triangle
  if(u < 0.f || u > 1.f) return false;

  //Prepare to test v parameter
  Q = CROSS(T, e1);

  //Calculate V parameter and test bound
  v = DOT(D, Q) * inv_det;

  //The intersection lies outside of the triangle
  if(v < 0.f || u + v  > 1.f) return false;

  t = DOT(e2, Q) * inv_det;

  if(t > EPSILON) { //ray intersection
    *out = t;
    return true;
  }

  // No hit, no win
  return false;
}