Error
PlatformLinux::LaunchNativeProcess (
    ProcessLaunchInfo &launch_info,
    lldb_private::NativeProcessProtocol::NativeDelegate &native_delegate,
    NativeProcessProtocolSP &process_sp)
{
#if !defined(__linux__)
    return Error("only implemented on Linux hosts");
#else
    if (!IsHost ())
        return Error("PlatformLinux::%s (): cannot launch a debug process when not the host", __FUNCTION__);

    // Retrieve the exe module.
    lldb::ModuleSP exe_module_sp;

    Error error = ResolveExecutable (
        launch_info.GetExecutableFile (),
        launch_info.GetArchitecture (),
        exe_module_sp,
        NULL);

    if (!error.Success ())
        return error;

    if (!exe_module_sp)
        return Error("exe_module_sp could not be resolved for %s", launch_info.GetExecutableFile ().GetPath ().c_str ());

    // Launch it for debugging
    error = NativeProcessLinux::LaunchProcess (
        exe_module_sp.get (),
        launch_info,
        native_delegate,
        process_sp);

    return error;
#endif
}