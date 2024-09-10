static int
menubar_set_menu(menubar_t* mb, HMENU menu, BOOL is_refresh)
{
    BYTE* buffer = NULL;
    TBBUTTON* buttons;
    TCHAR* labels;
    int i, n;

    MENUBAR_TRACE("menubar_set_menu(%p, %p)", mb, menu);

    if(menu == mb->menu  &&  !is_refresh)
        return 0;

    /* If dropped down, cancel it */
    if(mb->pressed_item >= 0) {
        menubar_ht_disable(mb);
        MENUBAR_SENDMSG(mb->win, WM_CANCELMODE, 0, 0);
    }

    /* Uninstall the old menu */
    if(mb->menu != NULL) {
        n = MENUBAR_SENDMSG(mb->win, TB_BUTTONCOUNT, 0, 0);
        for(i = 0; i < n; i++)
            MENUBAR_SENDMSG(mb->win, TB_DELETEBUTTON, 0, 0);
        mb->menu = NULL;
    }

    /* Install the new menu */
    n = (menu != NULL ? GetMenuItemCount(menu) : 0);
    if(MC_ERR(n < 0)) {
        MC_TRACE("menubar_set_menu: GetMenuItemCount() failed.");
        return -1;
    }

    if(n == 0) {
        mb->menu = menu;
        return 0;
    }

    buffer = (BYTE*) _malloca(n * sizeof(TBBUTTON) +
                              n * sizeof(TCHAR) * MENUBAR_ITEM_LABEL_MAXSIZE);
    if(MC_ERR(buffer == NULL)) {
        MC_TRACE("menubar_set_menu: _malloca() failed.");
        mc_send_notify(mb->notify_win, mb->win, NM_OUTOFMEMORY);
        return -1;
    }
    buttons = (TBBUTTON*) buffer;
    labels = (TCHAR*) (buffer + n * sizeof(TBBUTTON));

    memset(buttons, 0, n * sizeof(TBBUTTON));

    for(i = 0; i < n; i++) {
        UINT state;
        state = GetMenuState(menu, i, MF_BYPOSITION);

        buttons[i].iBitmap = I_IMAGENONE;
        buttons[i].fsState = 0;
        if(!(state & (MF_DISABLED | MF_GRAYED)))
            buttons[i].fsState |= TBSTATE_ENABLED;
        if((state & (MF_MENUBREAK | MF_MENUBARBREAK)) && i > 0)
            buttons[i-1].fsState |= TBSTATE_WRAP;

        if(state & MF_POPUP) {
            TCHAR* label = labels + i * MENUBAR_ITEM_LABEL_MAXSIZE;
            GetMenuString(menu, i, label, MENUBAR_ITEM_LABEL_MAXSIZE, MF_BYPOSITION);

            buttons[i].fsStyle = BTNS_AUTOSIZE | BTNS_DROPDOWN | BTNS_SHOWTEXT;
            buttons[i].dwData = i;
            buttons[i].iString = (INT_PTR) label;
            buttons[i].idCommand = i;
        } else {
            buttons[i].dwData = 0xffff;
            buttons[i].idCommand = 0xffff;
            if(state & MF_SEPARATOR) {
                buttons[i].fsStyle = BTNS_SEP;
                buttons[i].iBitmap = MENUBAR_SEPARATOR_WIDTH;
            }
        }
    }

    MENUBAR_SENDMSG(mb->win, TB_ADDBUTTONS, n, buttons);
    mb->menu = menu;
    _freea(buffer);
    return 0;
}