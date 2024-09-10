char    *dbl2str        (double d, int p, char buf[], int n)
{
#if 0

  /* 
   * <sign>     1 char
   * <e>        1 char
   * <sign>     1 char
   * <exponent> 1-3 chars
   *
   * Also, if the field width is less than the precision
   * (significant digits), then the latter will have to
   * be decreased in order to avoid over-running the buffer.
   *
   * In order to determine the appropriate precision, if it must
   * be decreased, we need to know whether or not the converted
   * number will include an exponent, and if so, how many digits
   * the exponent will include.
   */
#define STR_SIZE        1023
  static char           str[STR_SIZE+1];
  
  sprintf (str, "% #*.*g", n, p);
  strncpy (buf, str, n);
  buf[n] = 0;
  
#else
  int   decpt, sign;
  char  tmp[MAX_LEN+1];
  char  e_str[EXP_LEN+1];
  char  e_cnt;
  int   i = 0, j = 0;

  memset (e_str, EXP_LEN+1, 1);
  e_str[0] = 'e';

  strcpy (tmp, ecvt (d, n, &decpt, &sign));
  buf[i++] = sign? '-' : ' ';
                   
  e_str[1] = (decpt > 0? '+' : '-');
  
  if (decpt > 0)                /* magnitude >= 1? */
  {
    if (p > 0)          /* print some digits after decimal point */
    {
      if (decpt+p > n-2)        /* need scientific notation */
      {
        int2str (decpt-1, &e_str[2], 2);
        for (e_cnt = 0; e_str[(int)e_cnt]; e_cnt++);
        if (e_cnt+2 > n) goto no_room;
        buf[i++] = tmp[j++];
        if (i < n-e_cnt-1)
        {
          buf[i++] = '.';
          while (i < n-EXP_LEN) buf[i++] = tmp[j++];
        }
        strcpy (&buf[i], e_str);
      }
      else                      /* print out d+p digits */
      {
        for (; decpt > 0; decpt--) buf[i++] = tmp[j++];
        buf[i++] = '.';
        for (; p > 0; p--) buf[i++] = tmp[j++];
        buf[i++] = '\0';
      }
    }
    else                        /* not interested in digits after decimal */
    {
      if (decpt > n-1)          /* need scientific notation */
      {
        
      }
      else while (i < decpt+1) buf[i++] = tmp[j++];
      buf[i++] = 0;
    }
  }
  else                          /* magnitude < 1*/
  {
    if (p > 0)          /* */
    {
      if (p+decpt > 0)          /* print some digits out */
      {
        if (p-decpt > n-3)      /* need scientific notation */
        {
          int2str (-(decpt-1), &e_str[2], 2);
          for (e_cnt = 0; e_str[(int)e_cnt]; e_cnt++);
          if (e_cnt+2 > n) goto no_room;
          buf[i++] = tmp[j++];
          if (i < n-e_cnt-1)
          {
            buf[i++] = '.';
            while (i < n-e_cnt) buf[i++] = tmp[j++];
          }
          strcpy (&buf[i], e_str);
        }
        else            /* print 0.(-decpt zeroes)(p+decpt digits) */
        {
          buf[i++] = '0';
          buf[i++] = '.';
          p += decpt;
          for (; decpt < 0; decpt++) buf[i++] = '0';
          for (; p > 0; p--) buf[i++] = tmp[j++];
          buf[i++] = '\0';
        }
      }
      else                      /* number too small --effectively zero */
      {
        buf[i++] = '0';
        buf[i++] = '.';
        for (; (i < n) && (p > 0); p--) buf[i++] = '0';
        buf[i++] = '\0';
      }
    }
    else                        /* effectively zero */
    {
      buf[i++] = '0';
      buf[i++] = '\0';
    }
  }
  
  return buf;

  no_room:
  for (i = 0; i < n; i++) buf[i] = '#';
  buf[i++] = '\0';
  return buf;
#endif
}