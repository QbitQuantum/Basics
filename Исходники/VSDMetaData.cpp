librevenge::RVNGString libvisio::VSDMetaData::readCodePageString(librevenge::RVNGInputStream *input)
{
  uint32_t size = readU32(input);
  if (size > getRemainingLength(input))
    size = getRemainingLength(input);

  if (size == 0)
    return librevenge::RVNGString();

  std::vector<unsigned char> characters;
  for (uint32_t i = 0; i < size; ++i)
    characters.push_back(readU8(input));

  uint32_t codepage = getCodePage();
  librevenge::RVNGString string;

  if (codepage == 65001)
  {
    // http://msdn.microsoft.com/en-us/library/windows/desktop/dd374130%28v=vs.85%29.aspx
    // says this is UTF-8.
    characters.push_back(0);
    string.append(reinterpret_cast<const char *>(characters.data()));
  }
  else
  {
    UErrorCode status = U_ZERO_ERROR;
    UConverter *conv = nullptr;

    switch (codepage)
    {
    case 1252:
      // http://msdn.microsoft.com/en-us/goglobal/bb964654
      conv = ucnv_open("windows-1252", &status);
      break;
    }

    if (U_SUCCESS(status) && conv)
    {
      assert(!characters.empty());
      const auto *src = (const char *)&characters[0];
      const char *srcLimit = (const char *)src + characters.size();
      while (src < srcLimit)
      {
        UChar32 ucs4Character = ucnv_getNextUChar(conv, &src, srcLimit, &status);
        if (U_SUCCESS(status) && U_IS_UNICODE_CHAR(ucs4Character))
          appendUCS4(string, ucs4Character);
      }
    }

    if (conv)
      ucnv_close(conv);
  }

  return string;
}