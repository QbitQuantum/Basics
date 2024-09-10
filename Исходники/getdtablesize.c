static inline int
_setmaxstdio_nothrow (int newmax)
{
  int result;

  TRY_MSVC_INVAL
    {
      result = _setmaxstdio (newmax);
    }
  CATCH_MSVC_INVAL
    {
      result = -1;
    }
  DONE_MSVC_INVAL;

  return result;
}