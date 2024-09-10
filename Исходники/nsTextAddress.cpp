bool nsTextAddress::GetField(const nsAString &aLine, int32_t index,
                             nsString &field, char16_t delim) {
  bool result = false;
  int32_t pos = 0;
  int32_t maxLen = aLine.Length();
  char16_t tab = char16_t('\t');
  char16_t doubleQuote = char16_t('"');

  field.Truncate();

  if (delim == tab) tab = 0;

  while (index && (pos < maxLen)) {
    while (((aLine[pos] == char16_t(' ')) || (aLine[pos] == tab)) &&
           (pos < maxLen)) {
      pos++;
    }
    if (pos >= maxLen) break;
    if (aLine[pos] == doubleQuote) {
      do {
        pos++;
        if (((pos + 1) < maxLen) && (aLine[pos] == doubleQuote) &&
            (aLine[pos + 1] == doubleQuote)) {
          pos += 2;
        }
      } while ((pos < maxLen) && (aLine[pos] != doubleQuote));
      if (pos < maxLen) pos++;
    }
    if (pos >= maxLen) break;

    while ((pos < maxLen) && (aLine[pos] != delim)) pos++;

    if (pos >= maxLen) break;

    index--;
    pos++;
  }

  if (pos >= maxLen) return result;

  result = true;

  while ((pos < maxLen) && ((aLine[pos] == ' ') || (aLine[pos] == tab))) pos++;

  int32_t fLen = 0;
  int32_t startPos = pos;
  bool quoted = false;
  if (aLine[pos] == '"') {
    startPos++;
    fLen = -1;
    do {
      pos++;
      fLen++;
      if (((pos + 1) < maxLen) && (aLine[pos] == doubleQuote) &&
          (aLine[pos + 1] == doubleQuote)) {
        quoted = true;
        pos += 2;
        fLen += 2;
      }
    } while ((pos < maxLen) && (aLine[pos] != doubleQuote));
  } else {
    while ((pos < maxLen) && (aLine[pos] != delim)) {
      pos++;
      fLen++;
    }
  }

  if (!fLen) {
    return result;
  }

  field.Append(nsDependentSubstring(aLine, startPos, fLen));
  field.Trim(kWhitespace);

  if (quoted) {
    int32_t offset = field.Find("\"\"");
    while (offset != -1) {
      field.Cut(offset, 1);
      offset = MsgFind(field, "\"\"", false, offset + 1);
    }
  }

  return result;
}