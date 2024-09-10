boost::filesystem::wpath Platform::resolveShortcut(const boost::filesystem::wpath& path_to_shortcut) {
  try {
    CComPtr<IShellLink> psl;
    HRESULT hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void**) &psl);
    if (FAILED(hr)) {
      throw_GetLastError("resolveShortcut (CoCreateInstance(CLSID_ShellLink))");
    }
    CComQIPtr<IPersistFile> ppf(psl);
    if (!ppf) throw std::runtime_error("IPersistFile");
    if (FAILED(ppf->Load(path_to_shortcut.file_string().c_str(), STGM_READ))) throw_GetLastError("resolveShortcut (IPersistFile::Load)");
    WCHAR resPath[MAX_PATH];
    if (FAILED(psl->GetPath(resPath, MAX_PATH, NULL, 0 /*todo: might need a flag here*/ ))) throw_GetLastError("resolveShortcut (IShellLink::GetPath)");
    return boost::filesystem::wpath(resPath);

  } catch (const std::exception& e) {
    throw boost::filesystem::wfilesystem_error(e.what(), path_to_shortcut, boost::system::errc::make_error_code(boost::system::errc::bad_address));
  }
}