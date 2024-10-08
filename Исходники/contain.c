int main(int argc, char **argv) {
  char *gidmap = NULL, *inside = NULL, *outside = NULL, *uidmap = NULL;
  char *bind = NULL;
  int hostnet = 0, master, option, stdio = 0;
  pid_t child, parent;

  while ((option = getopt(argc, argv, "+:b:cg:i:no:u:")) > 0)
    switch (option) {
      case 'b':
        bind = optarg;
        break;
      case 'c':
        stdio++;
        break;
      case 'g':
        gidmap = optarg;
        break;
      case 'i':
        inside = optarg;
        break;
      case 'n':
        hostnet++;
        break;
      case 'o':
        outside = optarg;
        break;
      case 'u':
        uidmap = optarg;
        break;
      default:
        usage(argv[0]);
    }

  if (argc <= optind)
    usage(argv[0]);

  parent = getpid();
  switch (child = fork()) {
    case -1:
      error(1, errno, "fork");
    case 0:
      raise(SIGSTOP);
//      if (geteuid() != 0)
//        denysetgroups(parent);
      writemap(parent, GID, gidmap);
      writemap(parent, UID, uidmap);

      if (outside) {
        if (setgid(getgid()) < 0 || setuid(getuid()) < 0)
          error(1, 0, "Failed to drop privileges");
        execlp(SHELL, SHELL, "-c", outside, NULL);
        error(1, errno, "exec %s", outside);
      }

      exit(EXIT_SUCCESS);
  }

  if (setgid(getgid()) < 0 || setuid(getuid()) < 0)
    error(1, 0, "Failed to drop privileges");

  if (unshare(CLONE_NEWIPC | CLONE_NEWNS | CLONE_NEWUSER | CLONE_NEWUTS) < 0)
    error(1, 0, "Failed to unshare namespaces");

  if (!hostnet && unshare(CLONE_NEWNET) < 0)
      error(1, 0, "Failed to unshare network namespace");

  waitforstop(child);
  kill(child, SIGCONT);
  waitforexit(child);

  setgid(0);
  setgroups(0, NULL);
  setuid(0);

  master = stdio ? -1 : getconsole();
  createroot(argv[optind], master, inside, bind);

  unshare(CLONE_NEWPID);
  switch (child = fork()) {
    case -1:
      error(1, errno, "fork");
    case 0:
      mountproc();
      if (!hostnet)
        mountsys();
      enterroot();

      if (master >= 0) {
        close(master);
        setconsole("/dev/console");
      }

      clearenv();
      putenv("container=contain");

      if (argv[optind + 1])
        execv(argv[optind + 1], argv + optind + 1);
      else
        execl(SHELL, SHELL, NULL);
      error(1, errno, "exec");
  }

  return supervise(child, master);
}