  std::codecvt_base::result windows_file_codecvt::do_in(
    std::mbstate_t &, 
    const char* from, const char* from_end, const char*& from_next,
    wchar_t* to, wchar_t* to_end, wchar_t*& to_next) const
  {
    UINT codepage = AreFileApisANSI() ? CP_ACP : CP_OEMCP;

    int count;
    if ((count = ::MultiByteToWideChar(codepage, MB_PRECOMPOSED, from,
      from_end - from, to, to_end - to)) == 0) 
    {
      return error;  // conversion failed
    }

    from_next = from_end;
    to_next = to + count;
    *to_next = L'\0';
    return ok;
 }