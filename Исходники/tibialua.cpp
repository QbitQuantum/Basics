// create tray menu
void doTrayMenuCreate(HWND hwnd)
{
    // create tray menu
    trayMenu = CreatePopupMenu();
    AppendMenu(trayMenu, MF_STRING, ID_TRAY_MENU_NULL,     "Tibia Lua");
    AppendMenu(trayMenu, MF_SEPARATOR, 0, 0);

    // append scripts to tray menu
    doTrayMenuAppendScripts(trayMenu);

    AppendMenu(trayMenu, MF_SEPARATOR, 0, 0);
    AppendMenu(trayMenu, MF_STRING, ID_TRAY_MENU_HOTKEYS,  "Hotkeys");
    AppendMenu(trayMenu, MF_SEPARATOR, 0, 0);
    AppendMenu(trayMenu, MF_STRING, ID_TRAY_MENU_ABOUT,    "About...");
    AppendMenu(trayMenu, MF_STRING, ID_TRAY_MENU_HOMEPAGE, "Homepage...");
    AppendMenu(trayMenu, MF_STRING, ID_TRAY_MENU_EXIT,     "Exit");

    // set default tray menu item
    SetMenuDefaultItem(trayMenu, ID_TRAY_MENU_NULL, MF_BYCOMMAND);

    // check tray menu items
    CheckMenuItem(trayMenu, ID_TRAY_MENU_HOTKEYS, MF_CHECKED);
}