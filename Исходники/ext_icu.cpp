String f_icu_transliterate(CStrRef str, bool remove_accents) {
#if HAVE_OLD_LIBICU
  // inspired by the UnicodeString::setToUTF8 implementation
  int32_t length = str.length();
  int32_t bytesWritten=0;
  UnicodeString u_str;
  u_strFromUTF8WithSub(u_str.getBuffer(length+1), length+1, &bytesWritten,
      str.data(), length, 0xfffd, NULL, NULL);
  u_str.releaseBuffer(bytesWritten);
#else
  UnicodeString u_str = UnicodeString::fromUTF8(str.data());
#endif
  if (remove_accents) {
    s_transliterator->transliterate(u_str);
  } else {
    s_transliterator->transliterate_with_accents(u_str);
  }

  // Convert the UnicodeString back into a UTF8 String.
#if HAVE_OLD_LIBICU
  return icuStringToUTF8(u_str);
#else
  int32_t capacity = u_str.countChar32() * sizeof(UChar) + 1;
  char* out = (char *)malloc(capacity);
  CheckedArrayByteSink bs(out, capacity);
  u_str.toUTF8(bs);

  return String(out, AttachString);
#endif
}