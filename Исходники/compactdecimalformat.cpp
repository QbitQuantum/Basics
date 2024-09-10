// populatePower10 grabs data for a particular power of 10 from CLDR.
// The loaded data is stored in result.
static void populatePower10(const UResourceBundle* power10Bundle, CDFLocaleStyleData* result, UErrorCode& status) {
  if (U_FAILURE(status)) {
    return;
  }
  char* endPtr = NULL;
  double power10 = uprv_strtod(ures_getKey(power10Bundle), &endPtr);
  if (*endPtr != 0) {
    status = U_INTERNAL_PROGRAM_ERROR;
    return;
  }
  int32_t log10Value = computeLog10(power10, FALSE);
  // Silently ignore divisors that are too big.
  if (log10Value == MAX_DIGITS) {
    return;
  }
  int32_t size = ures_getSize(power10Bundle);
  int32_t numZeros = 0;
  UBool otherVariantDefined = FALSE;
  UResourceBundle* variantBundle = NULL;
  // Iterate over all the plural variants for the power of 10
  for (int32_t i = 0; i < size; ++i) {
    variantBundle = ures_getByIndex(power10Bundle, i, variantBundle, &status);
    if (U_FAILURE(status)) {
      ures_close(variantBundle);
      return;
    }
    const char* variant = ures_getKey(variantBundle);
    int32_t resLen;
    const UChar* formatStrP = ures_getString(variantBundle, &resLen, &status);
    if (U_FAILURE(status)) {
      ures_close(variantBundle);
      return;
    }
    UnicodeString formatStr(false, formatStrP, resLen);
    if (uprv_strcmp(variant, gOther) == 0) {
      otherVariantDefined = TRUE;
    }
    int32_t nz = populatePrefixSuffix(
        variant, log10Value, formatStr, result->unitsByVariant, status);
    if (U_FAILURE(status)) {
      ures_close(variantBundle);
      return;
    }
    if (nz != numZeros) {
      // We expect all format strings to have the same number of 0's
      // left of the decimal point.
      if (numZeros != 0) {
        status = U_INTERNAL_PROGRAM_ERROR;
        ures_close(variantBundle);
        return;
      }
      numZeros = nz;
    }
  }
  ures_close(variantBundle);
  // We expect to find an OTHER variant for each power of 10.
  if (!otherVariantDefined) {
    status = U_INTERNAL_PROGRAM_ERROR;
    return;
  }
  double divisor = power10;
  for (int32_t i = 1; i < numZeros; ++i) {
    divisor /= 10.0;
  }
  result->divisors[log10Value] = divisor;
}