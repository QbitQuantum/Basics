GDBRemoteCommunication::PacketResult
GDBRemoteCommunicationServerPlatform::Handle_qC(
    StringExtractorGDBRemote &packet) {
  // NOTE: lldb should now be using qProcessInfo for process IDs.  This path
  // here
  // should not be used.  It is reporting process id instead of thread id.  The
  // correct answer doesn't seem to make much sense for lldb-platform.
  // CONSIDER: flip to "unsupported".
  lldb::pid_t pid = m_process_launch_info.GetProcessID();

  StreamString response;
  response.Printf("QC%" PRIx64, pid);

  // If we launch a process and this GDB server is acting as a platform,
  // then we need to clear the process launch state so we can start
  // launching another process. In order to launch a process a bunch or
  // packets need to be sent: environment packets, working directory,
  // disable ASLR, and many more settings. When we launch a process we
  // then need to know when to clear this information. Currently we are
  // selecting the 'qC' packet as that packet which seems to make the most
  // sense.
  if (pid != LLDB_INVALID_PROCESS_ID) {
    m_process_launch_info.Clear();
  }

  return SendPacketNoLock(response.GetString());
}