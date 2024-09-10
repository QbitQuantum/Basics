int ProjectContextFormatString(char *outbuf, size_t outbuf_size, const char *fmt, va_list va)
{
  int wroffs=0;

  while (*fmt && outbuf_size > 1)
  {
    char c = *fmt++;
    if (c != '%') 
    {
      outbuf[wroffs++] = c;
      outbuf_size--;
      continue;
    }

    if (*fmt == '%')
    {
      outbuf[wroffs++] = '%';
      outbuf_size--;
      fmt++;
      continue;
    }


    const char *ofmt = fmt-1;
    bool want_abort=false;

    int has_prec=0;
    int prec=0;
    if (*fmt == '.')
    {
      has_prec=1;
      fmt++;
      while (*fmt >= '0' && *fmt <= '9') prec = prec*10 + (*fmt++-'0');
      if (*fmt != 'f' || prec < 0 || prec>20)
      {
        want_abort=true;
      }
    }
    else if (*fmt == '0')
    {
      has_prec=2;
      fmt++;
      while (*fmt >= '0' && *fmt <= '9') prec = prec*10 + (*fmt++-'0');
      if (*fmt != 'x' && *fmt != 'X' && *fmt != 'd' && *fmt != 'u')
      {
        want_abort=true;
      }
    }

    c = *fmt++;
    if (!want_abort) switch (c)
    {
      case '@':
      case 'p':
      case 's':
      {
        const char *str=va_arg(va,const char *);
        const char qc = outbuf_size >= 3 && c != 's' ? getConfigStringQuoteChar(str) : ' ';
        
        if (qc != ' ')
        {
          outbuf[wroffs++] = qc ? qc : '`';
          outbuf_size-=2; // will add trailing quote below
        }
        
        if (str) while (outbuf_size > 1 && *str)
        {
          char v = *str++;
          if (!qc && v == '`') v = '\'';
          outbuf[wroffs++] = v;
          outbuf_size--;
        }

        if (qc != ' ')
        {
          outbuf[wroffs++] = qc ? qc : '`';
          // outbuf_size already decreased above
        }
      }
      break;
      case 'c':
      {
        int v = va_arg(va,int);
        outbuf[wroffs++] = v&0xff;
        outbuf_size--;
      }
      break;
      case 'd':
      {
        int v = va_arg(va,int);
        if (v<0)
        {
          outbuf[wroffs++] = '-';
          outbuf_size--;
          v=-v; // this won't handle -2147483648 right, todo special case?
        }

        char tab[32];
        int x=0;
        do
        {
          tab[x++] = v%10;
          v/=10;
        }
        while (v);
        if (has_prec == 2) while (x<prec) { tab[x++] = 0; }

        while (--x >= 0 && outbuf_size>1)
        {
          outbuf[wroffs++] = '0' + tab[x];
          outbuf_size--;
        }
      }
      break;
      case 'u':
      {
        unsigned int v = va_arg(va,unsigned int);

        char tab[32];
        int x=0;
        do
        {
          tab[x++] = v%10;
          v/=10;
        }
        while (v);
        if (has_prec == 2) while (x<prec) { tab[x++] = 0; }

        while (--x >= 0 && outbuf_size>1)
        {
          outbuf[wroffs++] = '0' + tab[x];
          outbuf_size--;
        }
      }
      break;
      case 'x':
      case 'X':
      {
        const char base = (c - 'x') + 'a';
        unsigned int v = va_arg(va,unsigned int);

        char tab[32];
        int x=0;
        do
        {
          tab[x++] = v&0xf;
          v>>=4;
        }
        while (v);
      
        if (has_prec == 2) while (x<prec) { tab[x++] = 0; }

        while (--x >= 0 && outbuf_size>1)
        {
          if (tab[x] < 10)
            outbuf[wroffs++] = '0' + tab[x];
          else 
            outbuf[wroffs++] = base + tab[x] - 10;

          outbuf_size--;
        }
      }
      break;
      case 'f':
      {
        double v = va_arg(va,double);
        if (outbuf_size<64)
        {
          char tmp[64];
          projectcontext_fastDoubleToString(v,tmp,has_prec?prec:6);
          const char *str = tmp;
          while (outbuf_size > 1 && *str)
          {
            outbuf[wroffs++] = *str++;
            outbuf_size--;
          }
        }
        else
        {
          const char *p=projectcontext_fastDoubleToString(v,outbuf+wroffs,has_prec?prec:6);
          int amt = (int) (p-(outbuf+wroffs));
          wroffs += amt;
          outbuf_size-=amt;
        }
      }
      break;
      default:
        want_abort=true;
      break;
    }   
    if (want_abort)
    {
#if defined(_WIN32) && defined(_DEBUG)
      OutputDebugString("ProjectContextFormatString(): falling back to stock vsnprintf because of:");
      OutputDebugString(ofmt);
#endif
      fmt=ofmt;
      break;
    }
  }

  outbuf += wroffs;
  outbuf[0] = 0;
  if (outbuf_size<2||!*fmt)
    return wroffs;

#if defined(_WIN32) && defined(_MSC_VER)
  const int l = _vsnprintf(outbuf,outbuf_size,fmt,va); // _vsnprintf() does not always null terminate
  if (l < 0 || l >= (int)outbuf_size)
  {
    outbuf[outbuf_size-1] = 0;
    return wroffs + (int)strlen(outbuf);
  }
#else
  // vsnprintf() on non-win32, always null terminates
  const int l = vsnprintf(outbuf,outbuf_size,fmt,va);
  if (l >= (int)outbuf_size-1) return wroffs + (int)outbuf_size-1;
#endif
  return wroffs+l;
}