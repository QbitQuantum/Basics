void WSetKey( WAccelEditInfo *einfo, BYTE scan_code )
{
    bool        cntl;
    bool        shift;
    bool        alt;
    char        *str;
    char        scan_key;
    uint_16     key;
    uint_16     skey;
    bool        is_virt;
    BYTE        kbstate[256];
    int         ta_ret;
#ifdef __NT__
    WORD        ta_key;
#else
    DWORD       ta_key;
#endif

    if( einfo == NULL ) {
        return;
    }

    is_virt = TRUE;
    key = einfo->key_info.key;
    skey = WMapShiftedKeyToKey( key );
    GetKeyboardState( kbstate );
    cntl = (kbstate[VK_CONTROL] & 0x0080) != 0;
    shift = (kbstate[VK_SHIFT] & 0x0080) != 0;
    alt = (kbstate[VK_MENU] & 0x0080) != 0;

    str = WGetVKeyFromID( key );

    if( str == NULL ) {
        // I am assumming that they key must be alphanumeric
        // as WGetVKeyFromID( key ) would filter out all others
        if( isalpha( key ) ) {
            if( alt ) {
                str = WGetASCIIVKText( key );
            } else {
                if( cntl ) {
                    key = toupper( key ) - '@';
                } else {
                    if( !shift ) {
                        key = tolower( key );
                    }
                }
                str = WGetASCIIKeyText( key );
                is_virt = FALSE;
            }
        } else if( isdigit( key ) ) {
            if( alt || cntl ) {
                str = WGetASCIIVKText( key );
            } else {
                if( shift ) {
                    key = WMapKeyToShiftedKey( key );
                }
                str = WGetASCIIKeyText( key );
                is_virt = FALSE;
            }
        } else if( isdigit( skey ) ) {
            str = WGetASCIIVKText( skey );
        // The remaining keys are the ones where we did not get a
        // virtual key we could translate, an alpha-numeric key,
        // a shifted 0-9 ( ie !@#$%^&*() ).
        // The ToAscii function handles everything except the following
        // keys where cntl is pressed. These keys are `-=[]\;',./
        // So, I throw up my hands in defeat and add a special case
        } else if( cntl && (scan_key = WMapScanCodeToKey( scan_code )) != 0 ) {
            str = WGetASCIIKeyText( scan_key );
        } else {
            ta_ret = ToAscii( key, scan_code, kbstate, &ta_key, 0 );
            if( ta_ret ) {
                if( shift ) {
                    ta_key = WMapShiftedKeyToKey( ta_key );
                }
                str = WGetASCIIKeyText( ta_key );
            }
        }
    }

    WSetEditWithStr( GetDlgItem( einfo->edit_dlg, IDM_ACCEDKEY ), str );
    WSetVirtKey( einfo->edit_dlg, is_virt );
    if( is_virt ) {
        CheckDlgButton( einfo->edit_dlg, IDM_ACCEDALT, ( alt ) ? BST_CHECKED : BST_UNCHECKED );
        CheckDlgButton( einfo->edit_dlg, IDM_ACCEDCNTL, ( cntl ) ? BST_CHECKED : BST_UNCHECKED );
        CheckDlgButton( einfo->edit_dlg, IDM_ACCEDSHFT, ( shift ) ? BST_CHECKED : BST_UNCHECKED );
    }
}