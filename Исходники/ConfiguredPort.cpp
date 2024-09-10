static Port *
OpenPortInternal(const DeviceConfig &config, DataHandler &handler)
{
  const TCHAR *path = NULL;
  TCHAR buffer[MAX_PATH];

  switch (config.port_type) {
  case DeviceConfig::PortType::DISABLED:
    return NULL;

  case DeviceConfig::PortType::SERIAL:
    if (config.path.empty())
      return NULL;

    path = config.path.c_str();
    break;

  case DeviceConfig::PortType::RFCOMM:
#ifdef ANDROID
    if (config.bluetooth_mac.empty()) {
      LogFormat("No Bluetooth MAC configured");
      return NULL;
    }

    return OpenAndroidBluetoothPort(config.bluetooth_mac, handler);
#else
    LogFormat("Bluetooth not available on this platform");
    return NULL;
#endif

  case DeviceConfig::PortType::RFCOMM_SERVER:
#ifdef ANDROID
    return OpenAndroidBluetoothServerPort(handler);
#else
    LogFormat("Bluetooth not available on this platform");
    return NULL;
#endif

  case DeviceConfig::PortType::IOIOUART:
#if defined(ANDROID) && defined(IOIOLIB)
    if (config.ioio_uart_id >= AndroidIOIOUartPort::getNumberUarts()) {
      LogFormat("No IOIOUart configured in profile");
      return NULL;
    }

    return OpenAndroidIOIOUartPort(config.ioio_uart_id, config.baud_rate,
                                   handler);
#else
    LogFormat("IOIO Uart not available on this platform or version");
    return NULL;
#endif

  case DeviceConfig::PortType::AUTO:
    if (!DetectGPS(buffer, sizeof(buffer))) {
      LogFormat("no GPS detected");
      return NULL;
    }

    LogStartUp(_T("GPS detected: %s"), buffer);

    path = buffer;
    break;

  case DeviceConfig::PortType::INTERNAL:
  case DeviceConfig::PortType::DROIDSOAR_V2:
  case DeviceConfig::PortType::NUNCHUCK:
  case DeviceConfig::PortType::I2CPRESSURESENSOR:
  case DeviceConfig::PortType::IOIOVOLTAGE:
    break;

  case DeviceConfig::PortType::TCP_LISTENER: {
    TCPPort *port = new TCPPort(handler);
    if (!port->Open(config.tcp_port)) {
      delete port;
      return NULL;
    }

    return port;
  }

  case DeviceConfig::PortType::UDP_LISTENER: {
    SocketPort *port = new SocketPort(handler);
    if (!port->OpenUDPListener(config.tcp_port)) {
      delete port;
      return NULL;
    }

    return port;
  }

  case DeviceConfig::PortType::PTY: {
#if defined(HAVE_POSIX) && !defined(ANDROID)
    if (config.path.empty())
      return NULL;

    if (unlink(config.path.c_str()) < 0 && errno != ENOENT)
      return NULL;

    TTYPort *port = new TTYPort(handler);
    const char *slave_path = port->OpenPseudo();
    if (slave_path == NULL) {
      delete port;
      return NULL;
    }

    if (symlink(slave_path, config.path.c_str()) < 0) {
      delete port;
      return NULL;
    }

    return port;
#else
    return NULL;
#endif
  }
  }

  if (path == NULL)
    return NULL;

#ifdef HAVE_POSIX
  TTYPort *port = new TTYPort(handler);
#else
  SerialPort *port = new SerialPort(handler);
#endif
  if (!port->Open(path, config.baud_rate)) {
    delete port;
    return NULL;
  }

  return port;
}