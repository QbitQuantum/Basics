NS_IMETHODIMP
nsScreenManagerWin :: ScreenForNativeWidget(void *aWidget, nsIScreen **outScreen)
{
  HMONITOR mon = MonitorFromWindow ((HWND) aWidget, MONITOR_DEFAULTTOPRIMARY);
  *outScreen = CreateNewScreenObject (mon);
  return NS_OK;
}