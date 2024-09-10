float
asinhf(float x)
{
  float z;
  if (!isfinite (x))
    return x;
  z = fabsf (x);

  /* Avoid setting FPU underflow exception flag in x * x. */
#if 0
  if ( z < 0x1p-32)
    return x;
#endif


  /* Use log1p to avoid cancellation with small x. Put
     x * x in denom, so overflow is harmless. 
     asinh(x) = log1p (x + sqrt (x * x + 1.0) - 1.0)
              = log1p (x + x * x / (sqrt (x * x + 1.0) + 1.0))  */

  z = log1p (z + z * z / (sqrt (z * z + 1.0) + 1.0));

  return ( x >= 0.0 ? z : -z);
}