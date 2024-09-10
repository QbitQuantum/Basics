// Check the properties of a fundamental matrix:
//
//   1. The determinant is 0 (rank deficient)
//   2. The condition x'T*F*x = 0 is satisfied to precision.
//
bool ExpectFundamentalProperties(const Mat3 &F,
                                 const Mat &ptsA,
                                 const Mat &ptsB,
                                 double precision) {
  bool bOk = true;
  bOk &= F.determinant() < precision;
  assert(ptsA.cols() == ptsB.cols());
  const Mat hptsA = ptsA.colwise().homogeneous();
  const Mat hptsB = ptsB.colwise().homogeneous();
  for (int i = 0; i < ptsA.cols(); ++i) {
    const double residual = hptsB.col(i).dot(F * hptsA.col(i));
    bOk &= residual < precision;
  }
  return bOk;
}