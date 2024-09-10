CFStringEncoding
CFStringGetSystemEncoding (void)
{
#if defined(_WIN32)
  return kCFStringEncodingASCII;
#else
  if (_kCFStringSystemEncoding == kCFStringEncodingInvalidId)
    {
      GSMutexLock (&_kCFStringEncodingLock);
      if (_kCFStringSystemEncoding == kCFStringEncodingInvalidId)
        {
          const char *name;
          const char *defaultName;
          UErrorCode err = U_ZERO_ERROR;

          defaultName = ucnv_getDefaultName ();
          name = ucnv_getStandardName (defaultName, "MIME", &err);
          if (name != NULL)
            {
              _kCFStringSystemEncoding =
                CFStringConvertStandardNameToEncoding (name, -1);
            }
          else
            {
              name = ucnv_getStandardName (defaultName, "IANA", &err);
              if (name != NULL)
                _kCFStringSystemEncoding =
                  CFStringConvertStandardNameToEncoding (name, -1);
              else
                _kCFStringSystemEncoding = kCFStringEncodingInvalidId;
            }
        }
      GSMutexUnlock (&_kCFStringEncodingLock);
    }
  return _kCFStringSystemEncoding;
#endif
}