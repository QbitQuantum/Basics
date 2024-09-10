// Main program body.
int
main (int argc, char *argv[])
{
  int currArg = 1;
  int NUM_ARGS = 4;

  handle_license_and_version_args(argc, argv, ASF_NAME_STRING);
  asfSplashScreen(argc, argv);

  if (argc >= 2 && strmatches(argv[1],"-help","--help",NULL))
    print_help();
  if (argc<3)
    rtc_usage(ASF_NAME_STRING);

  while (currArg < (argc-NUM_ARGS)) {
    char *key = argv[currArg++];
    if (strmatches(key,"-help","--help",NULL)) {
        print_help(); // doesn't return
    }
    else if (strmatches(key,"-log","--log",NULL)) {
      CHECK_ARG(1);
      strncpy_safe(logFile,GET_ARG(1),256);
      fLog = FOPEN(logFile, "a");
      logflag = TRUE;
    }
    else if (strmatches(key,"-quiet","--quiet","-q",NULL)) {
      quietflag = TRUE;
    }
    else {
      --currArg;
      break;
    }
  }

  if ((argc-currArg) < NUM_ARGS) {
    printf("Insufficient arguments.  Expected %d, got %d.\n",
           NUM_ARGS, argc-currArg);
    rtc_usage(argv[0]);
  } else if ((argc-currArg) > NUM_ARGS) {
    printf("Unknown argument: %s\n", argv[currArg]);
    rtc_usage(argv[0]);
  }

  int fail = uavsar_rtc(argv[currArg], argv[currArg+1], argv[currArg+2],
                        argv[currArg+3]);

  asfPrintStatus(fail ? "Failed.\n" : "Done.\n");
  return fail ? EXIT_FAILURE : EXIT_SUCCESS;
}