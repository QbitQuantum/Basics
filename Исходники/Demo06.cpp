VECTOR4D SinCosNormal(float x, float y, float z) {
  VECTOR4D N = { 0.3f * 3.0f * PI * sin(3.0f * x * PI) * sinf(3.0f * y * PI), -0.3f * 3.0f * PI * cosf(3.0f * x * PI) * cos(3.0f * y * PI), 1.0f, 0.0f };
  N = Normalize(N);
  return N;
}