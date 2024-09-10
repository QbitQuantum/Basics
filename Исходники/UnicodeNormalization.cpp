static intptr_t hashChunk(const UCollator *Collator, intptr_t HashState,
                          const uint16_t *Str, uint32_t Length,
                          UErrorCode *ErrorCode) {
  UCollationElements *CollationIterator = ucol_openElements(
    Collator, Str, Length, ErrorCode);
  while (U_SUCCESS(*ErrorCode)) {
    intptr_t Elem = ucol_next(CollationIterator, ErrorCode);
    // Ignore zero valued collation elements. They don't participate in the
    // ordering relation.
    if (Elem == 0)
      continue;
    if (Elem != UCOL_NULLORDER) {
      Elem *= HASH_M;
      Elem ^= Elem >> HASH_R;
      Elem *= HASH_M;

      HashState *= HASH_M;
      HashState ^= Elem;
    } else {
      break;