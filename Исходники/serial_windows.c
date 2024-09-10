int
serialMonitorWaitLines (SerialDevice *serial) {
  DWORD event;

  if (WaitCommEvent(serial->package.fileHandle, &event, NULL)) return 1;
  logWindowsSystemError("WaitCommEvent");
  return 0;
}