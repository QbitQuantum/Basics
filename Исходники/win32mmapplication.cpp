  void cMainWindow::AddMenu()
  {
    // Create our menu
    win32mm::cMenu menu;
    menu.Create();

    // Create our File menu
    win32mm::cPopupMenu popupFile;
    popupFile.AppendMenuItemWithShortcut(ID_MENU_FILE_OPEN_FOLDER, TEXT(LANGTAG_OPEN_FOLDER), KEY_COMBO_CONTROL('O'));
    popupFile.AppendMenuItem(ID_MENU_FILE_IMPORT_FOLDER, TEXT(LANGTAG_IMPORT_FOLDER));
    popupFile.AppendMenuItem(ID_MENU_FILE_SETTINGS, TEXT(LANGTAG_SETTINGS));
    popupFile.AppendMenuItemWithShortcut(ID_MENU_FILE_QUIT, TEXT(LANGTAG_QUIT), KEY_COMBO_CONTROL('Q'));

    // Create our View menu
    win32mm::cPopupMenu popupView;
    popupView.AppendMenuItem(ID_MENU_VIEW_SINGLE_PHOTO_MODE, TEXT(LANGTAG_SINGLE_PHOTO_MODE));

    // Create our Help menu
    win32mm::cPopupMenu popupHelp;
    popupHelp.AppendMenuItem(ID_MENU_HELP_ABOUT, TEXT(LANGTAG_ABOUT));

    menu.AppendPopupMenu(popupFile, TEXT(LANGTAG_FILE));
    menu.AppendPopupMenu(popupView, TEXT(LANGTAG_VIEW));
    menu.AppendPopupMenu(popupHelp, TEXT(LANGTAG_HELP));

    SetMenu(menu);
  }