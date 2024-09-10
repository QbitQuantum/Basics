Error
Host::LaunchProcess (ProcessLaunchInfo &launch_info)
{
    Error error;
    char exe_path[PATH_MAX];

    PlatformSP host_platform_sp (Platform::GetHostPlatform ());

    const ArchSpec &arch_spec = launch_info.GetArchitecture();

    FileSpec exe_spec(launch_info.GetExecutableFile());

    FileSpec::FileType file_type = exe_spec.GetFileType();
    if (file_type != FileSpec::eFileTypeRegular)
    {
        lldb::ModuleSP exe_module_sp;
        error = host_platform_sp->ResolveExecutable (exe_spec,
                                                     arch_spec,
                                                     exe_module_sp,
                                                     NULL);

        if (error.Fail())
            return error;

        if (exe_module_sp)
            exe_spec = exe_module_sp->GetFileSpec();
    }

    if (exe_spec.Exists())
    {
        exe_spec.GetPath (exe_path, sizeof(exe_path));
    }
    else
    {
        launch_info.GetExecutableFile().GetPath (exe_path, sizeof(exe_path));
        error.SetErrorStringWithFormat ("executable doesn't exist: '%s'", exe_path);
        return error;
    }

    assert(!launch_info.GetFlags().Test (eLaunchFlagLaunchInTTY));

    ::pid_t pid = LLDB_INVALID_PROCESS_ID;

    error = LaunchProcessPosixSpawn(exe_path, launch_info, pid);

    if (pid != LLDB_INVALID_PROCESS_ID)
    {
        // If all went well, then set the process ID into the launch info
        launch_info.SetProcessID(pid);

        Log *log(lldb_private::GetLogIfAllCategoriesSet (LIBLLDB_LOG_PROCESS));

        // Make sure we reap any processes we spawn or we will have zombies.
        if (!launch_info.MonitorProcess())
        {
            const bool monitor_signals = false;
            StartMonitoringChildProcess (Process::SetProcessExitStatus,
                                         NULL,
                                         pid,
                                         monitor_signals);
            if (log)
                log->PutCString ("monitored child process with default Process::SetProcessExitStatus.");
        }
        else
        {
            if (log)
                log->PutCString ("monitored child process with user-specified process monitor.");
        }
    }
    else
    {
        // Invalid process ID, something didn't go well
        if (error.Success())
            error.SetErrorString ("process launch failed for unknown reasons");
    }
    return error;
}