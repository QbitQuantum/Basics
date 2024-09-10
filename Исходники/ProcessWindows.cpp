Error
ProcessWindows::DoLaunch(Module *exe_module,
                         ProcessLaunchInfo &launch_info)
{
    // Even though m_session_data is accessed here, it is before a debugger thread has been
    // kicked off.  So there's no race conditions, and it shouldn't be necessary to acquire
    // the mutex.

    Error result;
    if (!launch_info.GetFlags().Test(eLaunchFlagDebug))
    {
        StreamString stream;
        stream.Printf("ProcessWindows unable to launch '%s'.  ProcessWindows can only be used for debug launches.",
                      launch_info.GetExecutableFile().GetPath().c_str());
        std::string message = stream.GetString();
        result.SetErrorString(message.c_str());

        WINERR_IFALL(WINDOWS_LOG_PROCESS, message.c_str());
        return result;
    }

    bool stop_at_entry = launch_info.GetFlags().Test(eLaunchFlagStopAtEntry);
    m_session_data.reset(new ProcessWindowsData(stop_at_entry));

    SetPrivateState(eStateLaunching);
    DebugDelegateSP delegate(new LocalDebugDelegate(shared_from_this()));
    m_session_data->m_debugger.reset(new DebuggerThread(delegate));
    DebuggerThreadSP debugger = m_session_data->m_debugger;

    // Kick off the DebugLaunch asynchronously and wait for it to complete.
    result = debugger->DebugLaunch(launch_info);
    if (result.Fail())
    {
        WINERR_IFALL(WINDOWS_LOG_PROCESS, "DoLaunch failed launching '%s'.  %s",
                     launch_info.GetExecutableFile().GetPath().c_str(), result.AsCString());
        return result;
    }

    HostProcess process;
    Error error = WaitForDebuggerConnection(debugger, process);
    if (error.Fail())
    {
        WINERR_IFALL(WINDOWS_LOG_PROCESS, "DoLaunch failed launching '%s'.  %s",
                     launch_info.GetExecutableFile().GetPath().c_str(), error.AsCString());
        return error;
    }

    WINLOG_IFALL(WINDOWS_LOG_PROCESS, "DoLaunch successfully launched '%s'",
                 launch_info.GetExecutableFile().GetPath().c_str());

    // We've hit the initial stop.  If eLaunchFlagsStopAtEntry was specified, the private state
    // should already be set to eStateStopped as a result of hitting the initial breakpoint.  If
    // it was not set, the breakpoint should have already been resumed from and the private state
    // should already be eStateRunning.
    launch_info.SetProcessID(process.GetProcessId());
    SetID(process.GetProcessId());

    return result;
}