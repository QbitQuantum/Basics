Validator::CharClass ValidateGrapheme::UnicodeToCharClass(char32 ch) const {
  if (IsVedicAccent(ch)) return CharClass::kVedicMark;
  // The ZeroWidth[Non]Joiner characters are mapped to kCombiner as they
  // always combine with the previous character.
  if (u_hasBinaryProperty(ch, UCHAR_GRAPHEME_LINK)) return CharClass::kVirama;
  if (u_isUWhiteSpace(ch)) return CharClass::kWhitespace;
  int char_type = u_charType(ch);
  if (char_type == U_NON_SPACING_MARK || char_type == U_ENCLOSING_MARK ||
      char_type == U_COMBINING_SPACING_MARK || ch == kZeroWidthNonJoiner ||
      ch == kZeroWidthJoiner)
    return CharClass::kCombiner;
  return CharClass::kOther;
}