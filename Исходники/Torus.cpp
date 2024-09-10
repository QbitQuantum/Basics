bool Torus::intersects(const Ray& ray,
                       HitRecord* hitRecord,
                       const Matrix4x4& inverseTransform) const {
  // New ray
  const auto p1 = inverseTransform * ray.start;
  const auto p2 = inverseTransform * ray.other;
  Ray localRay(p1, p2);
  double t = solveIntersection(localRay);
  if (!isValid(t)) return false;

  Point3D localPoint = localRay.at(t);
  Point3D globalPoint = ray.at(t);

  // Get the norm. See: http://www.emeyex.com/site/projects/raytorus.pdf
  double k = Vector3D(localPoint).length2() - tubeRadius*tubeRadius - 1;
  Vector3D localNorm(
    4 * localPoint[0] * k,
    4 * localPoint[1] * k,
    4 * localPoint[2] * k + 8 * localPoint[2]
  );
  auto norm = inverseTransform.transpose() * localNorm;
  norm.normalize();
  return hitRecord->update(norm, globalPoint, t);
}