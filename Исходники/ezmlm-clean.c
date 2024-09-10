void main(int argc,char **argv)
{
  int fdlock;
  unsigned long delay;
  (void) umask(022);
  sig_pipeignore();
  when = now();

  getconfopt(argc,argv,options,1,0);
  if (flagreturn < 0)
    /* default to returning timed-out messages */
    flagreturn = !getconf_isset("noreturnposts");

  getconf_line(&modtime,"modtime",0);
  if (!stralloc_0(&modtime)) die_nomem();
  scan_ulong(modtime.s,&delay);
  if (!delay) delay = DELAY_DEFAULT;
  else if (delay < DELAY_MIN) delay = DELAY_MIN;
  else if (delay > DELAY_MAX) delay = DELAY_MAX;
  older = (unsigned long) when - 3600L * delay;	/* delay is in hours */

  fdlock = lockfile("mod/lock");

  dodir("mod/pending/",flagreturn);
  dodir("mod/accepted/",0);
  dodir("mod/rejected/",0);
  dodir("mod/unconfirmed/",0);
  _exit(0);
}