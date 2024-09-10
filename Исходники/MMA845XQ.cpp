float MMA845XQ::geta2d(float gx, float gy)
{
  float a;
  
  a = gx * gx;
  a = fma(gy,gy,a);
  
  return sqrt(a);
}