const char * UHokuyo::getNameFromDevice()
{
  int i;
  //
  if (isPortOpen())
  {
    closePort();
  }
  // open portand ensure that receive thread is running
  start();
  if (isPortOpen())
  { // wait for port to open ...
    lock();
    Wait(0.1);
    printf("Name request [V\\n]...\n");
    // request forst message - vill probably be lost
    sendToDevice("V\n", 2);
    printf("Waiting for reply ...\n");
    Wait(0.1);
    // request again
    sendToDevice("V\n", 2);
    // wait for reply
    i = 0;
    unlock();
    while (strlen(getName()) < 10)
    { // wait for reply
      Wait(0.1);
      i++;
      if (i > 20)
        break;
    }
    printf("Finished after <= %g secs\n", 0.1 * i);
    closePort();
  }
  return getName();
}