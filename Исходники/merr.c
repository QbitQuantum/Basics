void __mingw_setusermatherr (int (__cdecl *f)(struct _exception *))
{
  stUserMathErr = f;
  __setusermatherr (f);
}