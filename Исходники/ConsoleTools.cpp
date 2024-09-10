void ConsoleTools::setCatalogPath(const String &str) {
  delete catalogPath;
#if defined _WIN32
   // replace the environment variables to their values
  size_t i=ExpandEnvironmentStringsW(str.getWChars(),NULL,0);
  wchar_t *temp = new wchar_t[i];
  ExpandEnvironmentStringsW(str.getWChars(),temp,static_cast<DWORD>(i));
  catalogPath = new SString(temp);
  delete[] temp;
#else
  catalogPath = new SString(str);
#endif
}