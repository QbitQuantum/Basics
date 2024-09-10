int
main(int argc, char **argv)
{
  Args args(argc, argv, "DRIVER PORT BAUD");
  Emulator *emulator = LoadEmulator(args);
  const DeviceConfig config = ParsePortArgs(args);
  args.ExpectEnd();

  InitialiseIOThread();

  Port *port = OpenPort(config, *emulator->handler);
  if (port == NULL) {
    delete emulator;
    fprintf(stderr, "Failed to open COM port\n");
    return EXIT_FAILURE;
  }

  emulator->port = port;

  ConsoleOperationEnvironment env;
  emulator->env = &env;

  if (!port->WaitConnected(env)) {
    delete port;
    delete emulator;
    DeinitialiseIOThread();
    fprintf(stderr, "Failed to connect the port\n");
    return EXIT_FAILURE;
  }

  if (!port->StartRxThread()) {
    delete port;
    delete emulator;
    DeinitialiseIOThread();
    fprintf(stderr, "Failed to start the port thread\n");
    return EXIT_FAILURE;
  }

  while (port->GetState() != PortState::FAILED)
    Sleep(1000);

  delete port;
  delete emulator;
  DeinitialiseIOThread();
  return EXIT_SUCCESS;
}