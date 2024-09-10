bool MessageFormatter::setPattern(const String& pattern) {
  UErrorCode error = U_ZERO_ERROR;
  icu::UnicodeString pat(u16(pattern, error));
  if (U_FAILURE(error)) {
    setError(error, "Error converting pattern to UTF-16");
    return false;
  }

#ifdef MSG_FORMAT_QUOTE_APOS
  if (!FixQuotes(pat)) {
    setError(U_INTERNAL_PROGRAM_ERROR,
             "msgfmt_set_pattern: error converting pattern to "
             "quote-friendly format");
    return false;
  }
#endif

  m_namedParts.clear();
  m_numericParts.clear();
  m_tzSet = false;
  m_usesDate = false;

  error = U_ZERO_ERROR;
  umsg_applyPattern(formatter(),
                    pat.getBuffer(), pat.length(),
                    nullptr, &error);
  if (U_FAILURE(error)) {
    setError(error, "Error setting symbol value");
    return false;
  }

  return true;
}