void
f (double *r, __m128d x, __m128d y, __m128d z)
{
  __m128d t=_mm_move_sd(x,y);
  __m128d u=_mm_move_sd(t,z);
  *r = u[0];
}