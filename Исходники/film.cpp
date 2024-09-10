static float filter_func_gaussian(float v, float width)
{
  v *= 6.0f / width;
  return expf(-2.0f * v * v);
}