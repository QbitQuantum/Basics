/*
 * _ReleaseWindowResources - get rid of any resources
 */
void _ReleaseWindowResources( LPWDATA w )
{
    DeleteObject( w->brush );
    if( w->hascursor ) {
        DestroyCaret();
    }
    DeleteMenu( _SubMenuWindows, MSG_WINDOWS+w->handles[0], MF_BYCOMMAND );

} /* _ReleaseWindowResources */