int curl_win32_ascii_to_idn(const char *in, size_t in_len, char **out_utf8)
{
  (void)in_len; /* unused */
  if(in) {
    WCHAR unicode[IDN_MAX_LENGTH];

    if(IdnToUnicode(0, (wchar_t *)in, -1, unicode, IDN_MAX_LENGTH) == 0) {
      wprintf(L"ERROR %d converting to Punycode\n", GetLastError());
      return 0;
    }
    else {
      *out_utf8 = Curl_convert_wchar_to_UTF8(unicode);
      if(!*out_utf8)
        return 0;
    }
  }
  return 1;
}