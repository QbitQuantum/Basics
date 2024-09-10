void WMINamespaceClass::Print(const wchar_t *outlog) {
  FILE* out = CreateLogFile(outlog, L"at, ccs=UNICODE");
  MyPrintFunc(out, L"===============================Namespaces=========================\n");
  std::vector<std::wstring>::iterator it = NamespaceNames.begin();
  std::wstring strID;
  for (; it != NamespaceNames.end(); ++it) {
    GetWStrId(strID, *it, m_bXP);
    MyPrintFunc(out, L"%s (NS_%s)\n", it->c_str(), strID.c_str());
  }
  MyPrintFunc(out, L"==================================================================\n");
  if (out)
    ::fclose(out);
}