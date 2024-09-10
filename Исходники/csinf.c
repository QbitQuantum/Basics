float complex csinf (float complex Z)
{
  float complex Res;
  __real__ Res = sinf (__real__ Z) * coshf ( __imag__ Z);
  __imag__ Res = cosf (__real__ Z) * sinhf ( __imag__ Z);
  return Res;
}