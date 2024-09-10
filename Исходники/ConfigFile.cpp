std::string getUserHomeDirectory() {
  char buff[MAX_PATH];
  HRESULT res = SHGetFolderPathA(NULL, CSIDL_FLAG_CREATE | CSIDL_APPDATA, NULL,
                                 SHGFP_TYPE_CURRENT, buff);
  if (res != S_OK)
    assert(0 && "Failed to get user home directory");
  return buff;
}