// Very simple example code - sticks a sortkey in the buffer
// Not much error checking
int32_t getSortKey_current(const char *locale, const UChar *string, int32_t sLen, uint8_t *buffer, int32_t bLen) {
  UErrorCode status = U_ZERO_ERROR;
  UCollator *coll = ucol_open(locale, &status);
  if(U_FAILURE(status)) {
    return -1;
  }
  int32_t result = ucol_getSortKey(coll, string, sLen, buffer, bLen);
  ucol_close(coll);
  return result;  
}