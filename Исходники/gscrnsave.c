static void doConfig (HWND hwnd)
{
  // RegisterDialogClasses() lets the screensaver register any child control
  // windows needed by the configuration dialog box. If successful, that
  // function returns TRUE.

  if (RegisterDialogClasses (g_hinstance))
  {
    // Display the configuration dialog box, allowing the user to configure
    // the screensaver.

    DialogBoxParam (g_hinstance, MAKEINTRESOURCE(DLG_SCRNSAVECONFIGURE),
            hwnd, (DLGPROC) ScreenSaverConfigureDialog, 0);
  }
}