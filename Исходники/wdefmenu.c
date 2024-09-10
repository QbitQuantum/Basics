static void WdeEnableAllMenuItems( HMENU menu, Bool enable )
{
    int count;

    count = GetMenuItemCount( menu );
    for( count--; count >= 0; count-- ) {
        if( enable ) {
            EnableMenuItem( menu, count, MF_ENABLED | MF_BYPOSITION );
        } else {
            EnableMenuItem( menu, count, MF_GRAYED | MF_BYPOSITION );
        }
    }
}