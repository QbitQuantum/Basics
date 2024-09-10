bool DbgGdb::Interrupt()
{
    if ( m_debuggeePid > 0 ) {
        m_observer->UpdateAddLine( wxString::Format( wxT( "Interrupting debugee process: %ld" ), m_debuggeePid ) );

#ifdef __WXMSW__
        if ( !GetIsRemoteDebugging() && DebugBreakProcessFunc ) {
            // we have DebugBreakProcess
            HANDLE process = OpenProcess( PROCESS_ALL_ACCESS, FALSE, ( DWORD )m_debuggeePid );
            BOOL res = DebugBreakProcessFunc( process );
            CloseHandle(process);
            return res == TRUE;
        }

        if ( GetIsRemoteDebugging() ) {
            // We need to send GDB a Ctrl-C event.  Using DebugBreakProcess just leaves
			// it unresponsive.
            return GenerateConsoleCtrlEvent( CTRL_C_EVENT, 0 );
        }
 
        // on Windows version < XP we need to find a solution for interrupting the
        // debuggee process
        return false;
#else
        kill( m_debuggeePid, SIGINT );
        return true;
#endif
    } else {
        ::wxMessageBox(_("Can't interrupt debuggee process: I don't know its PID!"), wxT("CodeLite"));
    }
    return false;
}