static void add_user_menu_items(HMENU menu)
{
    MENUITEMINFO mii;
    memset(&mii, 0, sizeof(MENUITEMINFO));
    mii.type = MFT_SEPARATOR;
    InsertMenuItem(menu, GetMenuItemCount(menu), TRUE, &mii);
#if 1
    memset(&mii, 0, sizeof(MENUITEMINFO));
    mii.type = MFT_STRING;
    mii.hsubmenu = 0;
    mii.id = IDM_POP_NEW_TAB;
    mii.state = MFS_ENABLED;
    mii.cch = strlen("New Tab");
    mii.typedata = (DWORD)"New Tab";
    InsertMenuItem(menu, GetMenuItemCount(menu), TRUE, &mii);
#endif
    memset(&mii, 0, sizeof(MENUITEMINFO));
    mii.type = MFT_STRING;
    mii.hsubmenu = 0;
    mii.id =  IDM_POP_SAVE_AS;
    mii.state = MFS_ENABLED;
    mii.cch = strlen("Save As...");
    mii.typedata = (DWORD)"Save As...";
    InsertMenuItem(menu, GetMenuItemCount(menu), TRUE, &mii);
    
    memset(&mii, 0, sizeof(MENUITEMINFO));
    mii.type = MFT_STRING;
    mii.hsubmenu = 0;
    mii.id = IDM_POP_CLOSE_TAB;
    
    int count = SendMessage(propsheet_hwnd, PSM_GETPAGECOUNT, 0, 0);
    if (count >1) {
        mii.state &= ~MFS_DISABLED;
        mii.state |= MFS_ENABLED;
    } else {
        mii.state &= ~MFS_ENABLED;
        mii.state |= MFS_DISABLED;
    }
    mii.cch = strlen("Close Tab");
    mii.typedata = (DWORD)"Close Tab";
    InsertMenuItem(menu, GetMenuItemCount(menu), TRUE, &mii);
}