static void CantDoIt( void )
{
    if( PendingProgramInterrupt ) {
        if( MessageBox( 0, TRP_WIN_wanna_kill, TRP_The_WATCOM_Debugger, MB_SYSTEMMODAL + MB_YESNO + MB_ICONQUESTION ) == IDYES ) {
            Terminate();
        }
    } else if( MessageBox( 0, TRP_WIN_wanna_interrupt, TRP_The_WATCOM_Debugger, MB_SYSTEMMODAL + MB_YESNO + MB_ICONQUESTION ) == IDYES ) {
        InterruptProgram();
    }
}