/*
 * getItemMsg - find the hint message for the specified menu item
 */
static msg_id getItemMsg( statwnd *wnd, ctl_id menuid )
{
    int                 i;
    HWND                hint;
    HLOCAL              hinfo;
    HintWndInfo         *info;
    const MenuItemHint  *hinttable;
    msg_id              msgid;

    hint = GetHintHwnd( wnd );
    hinfo = GetProp( hint, HINT_PROP_ID );
    info = LocalLock( hinfo );
    hinttable = info->hints;
    msgid = HINT_EMPTY;
    if( hinttable != NULL ) {
        for( i = 0; i < info->hint_num_items; i++ ) {
            if( hinttable[i].menuid == menuid ) {
                msgid = hinttable[i].msgid;
                break;
            }
        }
    }
    LocalUnlock( hinfo );
    return( msgid );

} /* getItemMsg */