char *
int2str(register long int val, register char *dst, register int radix, 
        int upcase)
{
  char buffer[65];
  register char *p;
  long int new_val;
  char *dig_vec= upcase ? _dig_vec_upper : _dig_vec_lower;

  if (radix < 0)
  {
    if (radix < -36 || radix > -2)
      return NullS;
    if (val < 0)
    {
      *dst++ = '-';
      val = -val;
    }
    radix = -radix;
  }
  else if (radix > 36 || radix < 2)
    return NullS;

  /*
    The slightly contorted code which follows is due to the fact that
    few machines directly support unsigned long / and %.  Certainly
    the VAX C compiler generates a subroutine call.  In the interests
    of efficiency (hollow laugh) I let this happen for the first digit
    only; after that "val" will be in range so that signed integer
    division will do.  Sorry 'bout that.  CHECK THE CODE PRODUCED BY
    YOUR C COMPILER.  The first % and / should be unsigned, the second
    % and / signed, but C compilers tend to be extraordinarily
    sensitive to minor details of style.  This works on a VAX, that's
    all I claim for it.
  */
  p = &buffer[sizeof(buffer)-1];
  *p = '\0';
  new_val=(ulong) val / (ulong) radix;
  *--p = dig_vec[(uchar) ((ulong) val- (ulong) new_val*(ulong) radix)];
  val = new_val;
#ifdef HAVE_LDIV
  while (val != 0)
  {
    ldiv_t res;
    res=ldiv(val,radix);
    *--p = dig_vec[res.rem];
    val= res.quot;
  }
#else
  while (val != 0)
  {
    new_val=val/radix;
    *--p = dig_vec[(uchar) (val-new_val*radix)];
    val= new_val;
  }
#endif
  while ((*dst++ = *p++) != 0) ;
  return dst-1;
}