int smallestN(double r1, double r2, double r3) {
  double radianEPS = 1e-7;
  for (int n = 3; n <= 1000; ++n) {
    double segmentAngle = M_PI / n;
    double rem1 = remainder(r1, segmentAngle);
    double rem2 = remainder(r2, segmentAngle);
    double rem3 = remainder(r3, segmentAngle);
    if (fabs(rem1) < radianEPS && fabs(rem2) < radianEPS
      && fabs(rem3) < radianEPS) return n;
  }
  return -1;
}