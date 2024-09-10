int
iswcntrl(wint_t c)
{
  return iscntrl((int)c);
}