bool ParseSubCharsCommand(int numForms, const CCommandSubCharsSet *forms, 
    const UString &commandString, CIntVector &indices)
{
  indices.Clear();
  int numUsedChars = 0;
  for(int i = 0; i < numForms; i++)
  {
    const CCommandSubCharsSet &set = forms[i];
    int currentIndex = -1;
    int len = MyStringLen(set.Chars);
    for(int j = 0; j < len; j++)
    {
      wchar_t c = set.Chars[j];
      int newIndex = commandString.Find(c);
      if (newIndex >= 0)
      {
        if (currentIndex >= 0)
          return false;
        if (commandString.Find(c, newIndex + 1) >= 0)
          return false;
        currentIndex = j;
        numUsedChars++;
      }
    }
    if(currentIndex == -1 && !set.EmptyAllowed)
      return false;
    indices.Add(currentIndex);
  }
  return (numUsedChars == commandString.Length());
}