int main(int argc,char *argv[])
{
  int fd;
  int match;
  unsigned long msgsize = 0L;
  int opt;

  opt = getconfopt(argc,argv,options,1,0);
  if (argc - opt != 1)
    die_usage();

  if ((fd = open_read(argv[opt])) == -1)
    strerr_die2sys(111,FATAL,MSG1(ERR_OPEN,argv[opt]));
  substdio_fdbuf(&ssin,read,fd,inputbuf,sizeof inputbuf);

  lockfile("lock");

  getconf_ulong2(&msgnum,&cumsize,"num",0);
  
  fd = 0;
  while (getln(&ssin,&line,&match,'\n') == 0 && match) {
    if (line.len > 5
	&& byte_diff(line.s,5,"From ") == 0) {
      if (fd > 0) {
	if (substdio_flush(&ssarchive) == -1
	    || fchmod(fd,MODE_ARCHIVE|0700) == -1
	    || close(fd) == -1)
	  strerr_die2sys(111,FATAL,MSG1(ERR_WRITE,fnaf.s));
	fd = 0;
      }
      ++msgnum;
      cumsize += (msgsize + 128L) >> 8;
      msgsize = 0L;
      fd = openone(msgnum);
    }
    else if (fd > 0) {
      substdio_put(&ssarchive,line.s,line.len);
      msgsize += line.len;
    }
  }