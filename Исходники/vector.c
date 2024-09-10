void Transform(MATRIX a, VECTOR u, VECTOR v)
{
  /* Applies matrix "a" to vector "u", returning vector "v" */

  v[X] = DOT(a[X], u);
  v[Y] = DOT(a[Y], u);
  v[Z] = DOT(a[Z], u);
}