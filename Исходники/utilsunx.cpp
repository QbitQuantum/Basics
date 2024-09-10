void wxExecuteData::OnStart(int pid_)
{
    wxCHECK_RET( wxTheApp,
                 wxS("Ensure wxTheApp is set before calling wxExecute()") );

    // Setup the signal handler for SIGCHLD to be able to detect the child
    // termination.
    //
    // Notice that SetSignalHandler() is idempotent, so it's fine to call
    // it more than once with the same handler.
    wxTheApp->SetSignalHandler(SIGCHLD, OnSomeChildExited);


    // Remember the child PID to be able to wait for it later.
    pid = pid_;

    // Also save it in wxProcess where it will be accessible to the user code.
    if ( process )
        process->SetPid(pid);

    // Add this object itself to the list of child processes so that
    // we can check for its termination the next time we get SIGCHLD.
    ms_childProcesses[pid] = this;

    // However, if the child exited before we finished setting up above,
    // we may have already missed its SIGCHLD.  So we also do an explicit
    // check here before returning.
    int exitcode;
    if ( CheckForChildExit(pid, &exitcode) )
    {
        // Handle its termination if it did.
        // This call will implicitly remove it from ms_childProcesses
        // and, if running asynchronously, it will delete itself.
        OnExit(exitcode);
    }
}