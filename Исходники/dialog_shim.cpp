    // sets the "should exit" flag and wakes up the loop so that it terminates
    // soon
    void ScheduleExit( int rc = 0 )
    {
        wxCHECK_RET( IsInsideRun(), wxT("can't call ScheduleExit() if not running") );

        m_exitcode = rc;
        m_shouldExit = true;

        OnExit();

        // all we have to do to exit from the loop is to (maybe) wake it up so that
        // it can notice that Exit() had been called
        //
        // in particular, do *not* use here calls such as PostQuitMessage() (under
        // MSW) which terminate the current event loop here because we're not sure
        // that it is going to be processed by the correct event loop: it would be
        // possible that another one is started and terminated by mistake if we do
        // this
        WakeUp();
    }