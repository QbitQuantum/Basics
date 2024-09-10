void hvApp::OnIdle(wxIdleEvent& event)
{
    if (m_exitIfNoMainWindow && !GetTopWindow())
        ExitMainLoop();

    event.Skip();
    event.RequestMore();
}