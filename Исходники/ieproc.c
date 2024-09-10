/*
 * IEIsMenuIDValid
 */
static BOOL IEIsMenuIDValid( HMENU menu, unsigned id )
{
    UINT st;

    if( !ImgEdEnableMenuInput ) {
        return( FALSE );
    }

    if( menu == (HMENU)NULL ) {
        return( TRUE );
    }

    // put any menu identifiers that you would like forced here
    switch( id ) {
    case IMGED_CLOSEALL:
        if( ImgedIsDDE ) {
            return( TRUE );
        }
        break;
    }

    st = GetMenuState( menu, id, MF_BYCOMMAND );

    if( st == -1 || (st & MF_GRAYED) == MF_GRAYED ) {
        return( FALSE );
    }

    return( TRUE );

} /* IEIsMenuIDValid */