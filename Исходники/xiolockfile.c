/* returns 0 if it could create lock; 1 if the lock exists; -1 on error */
int xiogetlock(const char *lockfile) {
   char *s;
   struct stat strat;
   int fd;
   pid_t pid;
   char pidbuf[3*sizeof(pid_t)+1];
   size_t bytes;

   if (Lstat(lockfile, &strat) == 0) {
      return 1;
   }
   switch (errno) {
   case ENOENT: break;
   default:
      Error3("Lstat(\"%s\", %p): %s", lockfile, &strat, strerror(errno));
      return -1;
   }
   /* in this moment, the file did not exist */

   if ((s = Malloc(strlen(lockfile)+8)) == NULL) {
      errno = ENOMEM;
      return -1;
   }
   strcpy(s, lockfile);
   strcat(s, ".XXXXXX");

   if ((fd = Mkstemp(s)) < 0) {
      Error2("mkstemp(\"%s\"): %s", s, strerror(errno));
      return -1;
   }
  
   pid = Getpid();
   bytes = sprintf(pidbuf, F_pid, pid);
   if (writefull(fd, pidbuf, bytes) < 0) {
      Error4("write(%d, %p, "F_Zu"): %s", fd, pidbuf, bytes, strerror(errno));
      return -1;
   }
   Close(fd);

   /* Chmod(lockfile, 0600); */
   if (Link(s, lockfile) < 0) {
      int _errno = errno;
      Error3("link(\"%s\", \"%s\"): %s", s, lockfile, strerror(errno));
      Unlink(s);
      errno = _errno;
      return -1;
   }
   Unlink(s);

   return 0;
}