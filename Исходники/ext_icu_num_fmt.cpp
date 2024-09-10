static String HHVM_METHOD(NumberFormatter, getLocale, int64_t type) {
  NUMFMT_GET(obj, this_, String());
  UErrorCode error = U_ZERO_ERROR;
  const char *loc = unum_getLocaleByType(obj->formatter(),
                                         (ULocDataLocaleType)type, &error);
  NUMFMT_CHECK(obj, error, String());
  return String(loc, CopyString);
}