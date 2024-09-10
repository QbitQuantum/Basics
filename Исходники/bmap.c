int bmap_main(int argc, char *argv[]) {
  /* The "real" main is nmap_main().  This function hijacks control at the
     beginning to do the following:
     1) Check the environment variable NMAP_ARGS.
     2) Check if Nmap was called with --resume.
     3) Resume a previous scan or just call nmap_main.
  */
  char command[2048];
  int myargc;
  char **myargv = NULL ;
  char *cptr;
  int ret;
  int i;

  set_program_name(argv[0]);

  if ((cptr = getenv("NMAP_ARGS"))) {
    if (Snprintf(command, sizeof(command), "nmap %s", cptr) >= (int) sizeof(command)) {
        error("Warning: NMAP_ARGS variable is too long, truncated");
    }
    /* copy rest of command-line arguments */
    for (i = 1; i < argc && strlen(command) + strlen(argv[i]) + 1 < sizeof(command); i++) {
      strcat(command, " ");
      strcat(command, argv[i]);
    }
    myargc = arg_parse(command, &myargv);
    if (myargc < 1) {
      fatal("NMAP_ARGS variable could not be parsed");
    }
    ret = nmap_main(myargc, myargv);
    arg_parse_free(myargv);
    return ret;
  }


  return nmap_main(argc, argv);
}