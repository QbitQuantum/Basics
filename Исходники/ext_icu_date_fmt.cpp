static String HHVM_METHOD(IntlDateFormatter, getLocale, CVarRef which) {
  ULocDataLocaleType whichloc = ULOC_ACTUAL_LOCALE;
  if (!which.isNull()) whichloc = (ULocDataLocaleType)which.toInt64();

  DATFMT_GET(data, this_, null_string);
  UErrorCode error = U_ZERO_ERROR;
  const char *loc = udat_getLocaleByType(data->datefmt(), whichloc, &error);
  if (U_FAILURE(error)) {
    data->setError(error);
    return null_string;
  }
  return String(loc, CopyString);
}