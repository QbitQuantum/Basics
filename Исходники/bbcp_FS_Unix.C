int bbcp_FS_Unix::Stat(const char *path, const char *dent, int fd,
                       int chklnks, bbcp_FileInfo *sbuff)
{
   struct stat xbuff;
   char lbuff[2048];
   int n;

// Perform the stat function
//
#ifdef AT_SYMLINK_NOFOLLOW
   if (fstatat(fd, dent, &xbuff, AT_SYMLINK_NOFOLLOW)) return -errno;
   if ((xbuff.st_mode & S_IFMT) != S_IFLNK)
      return (sbuff ? Stat(xbuff, sbuff) : 0);
   if (chklnks > 0) return -ENOENT;
   if (!sbuff) return 0;
   if ((n = READLINK(fd,dent,path,lbuff,sizeof(lbuff)-1)) < 0) return -errno;
// if ((n = readlinkat(fd, dent, lbuff, sizeof(lbuff)-1)) < 0) return -errno;
   lbuff[n] = 0;
   if(sbuff->SLink) free(sbuff->SLink);
   sbuff->SLink = strdup(lbuff);
   if (!chklnks && fstatat(fd, dent, &xbuff, 0)) return -errno;
   return Stat(xbuff, sbuff);
#else
   if (lstat(path, &xbuff)) return -errno;
   if ((xbuff.st_mode & S_IFMT) != S_IFLNK)
      return (sbuff ? Stat(xbuff, sbuff) : 0);
   if (chklnks > 0) return -ENOENT;
   if (!sbuff) return 0;
   if ((n = readlink(path, lbuff, sizeof(lbuff)-1)) < 0) return -errno;
   lbuff[n] = 0;
   if(sbuff->SLink) free(sbuff->SLink);
   sbuff->SLink = strdup(lbuff);
   if (!chklnks && stat(path, &xbuff)) return -errno;
   return Stat(xbuff, sbuff);
#endif
}