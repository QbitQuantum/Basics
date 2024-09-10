void armci_init_clusinfo()
{
  char name[MAX_HOSTNAME], *merged;
  int  len, limit, rc;
  char *tmp;
  char *enval;

  if((tmp =getenv("ARMCI_HOSTNAME")) == NULL){
    limit = MAX_HOSTNAME-1;
    rc = GETHOSTNAME(name, limit);
    if(rc < 0)armci_die("armci: gethostname failed",rc);
    tmp = new_hostname(name);
  }
  if(tmp != NULL){
      if(strlen(tmp) >= MAX_HOSTNAME)
                        armci_die("armci: hostname too long",strlen(tmp));
      strcpy(name,tmp);
      printf("%d using %s hostname\n",armci_me, name);
      fflush(stdout);
  }
  len =  strlen(name);
#ifdef ARMCI_ENABLE_GPC_CALLS
  /*a simple way to run as many servers as compute processes*/ 
  enval = getenv("ARMCI_NSERV_EQ_NPROC");
  if(enval != NULL){
    sprintf(name+len,"n%d",getpid());
    len =  strlen(name);
    printf("\n%s\n",name);
  }
#endif


#ifdef HOSTNAME_TRUNCATE
  {    
     /* in some cases (e.g.,SP) when name is used to determine
      * cluster structure but not to establish communication
      * we can truncate hostnames to save memory */
     int i;
     limit = HOSTNAME_LEN-1;
     for(i=0; i<len; i++){
         if(name[i] =='.')break; /*we are not truncating 1st part of hostname*/
         if(i==limit)armci_die("Please increase HOSTNAME_LEN in ARMCI >",i+1);
     }
     if(len>limit)name[limit]='\0';
     len =limit;
  }
#else
  if(len >= HOSTNAME_LEN-1)
     armci_die("armci: gethostname overrun name string length",len);
#endif

#ifdef NO_SHMEM
  if(armci_enable_alpha_hack()) {
    name[len]='0'+armci_me;
    name[len+1]='\0';
    len++;
  }
#endif
  
  if(DEBUG)
     fprintf(stderr,"%d: %s len=%d\n",armci_me, name,(int)strlen(name));

#ifdef CLUSTER
  merged = merge_names(name); /* create hostname list */
  process_hostlist(merged);        /* compute cluster info */
  free(merged);
#else
  process_hostlist(name);        /* compute cluster info */
#endif

  armci_master = armci_clus_info[armci_clus_me].master;

#ifdef NO_SHMEM
  if(armci_enable_alpha_hack()) {
     int i;
     for(i=0;i<armci_nclus;i++){
        int len=strlen(armci_clus_info[i].hostname);
        /*     fprintf(stderr,"----hostlen=%d\n",len);*/
        armci_clus_info[i].hostname[len-1]='\0';
     }
  }
#endif

  print_clus_info();

}