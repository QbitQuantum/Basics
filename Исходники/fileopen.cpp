extern "C" int
WinMainCRTStartup()
{
  ExitProcess(WinMain(NULL, NULL, NULL, SW_SHOWDEFAULT));
}