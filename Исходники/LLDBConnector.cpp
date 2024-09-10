void LLDBConnector::DeleteAllBreakpoints()
{
    if ( !IsRunning() ) {
        m_pendingDeletionBreakpoints.clear();
        m_breakpoints.clear();
        
        LLDBEvent event(wxEVT_LLDB_BREAKPOINTS_UPDATED);
        event.SetBreakpoints( GetAllBreakpoints() );
        ProcessEvent( event );
        return;
     }

    // mark all breakpoints for deletion
    CL_DEBUGS(wxString () << "codelite: DeleteAllBreakpoints called");
    m_pendingDeletionBreakpoints.swap( m_breakpoints );
    
    if ( !IsCanInteract() ) {
        Interrupt( kInterruptReasonDeleteAllBreakpoints );
        
    } else {
        LLDBCommand command;
        command.SetCommandType(kCommandDeleteAllBreakpoints);
        SendCommand( command );
        m_pendingDeletionBreakpoints.clear();

    }
}