std::wstring ELStripLeadingSpaces(std::wstring input)
{
  size_t i = 0;

  //< Search input for the first non-space character
  while (i < input.length())
  {
    if (input.at(i) != ' ')
    {
      break;
    }

    i++;
  }

  return input.substr(i, std::wstring::npos);
}