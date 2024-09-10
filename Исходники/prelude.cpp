std::ostream & operator<<(std::ostream & o, wchar_t const c)
{
  char buf[MB_LEN_MAX];
  int const i = wctomb(buf, c);
  if(i < 0) o << '?';
  else std::copy(buf, buf + i, std::ostreambuf_iterator<char>(o));
  return o;
}