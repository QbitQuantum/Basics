float complex CLANG_PORT_DECL(ccoshf) (float complex Z)
{
  float complex Res;
  __real__ Res = coshf (__real__ Z) * cosf (__imag__ Z);
  __imag__ Res = sinhf (__real__ Z) * sinf (__imag__ Z);
  return Res;
}