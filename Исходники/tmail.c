int main (int argc,char *argv[])
{
  FILE *f = NIL;
  int pid,c,ret = 0;
  unsigned long msglen,status = 0;
  char *s,tmp[MAILTMPLEN];
  uid_t ruid = getuid ();
  struct passwd *pwd;
  openlog ("tmail",LOG_PID,LOG_MAIL);
#include "linkage.c"
				/* make sure have some arguments */
  if (--argc < 1) _exit (fail ("usage: tmail [-D] user[+folder]",EX_USAGE));
				/* process all flags */
  while (argc && (*(s = *++argv)) == '-') {
    argc--;			/* gobble this argument */
    switch (s[1]) {		/* what is this flag? */
    case 'D':			/* debug */
      debug = T;		/* don't fork */
      break;
    case 'd':			/* obsolete flag meaning multiple users */
      break;
    case 'I':			/* inbox specifier */
      if (argc--) inbox = cpystr (*++argv);
      else _exit (fail ("missing argument to -I",EX_USAGE));
      break;
    case 'f':			/* new name for this flag */
    case 'r':			/* flag giving return path */
      if (argc--) sender = cpystr (*++argv);
      else _exit (fail ("missing argument to -r",EX_USAGE));
      break;
    default:			/* anything else */
      _exit (fail ("unknown switch",EX_USAGE));
    }
  }

  if (!argc) ret = fail ("no recipients",EX_USAGE);
  else if (!(f = tmpfile ())) ret = fail ("can't make temp file",EX_TEMPFAIL);
  else {			/* build delivery headers */
    if (sender) fprintf (f,"Return-Path: <%s>\015\012",sender);
				/* start Received line: */
    fprintf (f,"Received: via tmail-%s",version);
				/* not root or daemon? */
    if (ruid && !((pwd = getpwnam ("daemon")) && (ruid == pwd->pw_uid))) {
      pwd = getpwuid (ruid);	/* get unprivileged user's information */
      if (inbox) {
	if (pwd) sprintf (tmp,"user %.80s",pwd->pw_name);
	else sprintf (tmp,"UID %ld",(long) ruid);
	strcat (tmp," is not privileged to use -I");
	_exit (fail (tmp,EX_USAGE));
      }
      fputs (" (invoked by ",f);
      if (pwd) fprintf (f,"user %s",pwd->pw_name);
      else fprintf (f,"UID %ld",(long) ruid);
      fputs (")",f);
    }
				/* write "for" if single recipient */
    if (argc == 1) fprintf (f," for %s",*argv);
    fputs ("; ",f);
    rfc822_date (tmp);
    fputs (tmp,f);
    fputs ("\015\012",f);
				/* copy text from standard input */
    if (!fgets (tmp,MAILTMPLEN-1,stdin) || !(s = strchr (tmp,'\n')) ||
	(s == tmp) || s[1]) _exit (fail ("bad first message line",EX_USAGE));
    if (s[-1] == '\015') {	/* nuke leading "From " line */
      if ((tmp[0] != 'F') || (tmp[1] != 'r') || (tmp[2] != 'o') ||
	  (tmp[3] != 'm') || (tmp[4] != ' ')) fputs (tmp,f);
      while ((c = getchar ()) != EOF) putc (c,f);
    }
    else {
      mm_log ("tmail called with LF-only newlines",WARN);
      if ((tmp[0] != 'F') || (tmp[1] != 'r') || (tmp[2] != 'o') ||
	  (tmp[3] != 'm') || (tmp[4] != ' ')) {
	*s++ = '\015';		/* overwrite NL with CRLF */
	*s++ = '\012';
	*s = '\0';		/* tie off string */
	fputs (tmp,f);		/* write line */
      }
				/* copy text from standard input */
      while ((c = getchar ()) != EOF) {
				/* add CR if needed */
	if (c == '\012') putc ('\015',f);
	putc (c,f);
      }
    }
    msglen = ftell (f);		/* size of message */
    fflush (f);			/* make sure all changes written out */

    if (ferror (f)) ret = fail ("error writing temp file",EX_TEMPFAIL);
    else if (!msglen) ret = fail ("empty message",EX_TEMPFAIL);
				/* single delivery */
    else if (argc == 1) ret = deliver (f,msglen,*argv);
    else do {			/* multiple delivery uses daughter forks */
      if ((pid = fork ()) < 0) ret = fail (strerror (errno),EX_OSERR);
      else if (pid) {		/* mother process */
	grim_pid_reap_status (pid,NIL,(void *) status);
				/* normal termination? */
	if (!ret) ret = (status & 0xff) ? EX_SOFTWARE : (status & 0xff00) >> 8;
      }
				/* daughter process */
      else _exit (deliver (f,msglen,*argv));
    } while (--argc && *argv++);
    mm_dlog (ret ? "error in delivery" : "all recipients delivered");
  }