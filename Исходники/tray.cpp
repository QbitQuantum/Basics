/**
 * Helper function that will allow us to receive some broadcast messages on Vista
 * (We need to bypass that filter if we run as Administrator, but the orginating process
 * has less priviledges)
 */
static void AdjustMessageFilters(UINT filter)
{
  HMODULE user32 = LoadLibraryW(L"user32.dll");
  if (user32 != 0) {
    pChangeWindowMessageFilter changeWindowMessageFilter =
      reinterpret_cast<pChangeWindowMessageFilter>(GetProcAddress(
        user32,
        "ChangeWindowMessageFilter"
      ));
    if (changeWindowMessageFilter != 0) {
      changeWindowMessageFilter(WM_TASKBARCREATED, filter);
    }
    FreeLibrary(user32);
  }
}