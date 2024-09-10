Error
PlatformRemoteGDBServer::LaunchProcess (ProcessLaunchInfo &launch_info)
{
    Log *log(lldb_private::GetLogIfAllCategoriesSet (LIBLLDB_LOG_PLATFORM));
    Error error;
    lldb::pid_t pid = LLDB_INVALID_PROCESS_ID;

    if (log)
        log->Printf ("PlatformRemoteGDBServer::%s() called", __FUNCTION__);

    m_gdb_client.SetSTDIN ("/dev/null");
    m_gdb_client.SetSTDOUT ("/dev/null");
    m_gdb_client.SetSTDERR ("/dev/null");
    m_gdb_client.SetDisableASLR (launch_info.GetFlags().Test (eLaunchFlagDisableASLR));
    m_gdb_client.SetDetachOnError (launch_info.GetFlags().Test (eLaunchFlagDetachOnError));
    
    const char *working_dir = launch_info.GetWorkingDirectory();
    if (working_dir && working_dir[0])
    {
        m_gdb_client.SetWorkingDir (working_dir);
    }
    
    // Send the environment and the program + arguments after we connect
    const char **envp = launch_info.GetEnvironmentEntries().GetConstArgumentVector();

    if (envp)
    {
        const char *env_entry;
        for (int i=0; (env_entry = envp[i]); ++i)
        {
            if (m_gdb_client.SendEnvironmentPacket(env_entry) != 0)
                break;
        }
    }
    
    ArchSpec arch_spec = launch_info.GetArchitecture();
    const char *arch_triple = arch_spec.GetTriple().str().c_str();
    
    m_gdb_client.SendLaunchArchPacket(arch_triple);
    if (log)
        log->Printf ("PlatformRemoteGDBServer::%s() set launch architecture triple to '%s'", __FUNCTION__, arch_triple ? arch_triple : "<NULL>");

    const uint32_t old_packet_timeout = m_gdb_client.SetPacketTimeout (5);
    int arg_packet_err = m_gdb_client.SendArgumentsPacket (launch_info);
    m_gdb_client.SetPacketTimeout (old_packet_timeout);
    if (arg_packet_err == 0)
    {
        std::string error_str;
        if (m_gdb_client.GetLaunchSuccess (error_str))
        {
            pid = m_gdb_client.GetCurrentProcessID ();
            if (pid != LLDB_INVALID_PROCESS_ID)
            {
                launch_info.SetProcessID (pid);
                if (log)
                    log->Printf ("PlatformRemoteGDBServer::%s() pid %" PRIu64 " launched successfully", __FUNCTION__, pid);
            }
            else
            {
                if (log)
                    log->Printf ("PlatformRemoteGDBServer::%s() launch succeeded but we didn't get a valid process id back!", __FUNCTION__);
                // FIXME isn't this an error condition? Do we need to set an error here?  Check with Greg.
            }
        }
        else
        {
            error.SetErrorString (error_str.c_str());
            if (log)
                log->Printf ("PlatformRemoteGDBServer::%s() launch failed: %s", __FUNCTION__, error.AsCString ());
        }
    }
    else
    {
        error.SetErrorStringWithFormat("'A' packet returned an error: %i", arg_packet_err);
    }
    return error;
}