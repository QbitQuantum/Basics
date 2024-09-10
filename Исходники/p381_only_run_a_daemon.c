int already_running(void)
{
     int        fd = 0;
     char       buf[16] = {0};

     fd = open(LOCKFILE, O_RDWR | O_CREAT, LOCKMODE);
     if (fd < 0)
     {
         syslog(LOG_ERR, "can't open %s: %s", LOCKFILE, strerror(errno));
         exit(1);
     }

     if (lockfile(fd) < 0)
     {
          //??????
          if (errno == EACCES || errno == EAGAIN)
          {
              syslog(LOG_ERR, "daemon is already_running");
              close(fd);
              return 1;
          }

          syslog(LOG_ERR, "can't lock %s: %s", LOCKFILE, strerror(errno));
          exit(1);
     }

     ftruncate(fd, 0);      //???P90
     sprintf(buf, "%ld", (long)getpid());
     write(fd, buf, strlen(buf) + 1);
     syslog(LOG_ERR, "write /var/run/daemon.pid: %s", buf);

     return 0;
}