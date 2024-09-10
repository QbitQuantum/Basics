std::string kiwix::removeAccents(const std::string &text) {
  ucnv_setDefaultName("UTF-8");
  UErrorCode status = U_ZERO_ERROR;
  Transliterator *removeAccentsTrans = Transliterator::createInstance("Lower; NFD; [:M:] remove; NFC", UTRANS_FORWARD, status);
  UnicodeString ustring = UnicodeString(text.c_str());
  removeAccentsTrans->transliterate(ustring);
  delete removeAccentsTrans;
  std::string unaccentedText;
  ustring.toUTF8String(unaccentedText);
  return unaccentedText;
}