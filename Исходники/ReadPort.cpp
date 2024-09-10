int main(int argc, char **argv)
{
  Args args(argc, argv, "PORT BAUD");
  const DeviceConfig config = ParsePortArgs(args);
  args.ExpectEnd();

  InitialiseIOThread();

  Port *port = OpenPort(config, nullptr, *(DataHandler *)nullptr);
  if (port == NULL) {
    delete port;
    fprintf(stderr, "Failed to open COM port\n");
    return EXIT_FAILURE;
  }

  ConsoleOperationEnvironment env;

  if (!port->WaitConnected(env)) {
    delete port;
    DeinitialiseIOThread();
    fprintf(stderr, "Failed to connect the port\n");
    return EXIT_FAILURE;
  }

  char buffer[4096];
  while (true) {
    switch (port->WaitRead(env, 60000)) {
    case Port::WaitResult::READY:
      break;

    case Port::WaitResult::TIMEOUT:
      continue;

    case Port::WaitResult::FAILED:
      delete port;
      return EXIT_FAILURE;

    case Port::WaitResult::CANCELLED:
      delete port;
      return EXIT_SUCCESS;
    }

    int nbytes = port->Read(buffer, sizeof(buffer));
    if (nbytes < 0)
      break;

    fwrite((const void *)buffer, 1, nbytes, stdout);
  }

  delete port;
  DeinitialiseIOThread();
  return EXIT_SUCCESS;
}