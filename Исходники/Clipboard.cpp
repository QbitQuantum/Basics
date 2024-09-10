bool ClipboardSetText(HWND owner, const UString &s)
{
  CClipboard clipboard;
  if (!clipboard.Open(owner))
    return false;
#ifdef _WIN32
  if (!::EmptyClipboard())
    return false;

  bool res;
  res = ClipboardSetData(CF_UNICODETEXT, (const wchar_t *)s, (s.Length() + 1) * sizeof(wchar_t));
  #ifndef _UNICODE
  AString a;
  a = UnicodeStringToMultiByte(s, CP_ACP);
  res |=  ClipboardSetData(CF_TEXT, (const char *)a, (a.Length() + 1) * sizeof(char));
  a = UnicodeStringToMultiByte(s, CP_OEMCP);
  res |=  ClipboardSetData(CF_OEMTEXT, (const char *)a, (a.Length() + 1) * sizeof(char));
  #endif
  return res;
#else
  wxTheClipboard->Clear();
  // This data objects are held by the clipboard,
  // so do not delete them in the app.
  wxString ws(s);
  wxTheClipboard->SetData( new wxTextDataObject(ws) );
  return true;
#endif
}