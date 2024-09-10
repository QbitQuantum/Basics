//
// Arguments    : const emxArray_real_T *Y
//                double no[32]
//                double xo[32]
// Return Type  : void
//
void hist(const emxArray_real_T *Y, double no[32], double xo[32])
{
  int k;
  int b_Y[1];
  emxArray_real_T c_Y;
  double maxy;
  double miny;
  double edges[33];
  int exponent;
  int d_Y[1];
  double nn[33];
  k = Y->size[0];
  if (k == 0) {
    for (k = 0; k < 32; k++) {
      xo[k] = 1.0 + (double)k;
      no[k] = 0.0;
    }
  } else {
    b_Y[0] = Y->size[0];
    c_Y = *Y;
    c_Y.size = (int *)&b_Y;
    c_Y.numDimensions = 1;
    MinAndMaxNoNonFinites(&c_Y, &miny, &maxy);
    if (miny == maxy) {
      miny = (miny - 16.0) - 0.5;
      maxy = (maxy + 16.0) - 0.5;
    }

    linspace(miny, maxy, edges);
    miny = (edges[1] - edges[0]) / 2.0;
    for (k = 0; k < 32; k++) {
      xo[k] = edges[k] + miny;
    }

    edges[0] = rtMinusInf;
    edges[32] = rtInf;
    for (k = 0; k < 31; k++) {
      miny = std::abs(edges[k + 1]);
      if ((!rtIsInf(miny)) && (!rtIsNaN(miny))) {
        if (miny <= 2.2250738585072014E-308) {
          miny = 4.94065645841247E-324;
        } else {
          frexp(miny, &exponent);
          miny = std::ldexp(1.0, exponent - 53);
        }
      } else {
        miny = rtNaN;
      }

      edges[k + 1] += miny;
    }

    d_Y[0] = Y->size[0];
    c_Y = *Y;
    c_Y.size = (int *)&d_Y;
    c_Y.numDimensions = 1;
    histc(&c_Y, edges, nn);
    memcpy(&no[0], &nn[0], sizeof(double) << 5);
    no[31] += nn[32];
  }
}