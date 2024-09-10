int
main(int argc, char **argv)
{
  Args args(argc, argv, "PORT BAUD");
  const DeviceConfig config = ParsePortArgs(args);
  args.ExpectEnd();

  InitialiseIOThread();

  NullDataHandler handler;
  std::unique_ptr<Port> port(OpenPort(config, handler));
  if (!port) {
    fprintf(stderr, "Failed to open COM port\n");
    return EXIT_FAILURE;
  }

  ConsoleOperationEnvironment env;

  if (!port->WaitConnected(env)) {
    fprintf(stderr, "Failed to connect the port\n");
    return EXIT_FAILURE;
  }

  RunUI(*port, env);

  DeinitialiseIOThread();

  return EXIT_SUCCESS;
}