void WaitForDeviceDisconnected(BleApiConfiguration &configuration, pBleDevice dev)
{
  // do nothing for a continuously connected authenticator
  if (configuration.alwaysconnected)
    return;

#if defined(PLATFORM_WINDOWS) && defined(FEATURE_WINRT)
  if ((configuration.logging & BleApiLogging::Info) != 0)
    std::cout << "Waiting until device disconnects..." << std::endl;
  while (dev->IsConnected()) 
    dev->Sleep(100);
  if ((configuration.logging & BleApiLogging::Info) != 0)
    std::cout << "'... disconnected." << std::endl;
#endif
}