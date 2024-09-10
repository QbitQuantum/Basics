int
PollDB()
{
        FILE *fd;
        job_registry_entry *en;
	job_registry_handle *rha;
	job_registry_handle *rhc;
	char *buffer=NULL;
        char *cdate=NULL;
	time_t now;
        int  maxtok,i,maxtokl,j;
        char **tbuf;
        char **lbuf;
	int len=0,flen=0;
        struct stat sbuf;
        int rc;
	char *regfile;
        char *cp=NULL;
	int to_sleep=FALSE;
	int skip_reg_open=FALSE;
	int ret;

	rha=job_registry_init(registry_file, BY_BATCH_ID);
	if (rha == NULL){
		do_log(debuglogfile, debug, 1, "%s: Error initialising job registry %s\n",argv0,registry_file);
		fprintf(stderr,"%s: Error initialising job registry %s :",argv0,registry_file);
		perror("");
	}
	
	for(;;){
	
		now=time(NULL);
	
		to_sleep=TRUE;
		/* cycle over connections: sleep if startnotify, startnotifyjob and sentendonce are not set.
		   If startnotifyjob is set the conn is served.
		*/ 
		for(i=0; i<MAX_CONNECTIONS; i++){
		
			if(!connections[i].startnotify && !connections[i].startnotifyjob && !(connections[i].firstnotify && connections[i].sentendonce)) continue;
			if(connections[i].startnotify) to_sleep=FALSE;
			
			if(connections[i].startnotifyjob){
				to_sleep=FALSE;
				rhc=job_registry_init(registry_file, BY_USER_PREFIX);
				if (rhc == NULL){
					do_log(debuglogfile, debug, 1, "%s: Error initialising job registry %s\n",argv0,registry_file);
					fprintf(stderr,"%s: Error initialising job registry %s :",argv0,registry_file);
		 	   	  	perror("");
		 	   	}
		 	   	do_log(debuglogfile, debug, 2, "%s:Job list for notification:%s\n",argv0,connections[i].joblist_string);
		 	   	maxtok=strtoken(connections[i].joblist_string,',',&tbuf);
   		 	   	for(j=0;j<maxtok;j++){
        	 	   	  	if ((en=job_registry_get(rhc, tbuf[j])) != NULL){
						buffer=ComposeClassad(en);
		 	   	  	}else{
						if(remupd_conf == NULL){
		 	   	  			cdate=iepoch2str(now);
		 	   	  			maxtokl=strtoken(tbuf[j],'_',&lbuf);
		 	   	  			if(lbuf[1]){
		 	   	  				if ((cp = strrchr (lbuf[1], '\n')) != NULL){
		 	   	  					*cp = '\0';
		 	   	  				}
		 	   	  				if ((cp = strrchr (lbuf[1], '\r')) != NULL){
		 	   	  					*cp = '\0';
		 	   	  				}
		 	   	  				buffer=make_message("[BlahJobName=\"%s\"; ClientJobId=\"%s\"; JobStatus=4; JwExitCode=999; ExitReason=\"BUpdater is not able to find the job anymore\"; Reason=\"BUpdater is not able to find the job anymore\"; ChangeTime=\"%s\"; ]\n",tbuf[j],lbuf[1],cdate);
		 	   	  			}
		 	   	  			freetoken(&lbuf,maxtokl);
		 	   	  			free(cdate);
						}else{
		 	   	  			maxtokl=strtoken(tbuf[j],':',&lbuf);
							JOB_REGISTRY_ASSIGN_ENTRY(en->batch_id,lbuf[0]);
							JOB_REGISTRY_ASSIGN_ENTRY(en->blah_id,lbuf[1]);
		 	   	  			freetoken(&lbuf,maxtokl);
							en->status = 0;
							if ((ret=job_registry_append(rhc, en))<0){
								if(ret != JOB_REGISTRY_NOT_FOUND){
									fprintf(stderr,"Update of record returns %d: ",ret);
									perror("");
								}
							}else{
								if(ret==JOB_REGISTRY_SUCCESS){
									do_log(debuglogfile, debug, 2, "%s: registry append in PollDB for: jobid=%s blahjobid=%s\n",argv0,en->batch_id,en->blah_id);
								}
							}
						}
		 	   	  	}
		 	   	  	free(en);
		 	   	  	len=strlen(buffer);
		 	   	  	if(connections[i].finalbuffer != NULL){
		 	   	  		flen=strlen(connections[i].finalbuffer);
		 	   	  	}else{
		 	   	  		flen=0;
		 	   	  	}
		 	   	  	connections[i].finalbuffer = realloc(connections[i].finalbuffer,flen+len+2);
		 	   	  	if (connections[i].finalbuffer == NULL){
		 	   	  		sysfatal("can't realloc finalbuffer in PollDB: %r");
		 	   	  	}
		 	   	  	if(flen==0){
		 	   	  		connections[i].finalbuffer[0]='\000';
					}
		 	   	  	strcat(connections[i].finalbuffer,buffer);
		 	   	  	free(buffer);
		 	   	}
		 	   	freetoken(&tbuf,maxtok);
		 	   
		 	   	if(connections[i].finalbuffer != NULL){
		 	   	  	if(NotifyCream(connections[i].finalbuffer,&connections[i])!=-1){
	         	   	  		/* change last notification time */
		 	   	  		connections[i].lastnotiftime=now;
		 	   	  		connections[i].startnotifyjob=FALSE;
		 	   	  	}
		 	   	  	free(connections[i].finalbuffer);
		 	   	  	connections[i].finalbuffer=NULL;
		 	   	}
		 	   	job_registry_destroy(rhc);
			}
			if(connections[i].firstnotify && connections[i].sentendonce){
				to_sleep=FALSE;
				if(NotifyCream("NTFDATE/END\n",&connections[i])!=-1){
					connections[i].startnotify=TRUE;
					connections[i].sentendonce=FALSE;
		 	   	  	connections[i].firstnotify=FALSE;
		 	   	  	connections[i].startnotifyjob=FALSE;
				}
			}
			
		}
		
		if(to_sleep){
			sleep(loop_interval);
			continue;
		}

                regfile=make_message("%s/registry",registry_file);
        	rc=stat(regfile,&sbuf);
		free(regfile);
		
		skip_reg_open=TRUE;
		for(i=0; i<MAX_CONNECTIONS; i++){
			if(sbuf.st_mtime>=connections[i].lastnotiftime){
				skip_reg_open=FALSE;
				break;
			}
		}
		if(skip_reg_open){
			do_log(debuglogfile, debug, 3, "Skip registry opening: mtime:%d lastn:%d\n",sbuf.st_mtime,connections[i].lastnotiftime);
			sleep(loop_interval);
			continue;
		}
		
		do_log(debuglogfile, debug, 3, "Normal registry opening\n");

		fd = job_registry_open(rha, "r");
		if (fd == NULL)
		{
			do_log(debuglogfile, debug, 1, "%s: Error opening job registry %s\n",argv0,registry_file);
			fprintf(stderr,"%s: Error opening job registry %s :",argv0,registry_file);
			perror("");
			sleep(loop_interval);
			continue;
		}
		if (job_registry_rdlock(rha, fd) < 0)
		{
			do_log(debuglogfile, debug, 1, "%s: Error read locking registry %s\n",argv0,registry_file);
			fprintf(stderr,"%s: Error read locking registry %s :",argv0,registry_file);
			perror("");
			sleep(loop_interval);
			continue;
		}
		while ((en = job_registry_get_next(rha, fd)) != NULL)
		{
		
			for(i=0; i<MAX_CONNECTIONS; i++){
				if(connections[i].creamfilter==NULL) continue;
				if(en->mdate >= connections[i].lastnotiftime && en->mdate < now && en->user_prefix && strstr(en->user_prefix,connections[i].creamfilter)!=NULL && strlen(en->updater_info)>0)
				{
					buffer=ComposeClassad(en);
					len=strlen(buffer);
					if(connections[i].finalbuffer != NULL){
						flen=strlen(connections[i].finalbuffer);
					}else{
						flen=0;
					}
					connections[i].finalbuffer = realloc(connections[i].finalbuffer,flen+len+2);
					if (connections[i].finalbuffer == NULL){
						sysfatal("can't realloc finalbuffer in PollDB: %r");
					}
					if(flen==0){
						connections[i].finalbuffer[0]='\000';
					}
					strcat(connections[i].finalbuffer,buffer);
					free(buffer);
				}
			}
			free(en);
		}

		for(i=0; i<MAX_CONNECTIONS; i++){
			if(connections[i].finalbuffer != NULL){
				if(NotifyCream(connections[i].finalbuffer,&connections[i])!=-1){
	        			/* change last notification time */
					connections[i].lastnotiftime=now;
				}
				free(connections[i].finalbuffer);
				connections[i].finalbuffer=NULL;
			}
		}
		
		fclose(fd);
		
		sleep(loop_interval);
	}
                
	job_registry_destroy(rha);
	
	return 0;
}