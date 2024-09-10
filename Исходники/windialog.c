void
win_open_config(void)
{
  if (config_wnd)
    return;

  set_dpi_auto_scaling(true);

  static bool initialised = false;
  if (!initialised) {
    InitCommonControls();
    RegisterClass(&(WNDCLASS){
      .style = CS_DBLCLKS,
      .lpfnWndProc = DefDlgProc,
      .cbClsExtra = 0,
      .cbWndExtra = DLGWINDOWEXTRA + 2 * sizeof (LONG_PTR),
      .hInstance = inst,
      .hIcon = null,
      .hCursor = LoadCursor(null, IDC_ARROW),
      .hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1),
      .lpszMenuName = null,
      .lpszClassName = "ConfigBox"
    });