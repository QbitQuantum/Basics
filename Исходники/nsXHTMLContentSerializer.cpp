// See if the string has any lines longer than longLineLen:
// if so, we presume formatting is wonky (e.g. the node has been edited)
// and we'd better rewrap the whole text node.
bool
nsXHTMLContentSerializer::HasLongLines(const nsString& text, int32_t& aLastNewlineOffset)
{
  uint32_t start=0;
  uint32_t theLen = text.Length();
  bool rv = false;
  aLastNewlineOffset = kNotFound;
  for (start = 0; start < theLen; ) {
    int32_t eol = text.FindChar('\n', start);
    if (eol < 0) {
      eol = text.Length();
    }
    else {
      aLastNewlineOffset = eol;
    }
    if (int32_t(eol - start) > kLongLineLen)
      rv = true;
    start = eol + 1;
  }
  return rv;
}