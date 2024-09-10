void InitScreen( void )
{
    FocusWnd = GetFocus();
    RestoreMainScreen( "WDWIN" );
    GUISetModalDlgs( FALSE );
}