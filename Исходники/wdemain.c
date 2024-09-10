bool WdeWasAcceleratorHandled( MSG *msg )
{
    if( !TranslateMDISysAccel( hWinWdeMDIClient, msg ) &&
        !TranslateAccelerator( hWinWdeMain, WdeAccel, msg ) ) {
        return( FALSE );
    }
    return( TRUE );
}