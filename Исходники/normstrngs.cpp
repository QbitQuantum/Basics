bool IsInterchangeValid7BitAscii(const char32 ch) {
  return IsValidCodepoint(ch) &&
      ch <= 128 &&
      (!u_isISOControl(static_cast<UChar32>(ch)) ||
       ch == '\n' || ch == '\f' || ch == '\t' || ch == '\r');
}