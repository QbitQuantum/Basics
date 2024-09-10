static Variant HHVM_STATIC_METHOD(Locale, acceptFromHttp,
                                  const String& header) {
  UErrorCode error = U_ZERO_ERROR;
  UEnumeration *avail = ures_openAvailableLocales(nullptr, &error);
  ULOC_CHECK(error, false);
  char out[MAX_LOCALE_LEN];
  UAcceptResult result;
  error = U_ZERO_ERROR;
  int len = uloc_acceptLanguageFromHTTP(out, sizeof(out), &result,
                                        header.c_str(), avail, &error);
  uenum_close(avail);
  ULOC_CHECK(error, false);
  if (len < 0 || result == ULOC_ACCEPT_FAILED) {
    return false;
  }
  return String(out, len, CopyString);
}