int tStatFile()
{
  int fd, retW, retS;
  char buffer[11];
  struct VFS_File_Stat s;

  fd = Open("/d/basic9f", O_CREATE|O_WRITE);
  if (fd < 0)
    return -1;

  retW = Write( fd, buffer, 10);
  if (retW < 0)
    return -1;

  Close(fd);

  retS = Stat("/d/basic9f", &s);

  Delete("/d/basic9f");

  return ( (retS >= 0) && (s.size == 10) ) ? 1 : -1;
}