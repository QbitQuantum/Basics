void
win_update_menus(void)
{
  bool shorts = !term.shortcut_override;
  bool clip = shorts && cfg.clip_shortcuts;
  bool alt_fn = shorts && cfg.alt_fn_shortcuts;
  bool ct_sh = shorts && cfg.ctrl_shift_shortcuts;

  ModifyMenu(
    sysmenu, IDM_NEW, 0, IDM_NEW,
    alt_fn ? "Ne&w\tAlt+F2" : ct_sh ? "Ne&w\tCtrl+Shift+N" : "Ne&w"
  );
  ModifyMenu(
    sysmenu, SC_CLOSE, 0, SC_CLOSE,
    alt_fn ? "&Close\tAlt+F4" : ct_sh ? "&Close\tCtrl+Shift+W" : "&Close"
  );

  uint sel_enabled = term.selected ? MF_ENABLED : MF_GRAYED;
  EnableMenuItem(menu, IDM_OPEN, sel_enabled);
  ModifyMenu(
    menu, IDM_COPY, sel_enabled, IDM_COPY,
    clip ? "&Copy\tCtrl+Ins" : ct_sh ? "&Copy\tCtrl+Shift+C" : "&Copy"
  );

  uint paste_enabled =
    IsClipboardFormatAvailable(CF_TEXT) ||
    IsClipboardFormatAvailable(CF_UNICODETEXT) ||
    IsClipboardFormatAvailable(CF_HDROP)
    ? MF_ENABLED : MF_GRAYED;
  ModifyMenu(
    menu, IDM_PASTE, paste_enabled, IDM_PASTE,
    clip ? "&Paste\tShift+Ins" : ct_sh ? "&Paste\tCtrl+Shift+V" : "&Paste"
  );

  ModifyMenu(
    menu, IDM_SEARCH, 0, IDM_SEARCH,
    alt_fn ? "S&earch\tAlt+F3" : ct_sh ? "S&earch\tCtrl+Shift+H" : "S&earch"
  );

  ModifyMenu(
    menu, IDM_RESET, 0, IDM_RESET,
    alt_fn ? "&Reset\tAlt+F8" : ct_sh ? "&Reset\tCtrl+Shift+R" : "&Reset"
  );

  uint defsize_enabled =
    IsZoomed(wnd) || term.cols != cfg.cols || term.rows != cfg.rows
    ? MF_ENABLED : MF_GRAYED;
  ModifyMenu(
    menu, IDM_DEFSIZE_ZOOM, defsize_enabled, IDM_DEFSIZE_ZOOM,
    alt_fn ? "&Default size\tAlt+F10" :
    ct_sh ? "&Default size\tCtrl+Shift+D" : "&Default size"
  );

  uint fullscreen_checked = win_is_fullscreen ? MF_CHECKED : MF_UNCHECKED;
  ModifyMenu(
    menu, IDM_FULLSCREEN_ZOOM, fullscreen_checked, IDM_FULLSCREEN_ZOOM,
    alt_fn ? "&Full Screen\tAlt+F11" :
    ct_sh ? "&Full Screen\tCtrl+Shift+F" : "&Full Screen"
  );

  uint otherscreen_checked = term.show_other_screen ? MF_CHECKED : MF_UNCHECKED;
  ModifyMenu(
    menu, IDM_FLIPSCREEN, otherscreen_checked, IDM_FLIPSCREEN,
    alt_fn ? "Flip &Screen\tAlt+F12" :
    ct_sh ? "Flip &Screen\tCtrl+Shift+S" : "Flip &Screen"
  );

  uint options_enabled = config_wnd ? MF_GRAYED : MF_ENABLED;
  EnableMenuItem(menu, IDM_OPTIONS, options_enabled);
  EnableMenuItem(sysmenu, IDM_OPTIONS, options_enabled);
}