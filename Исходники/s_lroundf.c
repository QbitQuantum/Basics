long int
__lroundf (float x)
{
  float adj;

  adj = 0x1.fffffep-2;		/* nextafterf (0.5f, 0.0f) */
  adj = copysignf (adj, x);
  return x + adj;
}