Vec3f radiationVector_qmc(const Vec3f& w, Qmc& random) {
  Vec3f u = (std::abs(w.x()) > 0.0001) ? Vec3f::UnitY().cross(w).normalized()
                                       : Vec3f::UnitX().cross(w).normalized();
  Vec3f v = w.cross(u);

  const Real r1  = 2.0 * M_PI * random.next();
  const Real r2  = random.next();
  const Real r2s = std::sqrt(r2);
  
  return (u * std::cos(r1) * r2s
        + v * std::sin(r1) * r2s
        + w * std::sqrt(1.0 - r2)).normalized();
}