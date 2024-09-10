UString::UString(const DOMString &d)
{
  if (d.isNull()) {
    attach(&Rep::null);
    return;
  }

  unsigned int len = d.length();
  UChar *dat = new UChar[len];
  memcpy(dat, d.unicode(), len * sizeof(UChar));
  rep = UString::Rep::create(dat, len);
}