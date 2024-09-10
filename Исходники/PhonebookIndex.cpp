int32_t GetPhonebookIndex(UCharIterator * iter, const char * locale, UChar * out, int32_t size,
        UBool * isError)
{
  if (size < MIN_OUTPUT_SIZE) {
    *isError = TRUE;
    return 0;
  }

  *isError = FALSE;

  // Normalize the first character to remove accents using the NFD normalization
  UErrorCode errorCode = U_ZERO_ERROR;
  int32_t len = unorm_next(iter, out, size, UNORM_NFD,
          0 /* options */, TRUE /* normalize */, NULL, &errorCode);
  if (U_FAILURE(errorCode)) {
    *isError = TRUE;
    return 0;
  }

  if (len == 0) {   // Empty input string
    return 0;
  }

  UChar c = out[0];

  // We are only interested in letters
  if (!u_isalpha(c)) {
    return 0;
  }

  c = u_toupper(c);

  // Check for explicitly mapped characters
  UChar c_mapped = map_character(c, DEFAULT_CHAR_MAP, sizeof(DEFAULT_CHAR_MAP) / sizeof(UChar));
  if (c_mapped != 0) {
    out[0] = c_mapped;
    return 1;
  }

  // Convert Kanas to Hiragana
  UChar next = len > 2 ? out[1] : 0;
  c = android::GetNormalizedCodePoint(c, next, NULL);

  // Traditional grouping of Hiragana characters
  if (0x3042 <= c && c <= 0x309F) {
    if (c < 0x304B) c = 0x3042;         // a
    else if (c < 0x3055) c = 0x304B;    // ka
    else if (c < 0x305F) c = 0x3055;    // sa
    else if (c < 0x306A) c = 0x305F;    // ta
    else if (c < 0x306F) c = 0x306A;    // na
    else if (c < 0x307E) c = 0x306F;    // ha
    else if (c < 0x3084) c = 0x307E;    // ma
    else if (c < 0x3089) c = 0x3084;    // ya
    else if (c < 0x308F) c = 0x3089;    // ra
    else c = 0x308F;                    // wa
    out[0] = c;
    return 1;
  }

  if (is_CJK(c)) {
    if (strncmp(locale, "ja", 2) == 0) {
      // Japanese word meaning "misc" or "other"
      out[0] = 0x4ED6;
      return 1;
    } else {
      return 0;
    }
  }

  out[0] = c;
  return 1;
}