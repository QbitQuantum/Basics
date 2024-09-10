static void setupSystemMenu( HWND hwnd ) {
    HMENU       smh;
    HMENU       mh;
    char        menuname[256];

    smh = GetSystemMenu( hwnd, FALSE );
    mh = GetMenu( hwnd );
    AppendMenu( smh, MF_SEPARATOR, 0,NULL );
    GetMenuString( mh, MENU_LOG_CURRENT_STATE, menuname, sizeof( menuname ),
                   MF_BYCOMMAND );
    AppendMenu( smh, MF_ENABLED, MENU_LOG_CURRENT_STATE, menuname );
    GetMenuString( mh, MENU_LOG_OPTIONS, menuname, sizeof( menuname ),
                   MF_BYCOMMAND );
    AppendMenu( smh, MF_ENABLED, MENU_LOG_OPTIONS, menuname );
    GetMenuString( mh, MENU_TASK_CTL, menuname, sizeof( menuname ),
                   MF_BYCOMMAND );
    AppendMenu( smh, MF_ENABLED, MENU_TASK_CTL, menuname );
}