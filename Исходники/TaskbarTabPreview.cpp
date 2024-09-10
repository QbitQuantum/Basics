nsresult
TaskbarTabPreview::Enable() {
  WNDCLASSW wc;
  HINSTANCE module = GetModuleHandle(nullptr);

  if (!GetClassInfoW(module, kWindowClass, &wc)) {
    wc.style         = 0;
    wc.lpfnWndProc   = GlobalWndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = module;
    wc.hIcon         = nullptr;
    wc.hCursor       = nullptr;
    wc.hbrBackground = (HBRUSH) nullptr;
    wc.lpszMenuName  = (LPCWSTR) nullptr;
    wc.lpszClassName = kWindowClass;
    RegisterClassW(&wc);
  }
  ::CreateWindowW(kWindowClass, L"TaskbarPreviewWindow",
                  WS_CAPTION | WS_SYSMENU, 0, 0, 200, 60,
                  nullptr, nullptr, module, this);
  // GlobalWndProc will set mProxyWindow so that WM_CREATE can have a valid HWND
  if (!mProxyWindow)
    return NS_ERROR_INVALID_ARG;

  UpdateProxyWindowStyle();

  nsresult rv = TaskbarPreview::Enable();
  nsresult rvUpdate;
  rvUpdate = UpdateTitle();
  if (NS_FAILED(rvUpdate))
    rv = rvUpdate;

  rvUpdate = UpdateIcon();
  if (NS_FAILED(rvUpdate))
    rv = rvUpdate;

  return rv;
}