void TEnumWindows::EnumWindows (TEnumMethod em)
{
  LPARAM  lParam = reinterpret_cast<LPARAM> (this);

  mDoingChildWindows = (em == emTopLevelWindows);

  EnumThreadWindows (GetCurrentThreadId(), WndEnumProc, lParam);
}