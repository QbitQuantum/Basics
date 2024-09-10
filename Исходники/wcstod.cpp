float_type wcstod(const wchar_t* str, wchar_t** end, float_type strtod_fn(const char*, char**)) {
  const wchar_t* original_str = str;
  while (iswspace(*str)) {
    str++;
  }

  // What's the longest span of the input that might be part of the float?
  size_t max_len = wcsspn(str, L"-+0123456789.xXeEpP()nNaAiIfFtTyY");

  // We know the only valid characters are ASCII, so convert them by brute force.
  char* ascii_str = new char[max_len + 1];
  if (!ascii_str) return float_type();
  for (size_t i = 0; i < max_len; ++i) {
    ascii_str[i] = str[i] & 0xff;
  }
  ascii_str[max_len] = 0;

  // Set up a fake FILE that points to those ASCII characters, for `parsefloat`.
  FILE f;
  __sfileext fext;
  _FILEEXT_SETUP(&f, &fext);
  f._flags = __SRD;
  f._bf._base = f._p = reinterpret_cast<unsigned char*>(ascii_str);
  f._bf._size = f._r = max_len;
  f._read = [](void*, char*, int) { return 0; }; // aka `eofread`, aka "no more data".
  f._lb._base = NULL;

  // Ask `parsefloat` to look at the same data more carefully.

  // We can't just do this straight away because we can't construct a suitable FILE*
  // in the absence of any `fwmemopen` analogous to `fmemopen`. And we don't want to
  // duplicate the `parsefloat` logic. We also don't want to actually have to have wchar_t
  // implementations of the ASCII `strtod` logic (though if you were designing a libc
  // from scratch, you'd probably want to just make that more generic and lose all the
  // cruft on top).
  size_t actual_len = parsefloat(&f, ascii_str, ascii_str + max_len);

  // Finally let the ASCII conversion function do the work.
  char* ascii_end;
  float_type result = strtod_fn(ascii_str, &ascii_end);
  if (ascii_end != ascii_str + actual_len) abort();

  if (end) {
    if (actual_len == 0) {
      // There was an error. We need to set the end pointer back to the original string, not the
      // one we advanced past the leading whitespace.
      *end = const_cast<wchar_t*>(original_str);
    } else {
      *end = const_cast<wchar_t*>(str) + actual_len;
    }
  }

  delete[] ascii_str;
  return result;
}