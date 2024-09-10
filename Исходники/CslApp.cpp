int CslApp::OnRun()
{
    if (GetTopWindow())
        wxApp::OnRun();

    return m_shutdown>CSL_SHUTDOWN_NORMAL ? 1 : 0;
}