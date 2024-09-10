BOOL CALLBACK
UpdMenu(HWND  hwnd,LPARAM lParam)
{
    int i;
    BOOL flag=lParam;
    //    int Checked;
    HMENU hSysMenu=GetSystemMenu(hwnd, FALSE);
    for(i=0;i<GetMenuItemCount(hSysMenu) && hSysMenu;i++)
        if(GetMenuItemID(hSysMenu,i)==IDM_TRAY) hSysMenu = 0;
    if (hSysMenu && lParam)
    {
        InsertMenu (hSysMenu, GetMenuItemID(hSysMenu,0),MF_SEPARATOR,IDM_SEPARATOR, NULL) ;
        if(GetWindowLong(hwnd,GWL_EXSTYLE)&WS_EX_TOPMOST)
            InsertMenu (hSysMenu, GetMenuItemID(hSysMenu,0),MF_STRING|MF_CHECKED,IDM_ONTOP,"Always on top");
        else
            InsertMenu (hSysMenu, GetMenuItemID(hSysMenu,0),MF_STRING,IDM_ONTOP,"Always on top");
        InsertMenu (hSysMenu, GetMenuItemID(hSysMenu,0),MF_STRING,IDM_TRAY,"Minimize in tray");
        InsertMenu (hSysMenu, GetMenuItemID(hSysMenu,0),MF_STRING,IDM_SIZE,"My size");
    }
    if (hSysMenu && lParam==FALSE)
    {
        DeleteMenu (hSysMenu,IDM_TRAY,MF_BYCOMMAND);
        DeleteMenu (hSysMenu,IDM_ONTOP,MF_BYCOMMAND);
        DeleteMenu (hSysMenu,IDM_SEPARATOR,MF_BYCOMMAND);
        DeleteMenu (hSysMenu,IDM_SIZE,MF_BYCOMMAND);

    }
    return TRUE;
}