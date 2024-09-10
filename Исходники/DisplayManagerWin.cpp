bool DisplayManagerWin::getDisplayInfo(int display, DISPLAY_DEVICEW& info)
{
  ZeroMemory(&info, sizeof(info));
  info.cb = sizeof(info);
  return EnumDisplayDevicesW(NULL, display, &info, 0);
}