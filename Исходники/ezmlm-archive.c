int main(int argc,char **argv)
{
  unsigned long max;
  int fd;
  int fdlock;
  msgentry *msgtable;
  subentry *subtable;
  authentry *authtable;
  dateentry *datetable;

  (void) umask(022);
  sig_pipeignore();

  getconfopt(argc,argv,options,1,0);
  if (flagsyncall)
    flagsync = 1;
  else if (flagcreate)
    flagsync = 0;
  archnum = (archnum / 100) * 100;

	/* Lock list to assure that no ezmlm-send is working on it */
	/* and that the "num" message is final */
  fdlock = lockfile("lock");
					/* get num */
  if (!getconf_ulong(&max,"num",0)
      || max == 0)
    strerr_die1x(100,MSG(ERR_EMPTY_LIST));
  (void) close(fdlock);

  if (!optto || optto > max) optto = max;

  fdlock = lockfile("archive/lock");	/* lock index */
  if (!flagcreate && !archnum) {	/* adjust archnum (from) / to */
    if (getconf_ulong(&archnum,"archnum",0))
      ++archnum;
    else
      archnum = 0;
  }

  if (archnum > optto)
    _exit(0);				/* nothing to do */

  if (mkdir("archive/threads",0755) == -1)
    if (errno != error_exist)
      strerr_die2sys(111,FATAL,MSG1(ERR_CREATE,"archive/threads"));
  if (mkdir("archive/subjects",0755) == -1)
    if (errno != error_exist)
      strerr_die2sys(111,FATAL,MSG1(ERR_CREATE,"archive/subjects"));
  if (mkdir("archive/authors",0755) == -1)
    if (errno != error_exist)
      strerr_die2sys(111,FATAL,MSG1(ERR_CREATE,"archive/authors"));

					/* do the subject threading */
  idx_mkthreads(&msgtable,&subtable,&authtable,&datetable,archnum,optto,max,0);
					/* update the index */
  write_threads(msgtable,subtable,authtable,datetable,archnum,optto);
					/* update archnum */
  if ((fd = open_trunc("archnumn")) == -1)
    strerr_die2sys(111,FATAL,MSG1(ERR_CREATE,"archnumn"));
  substdio_fdbuf(&ssnum,write,fd,numbuf,sizeof(numbuf));
  if (substdio_put(&ssnum,strnum,fmt_ulong(strnum,optto)) == -1)
     strerr_die2sys(111,FATAL,MSG1(ERR_WRITE,fnn.s));
  if (substdio_puts(&ssnum,"\n") == -1)
     strerr_die2sys(111,FATAL,MSG1(ERR_WRITE,fnn.s));
  close_proper(&ssnum,"archnum","archnumn");
  switch (flagerror) {
    case 0:
       _exit(0);				/* go bye-bye */
    case -1:
       strerr_die2x(99,WARNING,"threads entry with illegal format");
    case -2:
       strerr_die2x(99,WARNING,"thread in index, but threadfile missing");
    case -3:
       strerr_die2x(99,WARNING,"a subject file lacks subject");
    case -4:
       strerr_die2x(99,WARNING,"an author file lacks author/hash");
    case -5:
       strerr_die2x(99,WARNING,"threads entry lacks message count");
    default:
       strerr_die2x(99,WARNING,"something happened that isn't quite right");
  }
}