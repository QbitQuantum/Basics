/* analyse a file system entry, referred by file name */
int filan_file(const char *filename, FILE *outfile) {
   int fd = -1;
   int result;
#if HAVE_STAT64
   struct stat64 buf = {0};
#else
   struct stat buf = {0};
#endif /* !HAVE_STAT64 */

   if (filan_followsymlinks) {
#if HAVE_STAT64
      result = Stat64(filename, &buf);
#else
      result = Stat(filename, &buf);
#endif /* !HAVE_STAT64 */
      if (result < 0) {
	 Warn3("stat(\"%s\", %p): %s", filename, &buf, strerror(errno));
      }
   } else {
#if HAVE_STAT64
      result = Lstat64(filename, &buf);
#else
      result = Lstat(filename, &buf);
#endif /* !HAVE_STAT64 */
      if (result < 0) {
	 Warn3("lstat(\"%s\", %p): %s", filename, &buf, strerror(errno));
      }
   }
   switch (buf.st_mode&S_IFMT) {
#ifdef S_IFSOCK
   case S_IFSOCK: /* probably, it's useless to make a socket and describe it */
      break;
#endif /* S_IFSOCK */
   default:
      if ((fd =
	   Open(filename,  O_RDONLY|O_NOCTTY|O_NONBLOCK
#ifdef O_LARGEFILE
		|O_LARGEFILE
#endif
		, 0700))
	  < 0) {
	 Warn2("open(\"%s\", O_RDONLY|O_NOCTTY|O_NONBLOCK|O_LARGEFILE, 0700): %s",
	       filename, strerror(errno));
      }
   }
     
   result = filan_stat(&buf, fd, -1, outfile);
   fputc('\n', outfile);
   return result;
}