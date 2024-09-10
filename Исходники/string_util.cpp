String StringUtil::Trim(CStrRef input, TrimType type  /* = TrimBoth */,
                        CStrRef charlist /* = k_HPHP_TRIM_CHARLIST */) {
  if (input.empty()) return input;
  int len = input.size();
  char *ret = string_trim(input.data(), len,
                          charlist.data(), charlist.length(), type);
  return String(ret, len, AttachString);
}