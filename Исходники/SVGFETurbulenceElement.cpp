double
SVGFETurbulenceElement::Noise2(int aColorChannel, double aVec[2],
                               StitchInfo *aStitchInfo)
{
  int bx0, bx1, by0, by1, b00, b10, b01, b11;
  double rx0, rx1, ry0, ry1, *q, sx, sy, a, b, t, u, v;
  long i, j;
  t = aVec[0] + sPerlinN;
  bx0 = (int) t;
  bx1 = bx0 + 1;
  rx0 = t - (int) t;
  rx1 = rx0 - 1.0f;
  t = aVec[1] + sPerlinN;
  by0 = (int) t;
  by1 = by0 + 1;
  ry0 = t - (int) t;
  ry1 = ry0 - 1.0f;
  // If stitching, adjust lattice points accordingly.
  if (aStitchInfo != NULL) {
    if (bx0 >= aStitchInfo->mWrapX)
      bx0 -= aStitchInfo->mWidth;
    if (bx1 >= aStitchInfo->mWrapX)
      bx1 -= aStitchInfo->mWidth;
    if (by0 >= aStitchInfo->mWrapY)
      by0 -= aStitchInfo->mHeight;
    if (by1 >= aStitchInfo->mWrapY)
      by1 -= aStitchInfo->mHeight;
  }
  bx0 &= sBM;
  bx1 &= sBM;
  by0 &= sBM;
  by1 &= sBM;
  i = mLatticeSelector[bx0];
  j = mLatticeSelector[bx1];
  b00 = mLatticeSelector[i + by0];
  b10 = mLatticeSelector[j + by0];
  b01 = mLatticeSelector[i + by1];
  b11 = mLatticeSelector[j + by1];
  sx = double (S_CURVE(rx0));
  sy = double (S_CURVE(ry0));
  q = mGradient[aColorChannel][b00];
  u = rx0 * q[0] + ry0 * q[1];
  q = mGradient[aColorChannel][b10];
  v = rx1 * q[0] + ry0 * q[1];
  a = LERP(sx, u, v);
  q = mGradient[aColorChannel][b01];
  u = rx0 * q[0] + ry1 * q[1];
  q = mGradient[aColorChannel][b11];
  v = rx1 * q[0] + ry1 * q[1];
  b = LERP(sx, u, v);
  return LERP(sy, a, b);
}