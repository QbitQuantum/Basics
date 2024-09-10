double SO3_beta(const int m1, const int m2, const int j)
{
  if (j < 0)
    return K(0.0);
  else if (j < MAX(ABS(m1),ABS(m2)))
    return K(0.5);
  else if (m1 == 0 || m2 == 0)
    return K(0.0);
  else
  {
    const R m1a = FABS((R)m1), m2a = FABS((R)m2);
    return -COPYSIGN(
      ((SQRT(m1a)*SQRT(m2a))/((R)j))
      * SQRT(m1a/((R)(j+1-m1)))
      * SQRT(((R)(2*j+1))/((R)(j+1+m1)))
      * SQRT(m2a/((R)(j+1-m2)))
      * SQRT(((R)(2*j+1))/((R)(j+1+m2))),
      SIGNF((R)m1)*SIGNF((R)m2));
  }
}