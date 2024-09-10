void wxThread::Exit(ExitCode status)
{
    wxASSERT_MSG( This() == this,
                  _T("wxThread::Exit() can only be called in the context of the same thread") );

    if ( m_isDetached )
    {
        // from the moment we call OnExit(), the main program may terminate at
        // any moment, so mark this thread as being already in process of being
        // deleted or wxThreadModule::OnExit() will try to delete it again
        ScheduleThreadForDeletion();
    }

    // don't enter m_critsect before calling OnExit() because the user code
    // might deadlock if, for example, it signals a condition in OnExit() (a
    // common case) while the main thread calls any of functions entering
    // m_critsect on us (almost all of them do)
    OnExit();

    // delete C++ thread object if this is a detached thread - user is
    // responsible for doing this for joinable ones
    if ( m_isDetached )
    {
        // FIXME I'm feeling bad about it - what if another thread function is
        //       called (in another thread context) now? It will try to access
        //       half destroyed object which will probably result in something
        //       very bad - but we can't protect this by a crit section unless
        //       we make it a global object, but this would mean that we can
        //       only call one thread function at a time :-(
        DeleteThread(this);
        pthread_setspecific(gs_keySelf, 0);
    }
    else
    {
        m_critsect.Enter();
        m_internal->SetState(STATE_EXITED);
        m_critsect.Leave();
    }

    // terminate the thread (pthread_exit() never returns)
    pthread_exit(status);

    wxFAIL_MSG(_T("pthread_exit() failed"));
}