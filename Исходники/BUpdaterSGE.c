int main(int argc, char *argv[]){
    
    FILE *fd;
    job_registry_entry *en;
    time_t now;
    time_t purge_time=0;
    char constraint[JOBID_MAX_LEN+1];
    char constraint2[5];
    char *query=NULL;
    char *queryStates=NULL;
    char *query_err=NULL;

    char *pidfile=NULL;
    char string_now[11];
    char *tpath;
    
    int version=0;
    int tmptim;
    int finstr_len=0;
    int loop_interval=DEFAULT_LOOP_INTERVAL;
    
    int fsq_ret=0;
    
    int c;
    
    int confirm_time=0;
    
    static int help;
    static int short_help;
    
    while (1) {
	static struct option long_options[] =
	{
	    {"help",      no_argument,     &help,       1},
	    {"usage",     no_argument,     &short_help, 1},
	    {"nodaemon",  no_argument,       0, 'o'},
	    {"version",   no_argument,       0, 'v'},
	    {0, 0, 0, 0}
	};
	
	int option_index = 0;
	
	c = getopt_long (argc, argv, "vo",long_options, &option_index);
	
	if (c == -1){
	    break;
	}
	
	switch (c)
	{
	    
	    case 0:
		if (long_options[option_index].flag != 0){
		    break;
		}
		
	    case 'v':
		version=1;
		break;
		
	    case 'o':
		nodmn=1;
		break;
		
	    case '?':
		break;
		
	    default:
		abort ();
	}
    }
    
    //check if another instance is running 
    char **ptr;
    char out[3];
    fgets(out, sizeof(out),popen("ps -d | grep -c BUpdaterSGE","r"));
    strtoken(out,'\n',&ptr);
    if (strcmp(ptr[0],"1")!=0){
	fprintf(stderr,"There is another instance of BUpdaterSGE running.\nExiting ...\n");
	return -1;
    }
    freetoken(&ptr,1);

    if(help){
	usage();
    }
    
    if(short_help){
	short_usage();
    }
    
    argv0 = argv[0];
    
    signal(SIGHUP,sighup);
    
    if(version) {
	printf("%s Version: %s\n",progname,VERSION);
	exit(EXIT_SUCCESS);
    }  
    
    /* Checking configuration */
    check_config_file("UPDATER"); 
    
    cha = config_read(NULL);
    if (cha == NULL)
    {
	fprintf(stderr,"Error reading config: ");
	perror("");
	return -1;
    }
    config_setenv(NULL);
    
    ret = config_get("bupdater_child_poll_timeout",cha);
    if (ret != NULL){
	tmptim=atoi(ret->value);
	if (tmptim > 0) bfunctions_poll_timeout = tmptim*1000;
    }
    
    ret = config_get("bupdater_debug_level",cha);
    if (ret != NULL){
	debug=atoi(ret->value);
    }
    
    ret = config_get("bupdater_debug_logfile",cha);
    if (ret != NULL){
	debuglogname=strdup(ret->value);
	if(debuglogname == NULL){
	    sysfatal("strdup failed for debuglogname in main: %r");
	}
    }
    if(debug <=0){
	debug=0;
    }
    
    if(debuglogname){
	if((debuglogfile = fopen(debuglogname, "a+"))==0){
	    debug = 0;
	}
    }else{
	debug = 0;
    }

    ret = config_get("debug_level",cha);
    if (ret != NULL){
	debug=atoi(ret->value);
    }

    ret = config_get("debug_logfile",cha);
    if (ret != NULL){
	debuglogname=strdup(ret->value);
	if(debuglogname == NULL){
	    sysfatal("strdup failed for debuglogname in main: %r");
	}
    }
    if(debug <=0){
	debug=0;
    }

    if(debuglogname){
	if((debuglogfile = fopen(debuglogname, "a+"))==0){
	    debug = 0;
	}
    }else{
	debug = 0;
    }

    ret = config_get("sge_binpath",cha);
    if (ret == NULL){
	do_log(debuglogfile, debug, 1, "%s: key sge_binpath not found\n",argv0);
    } else {
	sge_binpath=strdup(ret->value);
	if(sge_binpath == NULL){
	    sysfatal("strdup failed for sge_binpath in main: %r");
	}
    }

    ret = config_get("sge_rootpath",cha);
    if (ret == NULL){
	do_log(debuglogfile, debug, 1, "%s: key sge_rootpath not found\n",argv0);
    } else {
	sge_rootpath=strdup(ret->value);
	if(sge_rootpath == NULL){
	    sysfatal("strdup failed for sge_rootpath in main: %r");
	}
	
	tpath=make_message("%s",sge_rootpath);
	if (opendir(tpath)==NULL){
	    do_log(debuglogfile, debug, 1, "%s: dir %s does not exist or is not readable\n",argv0,tpath);
	    sysfatal("dir %s does not exist or is not readable: %r",tpath);
	}
	free(tpath);
    }

    ret = config_get("sge_cellname",cha);
    if (ret == NULL){
	do_log(debuglogfile, debug, 1, "%s: key sge_cellname not found\n",argv0);
    } else {
	sge_cellname=strdup(ret->value);
	if(sge_cellname == NULL){
	    sysfatal("strdup failed for sge_cellname in main: %r");
	}
    }

    ret = config_get("sge_rootpath",cha);
    if (ret == NULL){
	if(debug){
	    fprintf(debuglogfile, "%s: key sge_rootpath not found\n",argv0);
	    fflush(debuglogfile);
	}
    } else {
	sge_rootpath=strdup(ret->value);
	if(sge_rootpath == NULL){
	    sysfatal("strdup failed for sge_rootpath in main: %r");
	}
    }

    ret = config_get("sge_cellname",cha);
    if (ret == NULL){
	if(debug){
	    fprintf(debuglogfile, "%s: key sge_cellname not found\n",argv0);
	    fflush(debuglogfile);
	}
    } else {
	sge_cellname=strdup(ret->value);
	if(sge_cellname == NULL){
	    sysfatal("strdup failed for sge_cellname in main: %r");
	}
    }

    ret = config_get("job_registry",cha);
    if (ret == NULL){
	do_log(debuglogfile, debug, 1, "%s: key job_registry not found\n",argv0);
	sysfatal("job_registry not defined. Exiting");
    } else {
	reg_file=strdup(ret->value);
	if(reg_file == NULL){
	    sysfatal("strdup failed for reg_file in main: %r");
	}
    }

    ret = config_get("purge_interval",cha);
    if (ret == NULL){
	do_log(debuglogfile, debug, 1, "%s: key purge_interval not found using the default:%d\n",argv0,purge_interval);
    } else {
	purge_interval=atoi(ret->value);
    }

    ret = config_get("finalstate_query_interval",cha);
    if (ret == NULL){
	do_log(debuglogfile, debug, 1, "%s: key finalstate_query_interval not found using the default:%d\n",argv0,finalstate_query_interval);
    } else {
	finalstate_query_interval=atoi(ret->value);
    }

    ret = config_get("alldone_interval",cha);
    if (ret == NULL){
	do_log(debuglogfile, debug, 1, "%s: key alldone_interval not found using the default:%d\n",argv0,alldone_interval);
    } else {
	alldone_interval=atoi(ret->value);
    }

    ret = config_get("bupdater_loop_interval",cha);
    if (ret == NULL){
	do_log(debuglogfile, debug, 1, "%s: key bupdater_loop_interval not found using the default:%d\n",argv0,loop_interval);
    } else {
	loop_interval=atoi(ret->value);
    }

    ret = config_get("bupdater_pidfile",cha);
    if (ret == NULL){
	do_log(debuglogfile, debug, 1, "%s: key bupdater_pidfile not found\n",argv0);
    } else {
	pidfile=strdup(ret->value);
	if(pidfile == NULL){
	    sysfatal("strdup failed for pidfile in main: %r");
	}
    }

    ret = config_get("job_registry_use_mmap",cha);
    if (ret == NULL){
        do_log(debuglogfile, debug, 1, "%s: key job_registry_use_mmap not found. Default is NO\n",argv0);
    } else {
        do_log(debuglogfile, debug, 1, "%s: key job_registry_use_mmap is set to %s\n",argv0,ret->value);
    }

    if( !nodmn ) daemonize();

    if( pidfile ){
	writepid(pidfile);
	free(pidfile);
    }

    config_free(cha);
    rha=job_registry_init(reg_file, BY_BATCH_ID);
    if (rha == NULL){
	do_log(debuglogfile, debug, 1, "%s: Error initialising job registry %s\n",argv0,reg_file);
	fprintf(stderr,"%s: Error initialising job registry %s :",argv0,reg_file);
	perror("");
    }
   for(;;){
	/* Purge old entries from registry */
	now=time(0);
	if(now - purge_time > 86400){
	    if(job_registry_purge(reg_file, now-purge_interval,0)<0){
		do_log(debuglogfile, debug, 1, "%s: Error purging job registry %s\n",argv0,reg_file);
		fprintf(stderr,"%s: Error purging job registry %s :",argv0,reg_file);
		perror("");
	    }else{
		purge_time=time(0);
	    }
	}
	
	//IntStateQuery();
	fd = job_registry_open(rha, "r");
	if (fd == NULL)
	{
	    do_log(debuglogfile, debug, 1, "%s: Error opening job registry %s\n",argv0,reg_file);
	    fprintf(stderr,"%s: Error opening job registry %s :",argv0,reg_file);
	    perror("");
	    sleep(loop_interval);
	}
	if (job_registry_rdlock(rha, fd) < 0)
	{
	    do_log(debuglogfile, debug, 1, "%s: Error read locking job registry %s\n",argv0,reg_file);
	    fprintf(stderr,"%s: Error read locking job registry %s :",argv0,reg_file);
	    perror("");
	    sleep(loop_interval);
	}
	job_registry_firstrec(rha,fd);
	fseek(fd,0L,SEEK_SET);

	if((query=calloc(STR_CHARS*2,1)) == 0){
	    sysfatal("can't malloc query %r");
	}
	if((queryStates=calloc(STR_CHARS*2,1)) == 0){
	    sysfatal("can't malloc query %r");
	}
	
	query[0]=' ';
	queryStates[0]=' ';
	while ((en = job_registry_get_next(rha, fd)) != NULL)
	{
	    if(((now - en->mdate) > finalstate_query_interval) && en->status!=3 && en->status!=4)
	    {
		/* create the constraint that will be used in condor_history command in FinalStateQuery*/
		snprintf(constraint, sizeof(constraint), " %s",en->batch_id);
		if (en->status==0) snprintf(constraint2, sizeof(constraint2), " u");
		if (en->status==1) snprintf(constraint2, sizeof(constraint2), " q");
		if (en->status==2) snprintf(constraint2, sizeof(constraint2), " r");
		if (en->status==5) snprintf(constraint2, sizeof(constraint2), " h");
		query=realloc(query,strlen(query)+strlen(constraint)+1);
		queryStates=realloc(queryStates,strlen(queryStates)+strlen(constraint2)+1);
		strcat(query,constraint);
		strcat(queryStates,constraint2);
		runfinal=TRUE;
	    }
	    /* Assign Status=4 and ExitStatus=-1 to all entries that after alldone_interval are still not in a final state(3 or 4) */
	    if((now - en->mdate > alldone_interval) && en->status!=3 && en->status!=4 && !runfinal)
	    {
		time_t now;
		now=time(0);
		snprintf(string_now,sizeof(string_now),"%d",now);
		AssignState(en->batch_id,"4" ,"-1","\0","\0",string_now);
	    }
	   free(en);
	}
	if(runfinal){
	    if((query_err=calloc((int)strlen(query),1)) == 0)
		sysfatal("can't malloc query_err %r");
	    FinalStateQuery(query,queryStates,query_err);
	    free(query_err);
	}
	free(query);
	free(queryStates);
	fclose(fd);
	if (runfinal){
	    runfinal=FALSE;
	}
	sleep (loop_interval);
    } //for

    job_registry_destroy(rha);
    return(0);
}