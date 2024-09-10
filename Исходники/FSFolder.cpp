static bool IsAscii(const UString &testString)
{
  for (int i = 0; i < testString.Length(); i++)
    if (testString[i] >= 0x80)
      return false;
  return true;
}