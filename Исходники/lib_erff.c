float erff(float x)
{
  float t;
  float z;

  z = fabsf(x);
  t = 1.0F / (1.0F + P * z);
  t = 1.0F - (((((A5 * t + A4) * t) + A3) * t + A2) * t + A1) * t * expf(-z * z);
  return copysignf(t, x);
}