int soap_s2xsd__duration(struct soap *soap, const char *s, LONG64 *a)
{ LONG64 sign = 1, Y = 0, M = 0, D = 0, H = 0, N = 0, S = 0;
  float f = 0;
  *a = 0;
  if (s)
  { if (*s == '-')
    { sign = -1;
      s++;
    }
    if (*s != 'P' && *s != 'p')
      return soap->error = SOAP_TYPE;
    s++;
    /* date part */
    while (s && *s)
    { char *r = NULL;
      LONG64 n;
      if (*s == 'T' || *s == 't')
      { s++;
	break;
      }
      n = soap_strtol(s, &r, 10);
      if (!r)
	return soap->error = SOAP_TYPE;
      s = r;
      switch (*s)
      { case 'Y':
        case 'y':
	  Y = n;
	  break;
	case 'M':
	case 'm':
	  M = n;
	  break;
	case 'D':
	case 'd':
	  D = n;
	  break;
	default:
	  return soap->error = SOAP_TYPE;
      }
      s++;
    }
    /* time part */
    while (s && *s)
    { char *r = NULL;
      LONG64 n;
      n = soap_strtol(s, &r, 10);
      if (!r)
	return soap->error = SOAP_TYPE;
      s = r;
      switch (*s)
      { case 'H':
        case 'h':
	  H = n;
	  break;
	case 'M':
	case 'm':
	  N = n;
	  break;
	case '.':
	  S = n;
#if defined(WITH_C_LOCALE) && defined(HAVE_STRTOD_L)
# ifdef WIN32
          f = (float)_strtod_l(s, NULL, SOAP_LOCALE(soap));
# else
          f = (float)strtod_l(s, NULL, SOAP_LOCALE(soap));
# endif
#elif defined(HAVE_STRTOD)
          f = (float)strtod(s, NULL);
#elif defined(WITH_C_LOCALE) && defined(HAVE_STRTOF_L)
          f = strtof_l((char*)s, NULL, SOAP_LOCALE(soap));
#elif defined(HAVE_STRTOF)
          f = strtof((char*)s, NULL);
#endif
	  s = NULL;
	  continue;
	case 'S':
	case 's':
	  S = n;
	  break;
	default:
	  return soap->error = SOAP_TYPE;
      }
      s++;
    }
    /* convert Y-M-D H:N:S.f to signed long long int milliseconds */
    *a = sign * ((((((((((((Y * 12) + M) * 30) + D) * 24) + H) * 60) + N) * 60) + S) * 1000) + (LONG64)(1000.0 * f + 0.5));
  }
  return soap->error;
}