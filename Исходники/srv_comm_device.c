static
LONG
CDECL
comm_open(FILEPTR * f)
{
  char deb[100];

  NOT_USED(f);


  /* Create and initialize internal file handle */
  FH(f) = (LONG)KMALLOC(sizeof(FileHandle));
  
  FH(f)->bytes_out = 0;
  FH(f)->selected = 0;
  FH(f)->queued = 0;

  SPRINTF(deb,
          "srv_comm_device: open: devinfo = 0x%lx, f = 0x%lx",
          f->devinfo,
          f);
  TRACE(deb);

  return 0;
}