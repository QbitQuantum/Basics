static void ReplaceDisk(UString &s)
{
  int i;
  for (i = 0; i < s.Length(); i++)
    if (s[i] != ' ')
      break;
  if (s.Length() > i + 1)
  {
    if (s[i + 1] == L':')
    {
      s.Delete(i + 1);
      // s.Insert(i + 1, L'_');
    }
  }
}