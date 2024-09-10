static String HHVM_METHOD(Collator, getLocale, int64_t type) {
  FETCH_COL(data, this_, "");
  data->clearError();
  UErrorCode error = U_ZERO_ERROR;
  auto loc = ucol_getLocaleByType(data->collator(), (ULocDataLocaleType)type,
                                  &error);
  if (U_FAILURE(error)) {
    data->setError(error, "Error getting locale by type");
  }
  return String(loc, CopyString);
}