complex __ccos(float zreal, float zimag)
{
  complex r;

  r.real = cosf(zreal) * coshf(zimag);
  r.imag = - sinf(zreal) * sinhf(zimag);
  return r;
}