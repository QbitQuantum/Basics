int
main(int argc,
     char *argv[]) {

  typedef enum {ERROR, HALT, LOG, REGISTER, TEST} Commands;
  const char *COMMANDS[] = {"error", "halt", "log", "register", "test"};
  const char *USAGE = "ctrl_host [-P password] [-t n] [-z] <command> host ...";

  int c;
  Commands command;
  struct host_cookie cookie;
  struct host_desc host;
  HostInfo info;
  struct host_desc nsDesc;
  unsigned short nsPort;
  const char *parameter = NULL;
  const char *password;
  const char *STATII[] = {"dead", "healthy", "sick", "unresponsive"};
  unsigned short sensorPort;
  HostStatii status;
  const char *TYPES[] = {"forecaster", "memory", "name_server", "sensor"};
  double timeOut;
  extern char *optarg;
  extern int optind;

  password = NULL;
  timeOut = PKTTIMEOUT;

  DirectDiagnostics(DIAGINFO, stdout);
  DirectDiagnostics(DIAGLOG, stdout);
  DirectDiagnostics(DIAGWARN, stderr);
  DirectDiagnostics(DIAGERROR, stderr);
  DirectDiagnostics(DIAGFATAL, stderr);

  nsPort = DefaultHostPort(NAME_SERVER_HOST);
  sensorPort = DefaultHostPort(SENSOR_HOST);

  while((c = getopt(argc, argv, SWITCHES)) != EOF) {

    switch(c) {

    case 'P':
      password = optarg;
      break;

    case 't':
      timeOut = atof(optarg);
      break;

    case 'z':
      DirectDiagnostics(DIAGINFO, DIAGSUPPRESS);
      DirectDiagnostics(DIAGLOG, DIAGSUPPRESS);
      DirectDiagnostics(DIAGWARN, DIAGSUPPRESS);
      DirectDiagnostics(DIAGERROR, DIAGSUPPRESS);
      DirectDiagnostics(DIAGFATAL, DIAGSUPPRESS);
      break;

    default:
      fprintf(stderr, "unrecognized switch\n%s\n", USAGE);
      exit(1);
      break;

    }

  }

  if(optind >= argc) {
    fprintf(stderr, "%s\n", USAGE);
    exit(1);
  }

  for(command = ERROR; command <= TEST; command++) {
    if(strncasecmp(COMMANDS[command], argv[optind], strlen(argv[optind])) == 0)
      break;
  }

  if(command > TEST) {
    fprintf(stderr, "unknown command %s\n", argv[optind]);
    exit(1);
  }

  optind++;

  switch(command) {

  case REGISTER:
    if(optind >= argc) {
      fprintf(stderr, "missing parameter for %c command\n", command);
      exit(1);
    }
    parameter = argv[optind++];
    HostDValue(parameter, nsPort, &nsDesc);
    if(!IsANameServer(&nsDesc, timeOut)) {
      fprintf(stderr, "%s is not a name server\n", parameter);
    }
    break;

  default:
    break;

  }

  for(; optind < argc; optind++) {

    HostDValue(argv[optind], sensorPort, &host);
    MakeHostCookie(host.host_name, host.port, &cookie);

    if(!ConnectToHost(&cookie, &cookie.sd)) {
      if(command == TEST) {
        printf("%s dead\n", HostDImage(&host));
      }
      else {
        WARN1("connect %s failed\n", HostDImage(&host));
      }
      continue;
    }

    switch(command) {

    case ERROR:
      if(!DoDiagnosticsCommand(cookie.sd, ALL_ERRORS, timeOut)) {
        WARN1("error toggle failed for host %s\n", HostDImage(&host));
      }
      break;

    case HALT:
      if(!DoHaltHost(cookie.sd, password, timeOut)) {
        WARN1("halt failed for host %s\n", HostDImage(&host));
      }
      break;

    case LOG:
      if(!DoDiagnosticsCommand(cookie.sd, ALL_LOGS, timeOut)) {
        WARN1("log toggle failed for host %s\n", HostDImage(&host));
      }
      break;

    case REGISTER:
      if(!DoRegisterHost(cookie.sd, parameter, password, timeOut)) {
        WARN1("registration change failed for host %s\n", HostDImage(&host));
      }
      break;

    case TEST:
      status = DoTestHost(cookie.sd, &info, timeOut);
      if((status == HEALTHY) || (status == SICK)) {
        printf("%s %s ", TYPES[info.hostType], HostDImage(&host));
        if((strcmp(info.registrationName, HostDImage(&host)) != 0) &&
           (strcmp(info.registrationName, "") != 0)) {
          printf("(%s) ", info.registrationName);
        }
        printf("registered with %s ", info.nameServer);
      }
      else {
        printf("%s ", HostDImage(&host));
      }
      printf("%s\n", STATII[status]);
      break;

    }

    DisconnectHost(&cookie);

  }

  return(0);

}