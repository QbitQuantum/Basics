void wxLuaDebuggerBase::OnEndDebugeeProcess(wxProcessEvent& event)
{
    //wxPrintf(wxT("OnEndDebugeeProcess the m_debuggeeProcess %p %d exists %d\n"), m_debuggeeProcess, m_debuggeeProcessID, wxProcess::Exists(m_debuggeeProcessID)); fflush(stdout);

    // The process's OnTerminate will null m_debuggeeProcess,
    // but if in destructor it's already NULL and don't send event.
    if (m_debuggeeProcess != NULL)
    {
        wxLuaDebuggerEvent debugEvent(wxEVT_WXLUA_DEBUGGER_EXIT, this);
        debugEvent.SetMessage(wxString::Format(wxT("Process (%d) ended with exit code : %d"), event.GetPid(), event.GetExitCode()));
        wxPostEvent(this, debugEvent);
    }

    event.Skip();
}