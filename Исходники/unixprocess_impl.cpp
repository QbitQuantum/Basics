void UnixProcessImpl::Cleanup()
{
    close(GetReadHandle());
    close(GetWriteHandle());

    if(m_thr) {
        // Stop the reader thread
        m_thr->Stop();
        delete m_thr;
    }
    m_thr = NULL;

    if(GetPid() != wxNOT_FOUND) {
        wxKill(GetPid(), GetHardKill() ? wxSIGKILL : wxSIGTERM, NULL, wxKILL_CHILDREN);
        // The Zombie cleanup is done in app.cpp in ::ChildTerminatedSingalHandler() signal handler
        int status(0);
        waitpid(-1, &status, WNOHANG);
    }
}