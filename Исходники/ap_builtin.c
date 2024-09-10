/* DO_DIST: Calculate distance between point 1 at (x1,y1) and
 *          point 2 at (x2,y2).
 */
double do_dist(double x1, double y1, double x2, double y2)
{
  double temp;
  errno = 0;
  temp = HYPOT((x1 - x2), (y1 - y2));
  MATH_ERROR("hypot");
  return (temp);
}