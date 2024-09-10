// Noise functions over 1, 2, and 3 dimensions
float Noise::smoothNoise1(float arg)
{
  int bx0, bx1;
  float rx0, rx1, sx, t, u, v, vec;

  vec = arg;
  SETUP(vec, bx0, bx1, rx0, rx1);

  sx = SCURVE(rx0);

  u = rx0 * g1[p[bx0]];
  v = rx1 * g1[p[bx1]];

  return LERP(sx, u, v);
}