void TextFunctions::_Register() {
  RegisterDynamicTextFunction(L"Time", 0, Time, true);
  RegisterDynamicTextFunction(L"Time", 1, Time, true);

  RegisterDynamicTextFunction(L"WindowTitle", 1, [] (LPCWSTR /* name */, UCHAR /* numArgs */, LPWSTR* args, LPWSTR dest, size_t cchDest) -> size_t {
    HWND window = FindWindowW(args[0], nullptr);
    if (window) {
      return GetWindowTextW(window, dest, (int)cchDest);
    }
    return 0;
  }, true);
}