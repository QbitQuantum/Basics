static float fclamp0(float x, float max) {
  x = (x + max - fabsf(x - max))/2.0f;
  return (x + fabsf(x))/2.0f;
}