void ULaserDevice::stop(bool justClosePort)
{
  if (isPortOpen())
  { // stop contiious mode and close serial port
    closePort();
  }
  if (threadRunning and not justClosePort)
  { // stop and join thread
    threadStop = true;
    pthread_join(threadHandle, NULL);
  }
  // close log too (if open)
  datalog.closeLog();
}