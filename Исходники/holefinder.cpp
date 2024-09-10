Eigen::Vector3d HoleFinder::getRandomPoint()
{
  Q_D(HoleFinder);

  // Randomly select a hole
  const Hole &hole = d->getRandomHole();

  // Trim the radius of the sphere by 1.5 units. If the sphere is smaller than
  // 1.5 units, trim it to 0.5 units.
  const double rmax = (hole.radius >= d->minDist)
      ? hole.radius - d->minDist : 0.5;

  // Randomly select point from uniform distribution around sphere. The radius
  // is chosen such that
  //
  // P(r) [is prop. to] Area(r) = 4*pi*r^2, or
  // P(r) = N * 4*pi*r^2
  //
  // We want P(r) to lie between [0,1] and r to be between [0, rmax].
  //
  // Lower boundary conditions are trivially satisfied:
  //
  // P(0) = N * 4*pi*0^2 = 0
  //
  // Upper boundary conditions:
  //
  // P(rmax) = 1 = N * 4*pi*rmax^2, or
  // N = 1 / (4*pi*rmax^2)
  //
  // So P(r) simplifies to
  //
  // P(r) = (1/(4*pi*r^2)) * 4*pi*r^2 = r^2 / (rmax^2)
  //
  // So we can pick a "p" value from a uniform distribution from [0,1] and
  // transform it to a random radius that is uniformly distributed throughout
  // the sphere by
  const double p = RANDDOUBLE();
  const double r = sqrt(p) * rmax;

  // A random unit vector representing the displacement:
  Eigen::Vector3d displacement (2.0 * RANDDOUBLE() - 1.0,
                                2.0 * RANDDOUBLE() - 1.0,
                                2.0 * RANDDOUBLE() - 1.0);
  displacement.normalize();

  // Put the two together
  displacement *= r;

  // Shift by the hole's origin
  const Eigen::Vector3d ret (hole.center + displacement);

  // Ta-da!
  return ret;
}