StateType GDBRemoteClientBase::SendContinuePacketAndWaitForResponse(
    ContinueDelegate &delegate, const UnixSignals &signals,
    llvm::StringRef payload, StringExtractorGDBRemote &response) {
  Log *log(ProcessGDBRemoteLog::GetLogIfAllCategoriesSet(GDBR_LOG_PROCESS));
  response.Clear();

  {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_continue_packet = payload;
    m_should_stop = false;
  }
  ContinueLock cont_lock(*this);
  if (!cont_lock)
    return eStateInvalid;
  OnRunPacketSent(true);

  for (;;) {
    PacketResult read_result = ReadPacket(response, kInterruptTimeout, false);
    switch (read_result) {
    case PacketResult::ErrorReplyTimeout: {
      std::lock_guard<std::mutex> lock(m_mutex);
      if (m_async_count == 0)
        continue;
      if (steady_clock::now() >= m_interrupt_time + kInterruptTimeout)
        return eStateInvalid;
    }
    case PacketResult::Success:
      break;
    default:
      if (log)
        log->Printf("GDBRemoteClientBase::%s () ReadPacket(...) => false",
                    __FUNCTION__);
      return eStateInvalid;
    }
    if (response.Empty())
      return eStateInvalid;

    const char stop_type = response.GetChar();
    if (log)
      log->Printf("GDBRemoteClientBase::%s () got packet: %s", __FUNCTION__,
                  response.GetStringRef().c_str());

    switch (stop_type) {
    case 'W':
    case 'X':
      return eStateExited;
    case 'E':
      // ERROR
      return eStateInvalid;
    default:
      if (log)
        log->Printf("GDBRemoteClientBase::%s () unrecognized async packet",
                    __FUNCTION__);
      return eStateInvalid;
    case 'O': {
      std::string inferior_stdout;
      response.GetHexByteString(inferior_stdout);
      delegate.HandleAsyncStdout(inferior_stdout);
      break;
    }
    case 'A':
      delegate.HandleAsyncMisc(
          llvm::StringRef(response.GetStringRef()).substr(1));
      break;
    case 'J':
      delegate.HandleAsyncStructuredDataPacket(response.GetStringRef());
      break;
    case 'T':
    case 'S':
      // Do this with the continue lock held.
      const bool should_stop = ShouldStop(signals, response);
      response.SetFilePos(0);

      // The packet we should resume with. In the future
      // we should check our thread list and "do the right thing"
      // for new threads that show up while we stop and run async
      // packets. Setting the packet to 'c' to continue all threads
      // is the right thing to do 99.99% of the time because if a
      // thread was single stepping, and we sent an interrupt, we
      // will notice above that we didn't stop due to an interrupt
      // but stopped due to stepping and we would _not_ continue.
      // This packet may get modified by the async actions (e.g. to send a
      // signal).
      m_continue_packet = 'c';
      cont_lock.unlock();

      delegate.HandleStopReply();
      if (should_stop)
        return eStateStopped;

      switch (cont_lock.lock()) {
      case ContinueLock::LockResult::Success:
        break;
      case ContinueLock::LockResult::Failed:
        return eStateInvalid;
      case ContinueLock::LockResult::Cancelled:
        return eStateStopped;
      }
      OnRunPacketSent(false);
      break;
    }
  }
}