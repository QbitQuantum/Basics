gcc_pure gcc_nonnull_all
static inline wchar_t *
StringFind(wchar_t *haystack, wchar_t needle, size_t size)
{
  return wmemchr(haystack, needle, size);
}