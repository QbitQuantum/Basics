  /* Fix the sign and return after stage 1 or stage 2 */
static double
signArctan2 (double y, double z)
{
  return __copysign (z, y);
}