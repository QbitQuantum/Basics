//----------------------------------------------------------------------------
//
STDMETHODIMP CAnchoAddonService::updateWindow(INT aWindowId, LPDISPATCH aProperties)
{
  if (!aProperties) {
    return E_INVALIDARG;
  }
  HWND hwnd = winIdToHWND(aWindowId);
  if (!isIEWindow(hwnd)) {
    return E_INVALIDARG;
  }
  CIDispatchHelper properties = aProperties;

  WINDOWINFO winInfo;
  winInfo.cbSize = sizeof(WINDOWINFO);
  BOOL res = GetWindowInfo(hwnd, &winInfo);
  int top = winInfo.rcWindow.top;
  int left = winInfo.rcWindow.left;
  int width = winInfo.rcWindow.right - winInfo.rcWindow.left;
  int height = winInfo.rcWindow.bottom - winInfo.rcWindow.top;
  bool shouldMove = SUCCEEDED((properties.Get<int, VT_I4>(L"top", top)));
  shouldMove = SUCCEEDED((properties.Get<int, VT_I4>(L"left", left))) || shouldMove;
  shouldMove = SUCCEEDED((properties.Get<int, VT_I4>(L"width", width))) || shouldMove;
  shouldMove = SUCCEEDED((properties.Get<int, VT_I4>(L"height", height))) || shouldMove;
  if (shouldMove) {
    ::MoveWindow(hwnd, left, top, width, height, TRUE);
  }
  bool focused = false;
  if (SUCCEEDED((properties.Get<bool, VT_BOOL, VARIANT_BOOL>(L"focused", focused)))) {
    if(focused) {
      ::SetForegroundWindow(hwnd);
    } else {
      //Bring to foreground next IE window
      HWND nextWin = hwnd;
      while (nextWin = GetNextWindow(nextWin, GW_HWNDNEXT)) {
        if (isIEWindow(hwnd)) {
          ::SetForegroundWindow(nextWin);
          break;
        }
      }
    }
  }
  std::wstring state;
  if ( SUCCEEDED((properties.Get<std::wstring, VT_BSTR, BSTR>(L"state", state)))) {
    if (state == L"maximized") {
      ::ShowWindow(hwnd, SW_MAXIMIZE);
    } else if (state == L"minimized") {
      ::ShowWindow(hwnd, SW_MINIMIZE);
    } else if (state == L"normal") {
      ::ShowWindow(hwnd, SW_NORMAL);
    } else if (state == L"fullscreen") {
      //TODO - fullscreen
    }
  }
  //TODO - drawAttention
  return S_OK;
}