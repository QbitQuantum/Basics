static Variant HHVM_STATIC_METHOD(IntlCalendar, getKeywordValuesForLocale,
                                 const String& key, const String& locale,
                                 bool common) {
  UErrorCode error = U_ZERO_ERROR;
  UEnumeration *uenum = ucal_getKeywordValuesForLocale(key.c_str(),
                                   ULOC_DEFAULT(locale).c_str(),
                                   common, &error);
  if (U_FAILURE(error)) {
    if (uenum) { uenum_close(uenum); }
    s_intl_error->set(error, "intlcal_get_keyword_values_for_locale: "
                             "error calling underlying method");
    return false;
  }
  return IntlIterator::newInstance(new BugStringCharEnumeration(uenum));
}