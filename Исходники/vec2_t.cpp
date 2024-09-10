bool intersect(vec_t & r, const vec_t & u1, const vec_t & u2, const vec_t & v1, const vec_t & v2) {
  const long double m11 = u1.x - u2.x, m12 = u1.y - u2.y;
  const long double m21 = v2.x - v1.x, m22 = v2.y - v1.y;

  const long double det = m11*m22 - m12*m21;

  if( fabsl(det) < eps )
    return false;

  const long double r11 =  m22, r12 = -m12;
  const long double r21 = -m21, r22 =  m11;

  const long double a = u1.x - v1.x, b = u1.y - v1.y;

  const long double t = (a*r11 + b*r21)/det, s = (a*r12 + b*r22)/det;

  r = u1 + (u2 - u1)*t;

  return true;
}