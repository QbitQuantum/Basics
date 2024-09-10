/*! Init the WMV bus client
 *  \param addr The clients address
 *  \param dev The device name of the attached communication interface, for example COM? in windows or /dev/ttyUSB? for Linux
 *  \param listener A pointer to a function which should be called when there is a message to be parsed from the bus
 *  \return 0 if the port was open sucessfully, 1 if not */
int WMVBusClient::initClient(unsigned char addr, QString dev, BusMessageListener *listener) {
  busAddr = addr;
  deviceName = dev;
  msgListener = listener;

  return(openPort(deviceName));
}