UnicodeString 
MessageFormat::autoQuoteApostrophe(const UnicodeString& pattern, UErrorCode& status) {
  UnicodeString result;
  if (U_SUCCESS(status)) {
    int32_t plen = pattern.length();
    const UChar* pat = pattern.getBuffer();
    int32_t blen = plen * 2 + 1; // space for null termination, convenience
    UChar* buf = result.getBuffer(blen);
    if (buf == NULL) {
      status = U_MEMORY_ALLOCATION_ERROR;
    } else {
      int32_t len = umsg_autoQuoteApostrophe(pat, plen, buf, blen, &status);
      result.releaseBuffer(U_SUCCESS(status) ? len : 0);
    }
  }
  if (U_FAILURE(status)) {
    result.setToBogus();
  }
  return result;
}