 int main(int argc, char *argv[])
{
  FILE *f;
  pstring fname;
  int uid, c;
  static pstring servicesf = CONFIGFILE;
  extern char *optarg;
  int verbose = 0, brief =0;
  BOOL processes_only=False;
  int last_pid=0;
  struct session_record *ptr;


  TimeInit();
  setup_logging(argv[0],True);

  charset_initialise();

  DEBUGLEVEL = 0;
  dbf = fopen("/dev/null","w");

  if (getuid() != geteuid()) {
    printf("smbstatus should not be run setuid\n");
    return(1);
  }

  while ((c = getopt(argc, argv, "pds:u:b")) != EOF) {
    switch (c) {
    case 'b':
      brief = 1;
      break;
    case 'd':
      verbose = 1;
      break;
    case 'p':
      processes_only = 1;
      break;
    case 's':
      pstrcpy(servicesf, optarg);
      break;
    case 'u':                                       /* added by OH */
      Ucrit_addUsername(optarg);                    /* added by OH */
      break;
    default:
      fprintf(stderr, "Usage: %s [-d] [-p] [-s configfile] [-u username]\n", *argv); /* changed by OH */
      return (-1);
    }
  }

  get_myname(myhostname, NULL);

  if (!lp_load(servicesf,False)) {
    fprintf(stderr, "Can't load %s - run testparm to debug it\n", servicesf);
    return (-1);
  }

  if (verbose) {
    printf("using configfile = %s\n", servicesf);
    printf("lockdir = %s\n", *lp_lockdir() ? lp_lockdir() : "NULL");
  }

  pstrcpy(fname,lp_lockdir());
  standard_sub_basic(fname);
  trim_string(fname,"","/");
  pstrcat(fname,"/STATUS..LCK");

  f = fopen(fname,"r");
  if (!f) {
    printf("Couldn't open status file %s\n",fname);
    if (!lp_status(-1))
      printf("You need to have status=yes in your smb config file\n");
    return(0);
  }
  else if (verbose) {
    printf("Opened status file %s\n", fname);
  }

  uid = getuid();

  if (!processes_only) {
    printf("\nSamba version %s\n",VERSION);

    if (brief)
    {
      printf("PID     Username  Machine                       Time logged in\n");
      printf("-------------------------------------------------------------------\n");
    }
    else
    {
      printf("Service      uid      gid      pid     machine\n");
      printf("----------------------------------------------\n");
    }
  }

  while (!feof(f))
    {
      if (fread(&crec,sizeof(crec),1,f) != 1)
	break;
      if ( crec.magic == 0x280267 && process_exists(crec.pid) 
           && Ucrit_checkUsername(uidtoname(crec.uid))                      /* added by OH */
         )
      {
        if (brief)
        {
	  ptr=srecs;
	  while (ptr!=NULL)
	  {
	    if ((ptr->pid==crec.pid)&&(strncmp(ptr->machine,crec.machine,30)==0)) 
	    {
	      if (ptr->start > crec.start)
		ptr->start=crec.start;
	      break;
	    }
	    ptr=ptr->next;
	  }
	  if (ptr==NULL)
	  {
	    ptr=(struct session_record *) malloc(sizeof(struct session_record));
	    ptr->uid=crec.uid;
	    ptr->pid=crec.pid;
	    ptr->start=crec.start;
	    strncpy(ptr->machine,crec.machine,30);
	    ptr->machine[30]='\0';
	    ptr->next=srecs;
	    srecs=ptr;
	  }
        }
        else
        {
	  Ucrit_addPid(crec.pid);                                             /* added by OH */
	  if (processes_only) {
	    if (last_pid != crec.pid)
	      printf("%d\n",crec.pid);
	    last_pid = crec.pid; /* XXXX we can still get repeats, have to
				    add a sort at some time */
	  }
	  else	  
	    printf("%-10.10s   %-8s %-8s %5d   %-8s (%s) %s",
		   crec.name,uidtoname(crec.uid),gidtoname(crec.gid),crec.pid,
		   crec.machine,crec.addr,
		   asctime(LocalTime(&crec.start)));
        }
      }
    }
  fclose(f);

  if (processes_only) exit(0);
  
  if (brief)
  {
    ptr=srecs;
    while (ptr!=NULL)
    {
      printf("%-8d%-10.10s%-30.30s%s",ptr->pid,uidtoname(ptr->uid),ptr->machine,asctime(LocalTime(&(ptr->start))));
    ptr=ptr->next;
    }
    printf("\n");
    exit(0);
  }

  printf("\n");

  locking_init(1);

  if (share_mode_forall(print_share_mode) <= 0)
    printf("No locked files\n");

  printf("\n");

  share_status(stdout);

  locking_end();

  return (0);
}