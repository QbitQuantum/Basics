bool WGetEditWindowID( HWND dlg, char **symbol, uint_16 *id,
                       WRHashTable *symbol_table, bool combo_change )
{
    int_32      val;
    char        *ep;
    WRHashValue hv;
    WRHashEntry *new_entry;
    bool        dup;

    if( dlg == (HWND)NULL ) {
        return( FALSE );
    }

    if( combo_change ) {
        *symbol = WGetStrFromComboLBox( GetDlgItem( dlg, IDM_ACCEDCMDID ), -1 );
    } else {
        *symbol = WGetStrFromEdit( GetDlgItem( dlg, IDM_ACCEDCMDID ), NULL );
    }

    if( *symbol == NULL ) {
        return( FALSE );
    }

    if( **symbol == '\0' ) {
        *symbol = WGetStrFromEdit( GetDlgItem( dlg, IDM_ACCEDCMDNUM ), NULL );
    }

    if( *symbol == NULL ) {
        return( FALSE );
    }

    strupr( *symbol );

    // check if the string has a numeric representation
    val = (int_32)strtol( *symbol, &ep, 0 );
    if( *ep != '\0' ) {
        // the string did not have a numeric representation
        // so let's look it up in the hash table
        if( WRLookupName( symbol_table, *symbol, &hv ) ) {
            *id = (uint_16)hv;
        } else {
            dup = false;
            new_entry = WRAddDefHashEntry( symbol_table, *symbol, &dup );
            if( new_entry != NULL ) {
                *id = (uint_16)new_entry->value;
                if( !dup ) {
                    SendDlgItemMessage( dlg, IDM_ACCEDCMDID, CB_ADDSTRING,
                                        0, (LPARAM)(LPSTR)new_entry->name );
                    SendDlgItemMessage( dlg, IDM_ACCEDCMDID, CB_SETITEMDATA,
                                        0, (LPARAM)new_entry );
                }
            } else {
                *id = 0;
                WRMemFree( *symbol );
                *symbol = NULL;
                return( FALSE );
            }
        }
    } else {
        // the string did have a numeric representation
        *id = (uint_16)val;
        WRMemFree( *symbol );
        *symbol = NULL;
    }

    return( TRUE );
}