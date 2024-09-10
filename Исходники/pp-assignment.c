//
// Compare (*left) and (*right), ignoring case
//
int cmp(const void* left, const void* right) {
  const unsigned char
    *s1 = *(const unsigned char **) left,
    *s2 = *(const unsigned char **) right;

  for (; _tolower(*s1) == _tolower(*s2); ++s1, ++s2) {
    if (*s1 == '\0') { return 0; }
  }

  return _tolower(*s1) - _tolower(*s2);
}