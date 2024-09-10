static char PostListen( void )
{
    NetCtlBlk.ncb_command = NCBLISTEN | ASYNCH;
    return( NetBIOS( &NetCtlBlk ) == 0 );
}