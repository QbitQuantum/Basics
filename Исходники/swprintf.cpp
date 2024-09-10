int vswprintf(wchar_t* wcs, size_t maxlen, const wchar_t* fmt, va_list ap) {
  mbstate_t mbstate;
  memset(&mbstate, 0, sizeof(mbstate));

  // At most, each wide character (UTF-32) can be expanded to four narrow
  // characters (UTF-8).
  const size_t max_mb_len = maxlen * 4;
  const size_t mb_fmt_len = wcslen(fmt) * 4 + 1;
  UniquePtr<char[]> mbfmt(new char[mb_fmt_len]);
  if (wcsrtombs(mbfmt.get(), &fmt, mb_fmt_len, &mbstate) == MBS_FAILURE) {
    return -1;
  }

  UniquePtr<char[]> mbs(new char[max_mb_len]);
  int nprinted = vsnprintf(mbs.get(), max_mb_len, mbfmt.get(), ap);
  if (nprinted == -1) {
    return -1;
  }

  const char* mbsp = mbs.get();
  if (mbsrtowcs(wcs, &mbsp, maxlen, &mbstate) == MBS_FAILURE) {
    return -1;
  }

  // Can't use return value from vsnprintf because that number is in narrow
  // characters, not wide characters.
  int result = wcslen(wcs);

  // swprintf differs from snprintf in that it returns -1 if the output was
  // truncated.
  //
  // Truncation can occur in two places:
  // 1) vsnprintf truncated, in which case the return value is greater than the
  //    length we passed.
  // 2) Since the char buffer we pass to vsnprintf might be oversized, that
  //    might not truncate while mbsrtowcs will. In this case, mbsp will point
  //    to the next unconverted character instead of nullptr.
  if (nprinted >= max_mb_len || mbsp != nullptr) {
    return -1;
  }

  return result;
}