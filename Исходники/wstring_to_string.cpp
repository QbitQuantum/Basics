std::string     wstring_to_string(const std::wstring & s)
{
  const wchar_t *wcs = s.c_str();
  std::size_t    len = wcsrtombs(NULL, &wcs, 0, NULL);

  if (len != (size_t) -1)
    {
      char      *dest = new char[len + 1];

      if (dest)
        {
          mbstate_t     state;

          memset(&state, 0, sizeof state);
          wcs = s.c_str();
          len = wcsrtombs(dest, &wcs, len, &state);
          if (len != (size_t) -1)
            {
              dest[len] = '\0';
              std::string result(dest);
              delete [] dest;
              return result;
            }
          delete [] dest;
        }
    }
  // conversion error try something stupid
  return std::string(s.begin(), s.end());
}