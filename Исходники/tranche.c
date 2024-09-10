int main(int argc, char *argv[])
{
  int i,n;
  int opt, r=0, fuse_ret=0;
  int tmp_mntpoint=0;

  //FILE *tranche_ofp = stdout;

  char **fuse_args;
  int persist_flag = 0;

  tranche_ofp = stdout;

  fuse_args = (char **)malloc(sizeof(char*)*3);
  fuse_args[0] = strdup(argv[0]);
  fuse_args[1] = NULL;
  fuse_args[2] = strdup("-f");

  tranche_start = 0;
  tranche_size = -1;
  tranche_mountpoint=NULL;
  tranche_exposed_fn=NULL;
  tranche_ifn=NULL;
  tranche_ifd=-1;

  memset(&tranche_stbuf, 0, sizeof(struct stat));

  while ((opt=getopt(argc, argv, "b:s:f:m:qhpD"))!=-1) switch(opt) {
    case 'b':
      tranche_start = atoi(optarg);
      break;
    case 's':
      tranche_size = atoi(optarg);
      break;
    case 'f':
      tranche_ifn = strdup(optarg);
      break;
    case 'm':
      tranche_mountpoint = strdup(optarg);
      break;
    case 'q':
      quiet_flag = 1;
      break;
    case 'h':
      help_flag = 1;
      break;
    case 'p':
      persist_flag = 1;
      break;
    case 'D':
      g_debug = 1;
      break;
    default:
      break;
  }

  if (help_flag) {
    show_help();
    exit(1);
  }

  if (!tranche_ifn) {
    fprintf(stderr, "Provide input filename (-f)\n");
    show_help();
    exit(1);
  }

  // Create mount point and construct exposed filename
  //
  if (!tranche_mountpoint) {
    tranche_mountpoint = strdup("/tmp/tranchemntXXXXXX");
    mkdtemp(tranche_mountpoint);
    tmp_mntpoint=1;
  }
  tranche_exposed_fn = tempnam(tranche_mountpoint, NULL);
  fuse_args[1] = strdup(tranche_mountpoint);

  // Open the underlying file and get stats for it
  //
  tranche_ifd = open(tranche_ifn, O_RDONLY);
  if (tranche_ifd<0) {
    perror("error: ");
    exit(errno);
  }



  r = fstat(tranche_ifd, &tranche_stbuf);
  if (r<0) {
    perror("error:");
    return r;
  }

  if ((tranche_size<0) || ((tranche_stbuf.st_size-tranche_start) < tranche_size)) {
    tranche_size = tranche_stbuf.st_size-tranche_start;
  }
  if (tranche_size<=0) { tranche_size=0; }

  n = strlen(tranche_exposed_fn);
  for (i=n-1; i>=0; i--) {
    if (tranche_exposed_fn[i]=='/') { break; }
  }
  if (i<0) { i=0; }
  tranche_mount_path = strdup(tranche_exposed_fn+i);

  // Start fuse server.
  //
  // The fuse server is running in the foreground (the '-f'
  // option in fuse_args) and will block until it's done.
  //
  fuse_ret = fuse_main(2+persist_flag, fuse_args, &tranche_oper, NULL);

  // Fuse serverhas been stopped, close our underlying file
  //
  close(tranche_ifd);

  // Cleanup the mount point
  //
  if (tmp_mntpoint) {
    r = rmdir(tranche_mountpoint);
    if (r<0) { perror(""); }
  }

  free(fuse_args[0]);
  free(fuse_args[1]);
  free(fuse_args[2]);
  free(fuse_args);

  free(tranche_ifn);
  free(tranche_mountpoint);

  return fuse_ret;
}