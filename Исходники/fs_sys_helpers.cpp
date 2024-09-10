std::string
get_application_data_folder() {
  wchar_t szPath[MAX_PATH];

  if (SUCCEEDED(SHGetFolderPathW(nullptr, CSIDL_APPDATA | CSIDL_FLAG_CREATE, nullptr, 0, szPath)))
    return to_utf8(std::wstring(szPath)) + "\\mkvtoolnix";

  return "";
}