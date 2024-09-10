int main(int argc, char **argv)
{
  Args args(argc, argv, "PORT BAUD");
  const DeviceConfig config = ParsePortArgs(args);
  args.ExpectEnd();

  InitialiseIOThread();

  MyHandler handler;
  Port *port = OpenPort(config, handler);
  if (port == NULL) {
    fprintf(stderr, "Failed to open COM port\n");
    return EXIT_FAILURE;
  }

  if (!port->StartRxThread()) {
    delete port;
    fprintf(stderr, "Failed to start the port thread\n");
    return EXIT_FAILURE;
  }

  while (true)
    Sleep(10000);

  delete port;
  DeinitialiseIOThread();
  return EXIT_SUCCESS;
}