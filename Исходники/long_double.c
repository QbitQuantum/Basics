const char *soap_decimal2s(struct soap *soap, long double n)
{
#if !defined(WITH_C_LOCALE) || !defined(HAVE_SPRINTF_L)
  char *s;
#endif
  if (soap_isnan(n))
    return "NaN";
  if (soap_ispinfd(n))
    return "INF";
  if (soap_isninfd(n))
    return "-INF";
#if defined(WITH_C_LOCALE) && defined(HAVE_SPRINTF_L)
# ifdef WIN32
  _sprintf_s_l(soap->tmpbuf, _countof(soap->tmpbuf), "%.*Lg", SOAP_LOCALE(soap), LDBL_DIG, n);
# else
  sprintf_l(soap->tmpbuf, SOAP_LOCALE(soap), "%.*Lg", LDBL_DIG, n);
# endif
#else
  (SOAP_SNPRINTF(soap->tmpbuf, sizeof(soap->tmpbuf), LDBL_DIG + 8), "%.*Lg", LDBL_DIG, n);
  s = strchr(soap->tmpbuf, ',');	/* convert decimal comma to DP */
  if (s)
    *s = '.';
#endif
  return soap->tmpbuf;
}