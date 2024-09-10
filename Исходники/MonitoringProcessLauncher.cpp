HostProcess
MonitoringProcessLauncher::LaunchProcess(const ProcessLaunchInfo &launch_info,
                                         Status &error) {
  ProcessLaunchInfo resolved_info(launch_info);

  error.Clear();
  char exe_path[PATH_MAX];

  PlatformSP host_platform_sp(Platform::GetHostPlatform());

  const ArchSpec &arch_spec = resolved_info.GetArchitecture();

  FileSpec exe_spec(resolved_info.GetExecutableFile());

  llvm::sys::fs::file_status stats;
  status(exe_spec.GetPath(), stats);
  if (!is_regular_file(stats)) {
    ModuleSpec module_spec(exe_spec, arch_spec);
    lldb::ModuleSP exe_module_sp;
    error =
        host_platform_sp->ResolveExecutable(module_spec, exe_module_sp, NULL);

    if (error.Fail())
      return HostProcess();

    if (exe_module_sp) {
      exe_spec = exe_module_sp->GetFileSpec();
      status(exe_spec.GetPath(), stats);
    }
  }

  if (exists(stats)) {
    exe_spec.GetPath(exe_path, sizeof(exe_path));
  } else {
    resolved_info.GetExecutableFile().GetPath(exe_path, sizeof(exe_path));
    error.SetErrorStringWithFormat("executable doesn't exist: '%s'", exe_path);
    return HostProcess();
  }

  resolved_info.SetExecutableFile(exe_spec, false);
  assert(!resolved_info.GetFlags().Test(eLaunchFlagLaunchInTTY));

  HostProcess process =
      m_delegate_launcher->LaunchProcess(resolved_info, error);

  if (process.GetProcessId() != LLDB_INVALID_PROCESS_ID) {
    Log *log(lldb_private::GetLogIfAllCategoriesSet(LIBLLDB_LOG_PROCESS));

    Host::MonitorChildProcessCallback callback =
        launch_info.GetMonitorProcessCallback();

    bool monitor_signals = false;
    if (callback) {
      // If the ProcessLaunchInfo specified a callback, use that.
      monitor_signals = launch_info.GetMonitorSignals();
    } else {
      callback = Process::SetProcessExitStatus;
    }

    process.StartMonitoring(callback, monitor_signals);
    if (log)
      log->PutCString("started monitoring child process.");
  } else {
    // Invalid process ID, something didn't go well
    if (error.Success())
      error.SetErrorString("process launch failed for unknown reasons");
  }
  return process;
}