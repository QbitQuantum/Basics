/**
 * @author Prof. A Olowofoyeku (The African Chief)
 * @author Frank Heckenbach
 * @see http://gd.tuwien.ac.at/gnu/mingw/os-hacks.h
 */
int statfs(const char *path, struct statfs *buf)
{
  HINSTANCE h;
  FARPROC f;
  char tmp[MAX_PATH], resolved_path[MAX_PATH];
  int retval = 0;

  errno = 0;

  realpath(path, resolved_path);
  if(!resolved_path)
    retval = -1;
  else
  {
    /* check whether GetDiskFreeSpaceExA is supported */
    h = LoadLibraryA("kernel32.dll");
    if(h)
      f = GetProcAddress(h, "GetDiskFreeSpaceExA");
    else
      f = NULL;
    if(f)
    {
      ULARGE_INTEGER bytes_free, bytes_total, bytes_free2;
      if(!f(resolved_path, &bytes_free2, &bytes_total, &bytes_free))
      {
        errno = ENOENT;
        retval = -1;
      }
      else
      {
        buf->f_bsize = FAKED_BLOCK_SIZE;
        buf->f_bfree = (bytes_free.QuadPart) / FAKED_BLOCK_SIZE;
        buf->f_files = buf->f_blocks =
          (bytes_total.QuadPart) / FAKED_BLOCK_SIZE;
        buf->f_ffree = buf->f_bavail =
          (bytes_free2.QuadPart) / FAKED_BLOCK_SIZE;
      }
    }
    else
    {
      DWORD sectors_per_cluster, bytes_per_sector;
      if(h)
        FreeLibrary(h);
      if(!GetDiskFreeSpaceA(resolved_path, &sectors_per_cluster,
                            &bytes_per_sector, &buf->f_bavail,
                            &buf->f_blocks))
      {
        errno = ENOENT;
        retval = -1;
      }
      else
      {
        buf->f_bsize = sectors_per_cluster * bytes_per_sector;
        buf->f_files = buf->f_blocks;
        buf->f_ffree = buf->f_bavail;
        buf->f_bfree = buf->f_bavail;
      }
    }
    if(h)
      FreeLibrary(h);
  }

  /* get the FS volume information */
  if(strspn(":", resolved_path) > 0)
    resolved_path[3] = '\0';    /* we want only the root */
  if(GetVolumeInformation
     (resolved_path, NULL, 0, &buf->f_fsid, &buf->f_namelen, NULL, tmp,
      MAX_PATH))
  {
    if(strcasecmp("NTFS", tmp) == 0)
    {
      buf->f_type = NTFS_SUPER_MAGIC;
    }
    else
    {
      buf->f_type = MSDOS_SUPER_MAGIC;
    }
  }
  else
  {
    errno = ENOENT;
    retval = -1;
  }
  return retval;
}