bool
DeviceDescriptor::DoOpen(OperationEnvironment &env)
{
  assert(config.IsAvailable());

  if (config.port_type == DeviceConfig::PortType::INTERNAL)
    return OpenInternalSensors();

  if (config.port_type == DeviceConfig::PortType::DROIDSOAR_V2)
    return OpenDroidSoarV2();

  if (config.port_type == DeviceConfig::PortType::I2CPRESSURESENSOR)
    return OpenI2Cbaro();

  if (config.port_type == DeviceConfig::PortType::NUNCHUCK)
    return OpenNunchuck();

  if (config.port_type == DeviceConfig::PortType::IOIOVOLTAGE)
    return OpenVoltage();

  reopen_clock.Update();

  Port *port = OpenPort(config, port_listener, *this);
  if (port == nullptr) {
    TCHAR name_buffer[64];
    const TCHAR *name = config.GetPortName(name_buffer, 64);

    StaticString<256> msg;
    msg.Format(_T("%s: %s."), _("Unable to open port"), name);
    env.SetErrorMessage(msg);
    return false;
  }

  DumpPort *dump_port = new DumpPort(port);
  dump_port->Disable();

  if (!port->WaitConnected(env) || !OpenOnPort(dump_port, env)) {
    if (!env.IsCancelled())
      ++n_failures;

    delete dump_port;
    return false;
  }

  ResetFailureCounter();
  return true;
}