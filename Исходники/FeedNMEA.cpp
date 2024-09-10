int
main(int argc, char **argv)
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

  ConsoleOperationEnvironment env;

  if (!port->WaitConnected(env)) {
    delete port;
    DeinitialiseIOThread();
    fprintf(stderr, "Failed to connect the port\n");
    return EXIT_FAILURE;
  }

  if (!port->StartRxThread()) {
    delete port;
    DeinitialiseIOThread();
    fprintf(stderr, "Failed to start the port thread\n");
    return EXIT_FAILURE;
  }

  char stamp[6] = "";

  char line[1024];
  while (fgets(line, sizeof(line), stdin) != NULL) {
    if (memcmp(line, "$GP", 3) == 0 &&
        (memcmp(line + 3, "GGA", 3) == 0 ||
         memcmp(line + 3, "RMC", 3) == 0) &&
        line[6] == ',' &&
        strncmp(stamp, line + 7, sizeof(stamp)) != 0) {
      /* the time stamp has changed - sleep for one second */
      Sleep(1000);
      strncpy(stamp, line + 7, sizeof(stamp));
    }

    if (!port->FullWriteString(line, env, 1000)) {
      fprintf(stderr, "Failed to write to port\n");
      delete port;
      return EXIT_FAILURE;
    }
  }

  delete port;
  DeinitialiseIOThread();
  return EXIT_SUCCESS;
}