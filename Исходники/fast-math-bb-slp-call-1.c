__attribute__((noinline, noclone)) void
f1 (void)
{
  a[0] = copysignf (b[0], c[0]) + 1.0f + sqrtf (d[0]);
  a[1] = copysignf (b[1], c[1]) + 2.0f + sqrtf (d[1]);
  a[2] = copysignf (b[2], c[2]) + 3.0f + sqrtf (d[2]);
  a[3] = copysignf (b[3], c[3]) + 4.0f + sqrtf (d[3]);
  a[4] = copysignf (b[4], c[4]) + 5.0f + sqrtf (d[4]);
  a[5] = copysignf (b[5], c[5]) + 6.0f + sqrtf (d[5]);
  a[6] = copysignf (b[6], c[6]) + 7.0f + sqrtf (d[6]);
  a[7] = copysignf (b[7], c[7]) + 8.0f + sqrtf (d[7]);
}