static inline bool parseAlphaValue(const CharacterType*& string,
                                   const CharacterType* end,
                                   const char terminator,
                                   int& value) {
  while (string != end && isHTMLSpace<CharacterType>(*string))
    string++;

  bool negative = false;

  if (string != end && *string == '-') {
    negative = true;
    string++;
  }

  value = 0;

  int length = end - string;
  if (length < 2)
    return false;

  if (string[length - 1] != terminator || !isASCIIDigit(string[length - 2]))
    return false;

  if (string[0] != '0' && string[0] != '1' && string[0] != '.') {
    if (checkForValidDouble(string, end, terminator)) {
      value = negative ? 0 : 255;
      string = end;
      return true;
    }
    return false;
  }

  if (length == 2 && string[0] != '.') {
    value = !negative && string[0] == '1' ? 255 : 0;
    string = end;
    return true;
  }

  if (isTenthAlpha(string, length - 1)) {
    static const int tenthAlphaValues[] = {0,   25,  51,  76,  102,
                                           127, 153, 179, 204, 230};
    value = negative ? 0 : tenthAlphaValues[string[length - 2] - '0'];
    string = end;
    return true;
  }

  double alpha = 0;
  if (!parseDouble(string, end, terminator, alpha))
    return false;
  value = negative ? 0 : static_cast<int>(alpha * nextafter(256.0, 0.0));
  string = end;
  return true;
}