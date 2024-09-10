int __iswpunct_ascii(wint_t c)
{
  return iswprint (c) && !iswalnum(c) && !iswspace(c);
}