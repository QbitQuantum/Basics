void ProcessInterruptTerminateHandler::InterruptProcess(PROCESS_INFORMATION& info) {
  //block from second call
  if (IsInterrupted()) return;
  

  LOG.LogInfo(L"Service process will be killed, exit code would be 42");
  //TODO:implement kill process
  if (0 == TerminateProcess(info.hProcess, 42)) {
    LOG.LogWarnFormat(L"Failed to terminate service process. %s", LOG.GetLastError());
    return;
  }

  //mark interrupt to the process was sent
  Interrupt();
}