// Returns false on timeout, true when data has been read even if that data
// didn't form a usable command. Is there is no usable command, cmd is null.
bool DebuggerCommand::Receive(DebuggerThriftBuffer &thrift,
                              DebuggerCommandPtr &cmd, const char *caller) {
  TRACE(5, "DebuggerCommand::Receive\n");
  cmd.reset();

  struct pollfd fds[1];
  fds[0].fd = thrift.getSocket()->fd();
  fds[0].events = POLLIN|POLLERR|POLLHUP;
  int ret = poll(fds, 1, POLLING_SECONDS * 1000);
  if (ret == 0) return false; // Timeout
  if (ret == -1) {
    auto errorNumber = errno; // Just in case TRACE_RB changes errno
    TRACE_RB(1, "DebuggerCommand::Receive: error %d\n", errorNumber);
    return errorNumber != EINTR; // Treat signals as timeouts
  }
  // If we don't have any data to read (POLLIN) then we're done. If we
  // do have data we'll attempt to read and decode it below, even if
  // there are other error bits set.
  if (!(fds[0].revents & POLLIN)) {
    TRACE_RB(1, "DebuggerCommand::Receive: revents %d\n", fds[0].revents);
    return true;
  }

  int32_t type;
  std::string clsname;
  try {
    thrift.reset(true);
    thrift.read(type);
    thrift.read(clsname);
  } catch (...) {
    // Note: this error case is difficult to test. But, it's exactly the same
    // as the error noted below. Make sure to keep handling of both of these
    // errors in sync.
    TRACE_RB(1, "%s: socket error receiving command", caller);
    return true;
  }

  TRACE(1, "DebuggerCommand::Receive: got cmd of type %d\n", type);

  // not all commands are here, as not all commands need to be sent over wire
  switch (type) {
    case KindOfBreak    :  cmd = DebuggerCommandPtr(new CmdBreak    ()); break;
    case KindOfContinue :  cmd = DebuggerCommandPtr(new CmdContinue ()); break;
    case KindOfDown     :  cmd = DebuggerCommandPtr(new CmdDown     ()); break;
    case KindOfException:  cmd = DebuggerCommandPtr(new CmdException()); break;
    case KindOfFrame    :  cmd = DebuggerCommandPtr(new CmdFrame    ()); break;
    case KindOfGlobal   :  cmd = DebuggerCommandPtr(new CmdGlobal   ()); break;
    case KindOfInfo     :  cmd = DebuggerCommandPtr(new CmdInfo     ()); break;
    case KindOfConstant :  cmd = DebuggerCommandPtr(new CmdConstant ()); break;
    case KindOfList     :  cmd = DebuggerCommandPtr(new CmdList     ()); break;
    case KindOfMachine  :  cmd = DebuggerCommandPtr(new CmdMachine  ()); break;
    case KindOfNext     :  cmd = DebuggerCommandPtr(new CmdNext     ()); break;
    case KindOfOut      :  cmd = DebuggerCommandPtr(new CmdOut      ()); break;
    case KindOfPrint    :  cmd = DebuggerCommandPtr(new CmdPrint    ()); break;
    case KindOfQuit     :  cmd = DebuggerCommandPtr(new CmdQuit     ()); break;
    case KindOfRun      :  cmd = DebuggerCommandPtr(new CmdRun      ()); break;
    case KindOfStep     :  cmd = DebuggerCommandPtr(new CmdStep     ()); break;
    case KindOfThread   :  cmd = DebuggerCommandPtr(new CmdThread   ()); break;
    case KindOfUp       :  cmd = DebuggerCommandPtr(new CmdUp       ()); break;
    case KindOfVariable :  cmd = DebuggerCommandPtr(new CmdVariable ()); break;
    case KindOfVariableAsync :
      cmd = DebuggerCommandPtr(new CmdVariable (KindOfVariableAsync)); break;
    case KindOfWhere    :  cmd = DebuggerCommandPtr(new CmdWhere    ()); break;
    case KindOfWhereAsync:
      cmd = DebuggerCommandPtr(new CmdWhere(KindOfWhereAsync)); break;
    case KindOfEval     :  cmd = DebuggerCommandPtr(new CmdEval     ()); break;
    case KindOfInterrupt:  cmd = DebuggerCommandPtr(new CmdInterrupt()); break;
    case KindOfSignal   :  cmd = DebuggerCommandPtr(new CmdSignal   ()); break;
    case KindOfShell    :  cmd = DebuggerCommandPtr(new CmdShell    ()); break;
    case KindOfInternalTesting :
      cmd = DebuggerCommandPtr(new CmdInternalTesting()); break;

    case KindOfExtended: {
      assert(!clsname.empty());
      cmd = CmdExtended::CreateExtendedCommand(clsname);
      assert(cmd);
      break;
    }

    default:
      TRACE_RB(1, "%s: received bad cmd type: %d", caller, type);
      cmd.reset();
      return true;
  }
  if (!cmd->recv(thrift)) {
    // Note: this error case is easily tested, and we have a test for it. But
    // the error case noted above is quite difficult to test. Keep these two
    // in sync.
    TRACE_RB(1, "%s: socket error receiving command", caller);
    cmd.reset();
  }
  return true;
}