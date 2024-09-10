static void tokenize(const UnicodeString & str, rde::vector<UnicodeString> & tokens,
  const UnicodeString & delimiters = L" ", const bool trimEmpty = false)
{
  intptr_t lastPos = 0;
  while (true)
  {
    intptr_t pos = str.FindFirstOf(delimiters.c_str(), lastPos);
    if (pos == NPOS)
    {
       pos = str.Length();

       if (pos != lastPos || !trimEmpty)
       {
         tokens.push_back(
           UnicodeString(str.data() + lastPos, pos - lastPos));
       }
       break;
    }
    else
    {
      if (pos != lastPos || !trimEmpty)
      {
        tokens.push_back(
          UnicodeString(str.data() + lastPos, pos - lastPos));
      }
    }

    lastPos = pos + 1;
  }
}