bool substr_match(const wstring& str, wstring::size_type pos, wstring::const_pointer mstr) {
  size_t mstr_len = wcslen(mstr);
  if ((pos > str.length()) || (pos + mstr_len > str.length())) {
    return false;
  }
  return wmemcmp(str.data() + pos, mstr, mstr_len) == 0;
}