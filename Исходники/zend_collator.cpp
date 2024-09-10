static String intl_convert_str_utf16_to_utf8(CStrRef utf16_str,
                                             UErrorCode * status) {
  char* str = nullptr;
  int str_len = 0;
  intl_convert_utf16_to_utf8(&str, &str_len,
                             (UChar*)(utf16_str.data()),
                             UCHARS(utf16_str.length()),
                             status);
  if (U_FAILURE(*status)) {
    return "";
  }
  return String(str, str_len, AttachString);
}