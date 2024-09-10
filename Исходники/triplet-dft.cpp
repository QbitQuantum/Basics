double pairdist_this_work_short(const Grid &gsigma, const Grid &density, const Grid &nA, const Grid &n3,
                                const Grid &nbar_sokolowski, Cartesian r0, Cartesian r1) {
  const Cartesian r01 = Cartesian(r0 - r1);
  const double r = sqrt(r01.dot(r01));
  return (short_range_radial_distribution(gsigma(r0), r) + short_range_radial_distribution(gsigma(r1), r))/2;
}