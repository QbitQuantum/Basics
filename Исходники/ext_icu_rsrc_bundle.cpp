static Variant HHVM_STATIC_METHOD(ResourceBundle, getLocales,
                                                  const String& bundleName) {
  UErrorCode error = U_ZERO_ERROR;
  auto le = ures_openAvailableLocales(bundleName.c_str(), &error);
  if (U_FAILURE(error)) {
    s_intl_error->setError(error, "Cannot fetch locales list");
    return false;
  }
  error = U_ZERO_ERROR;
  uenum_reset(le, &error);
  if (U_FAILURE(error)) {
    s_intl_error->setError(error, "Cannot iterate locales list");
    return false;
  }

  Array ret = Array::Create();
  const char *entry;
  int32_t entry_len;
  while ((entry = uenum_next(le, &entry_len, &error))) {
    ret.append(String(entry, entry_len, CopyString));
  }
  return ret;
}