bool
CaiGpsNavDevice::Open(OperationEnvironment &env)
{
  port->Write(CtrlC);
  env.Sleep(50);
  port->Write("NMEA\r");

  // This is for a slightly different mode, that
  // apparently outputs pressure info too...
  //port->Write("PNP\r\n");
  //port->Write("LOG 0\r\n");

  return true;
}