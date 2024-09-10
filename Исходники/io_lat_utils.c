// -----------------------------------------------------------------
// Access from node0 only
int read_gauge_hdr(gauge_file *gf) {
  FILE *fp = gf->fp;
  gauge_header *gh = gf->header;
  int32type tmp, btmp;
  int j, stat, byterevflag = 0;
  char myname[] = "read_gauge_hdr";

  // Read header, do byte reversal, if necessary, and check consistency
  // Read and verify magic number
  stat = sread_data(fp, &gh->magic_number, sizeof(gh->magic_number),
                    myname, "magic number");
  if (stat != 0)
    terminate(1);

  tmp = gh->magic_number;
  btmp = gh->magic_number;
  byterevn((int32type *)&btmp, 1);

  /** See if header chunk is BEGI = 1111836489 for big endian
    or the byte reverse 1229407554 for little endian **/
  if (tmp == GAUGE_VERSION_NUMBER)
    byterevflag = 0;
  else if (btmp == GAUGE_VERSION_NUMBER) {
    byterevflag = 1;
    gh->magic_number = btmp;
//    printf("Reading with byte reversal\n");
    if (sizeof(float) != sizeof(int32type)) {
      printf("read_gauge_hdr: Can't byte reverse\n");
      printf("requires size of int32type(%d) = size of float(%d)\n",
             (int)sizeof(int32type), (int)sizeof(float));
      terminate(1);
    }
  }
  else if (tmp == LIME_MAGIC_NO || btmp == LIME_MAGIC_NO) {
    // LIME format suggests a SciDAC file
    // Print error, set flag and return
    printf("%s: Looks like a SciDAC-formatted file\n", myname);
    gh->magic_number = LIME_MAGIC_NO;
    return 0;
  }
  else {
    // End of the road
    printf("read_gauge_hdr: Unrecognized magic number in gauge header\n");
    printf("Expected %x but read %x\n", GAUGE_VERSION_NUMBER, tmp);
    printf("Expected %s but read %d\n", (char *)GAUGE_VERSION_NUMBER, tmp);
    terminate(1);
    return byterevflag;
  }

  // Read and process header information
  // Get lattice dimensions
  stat = sread_byteorder(byterevflag, fp, gh->dims, sizeof(gh->dims),
                         myname, "dimensions");
  if (stat != 0)
    terminate(1);

  // Check lattice dimensions for consistency
  if (gh->dims[0] != nx ||
      gh->dims[1] != ny ||
      gh->dims[2] != nz ||
      gh->dims[3] != nt) {
    /* So we can use this routine to discover the dimensions,
       we provide that if nx = ny = nz = nt = -1 initially
       we don't die */
    if (nx != -1 || ny != -1 || nz != -1 || nt != -1) {
      printf("%s: Incorrect lattice dimensions ",myname);
      for (j = 0; j < NDIMS; j++)
        printf("%d ", gh->dims[j]);
      printf("\n");
      fflush(stdout);
      terminate(1);
    }
    else {
      nx = gh->dims[0];
      ny = gh->dims[1];
      nz = gh->dims[2];
      nt = gh->dims[3];
      volume = nx * ny * nz * nt;
    }
  }
  // Read date and time stamp
  stat = sread_data(fp, gh->time_stamp, sizeof(gh->time_stamp),
                    myname, "time stamp");
  if (stat != 0)
    terminate(1);

  // Read header byte length
  gh->header_bytes = sizeof(gh->magic_number) + sizeof(gh->dims)
                   + sizeof(gh->time_stamp) + sizeof(gh->order);

  // Read data order
  stat = sread_byteorder(byterevflag, fp, &gh->order, sizeof(gh->order),
                         myname, "order parameter");
  if (stat != 0)
    terminate(1);

  return byterevflag;
}