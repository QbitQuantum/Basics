int
IntStateQuery()
{

        FILE *fp;
	char *line=NULL;
	char **token;
	char **token_l;
	char **token_e;
	int maxtok_t=0;
	int maxtok_l=0;
	int maxtok_e=0;
	job_registry_entry en;
	int ret;
	time_t tmstampepoch;
	char *cp=NULL; 
	char *batch_str=NULL;
	char *command_string=NULL;
	job_registry_entry *ren=NULL;
	int isresumed=FALSE;
	int first=TRUE;
	time_t now;
	char *string_now=NULL;

	command_string=make_message("%s/scontrol -a show jobid",slurm_binpath);
	fp = popen(command_string,"r");

	en.status=UNDEFINED;
	JOB_REGISTRY_ASSIGN_ENTRY(en.wn_addr,"\0");
	JOB_REGISTRY_ASSIGN_ENTRY(en.exitreason,"\0");
	JOB_REGISTRY_ASSIGN_ENTRY(en.updater_info,"\0");
	en.exitcode=-1;
	bupdater_free_active_jobs(&bact);

	if(fp!=NULL){
		while(!feof(fp) && (line=get_line(fp))){
			if(line && strlen(line)==0){
				free(line);
				continue;
			}
			if ((cp = strrchr (line, '\n')) != NULL){
				*cp = '\0';
			}
			do_log(debuglogfile, debug, 3, "%s: line in IntStateQuery is:%s\n",argv0,line);
			now=time(0);
			string_now=make_message("%d",now);
			maxtok_t = strtoken(line, ' ', &token);
			if(line && strstr(line,"JobId=")){
				isresumed=FALSE;
				if(!first && en.status!=UNDEFINED && ren && ren->status!=REMOVED && ren->status!=COMPLETED){	
					if ((ret=job_registry_update_recn_select(rha, &en, ren->recnum,
					JOB_REGISTRY_UPDATE_WN_ADDR|
					JOB_REGISTRY_UPDATE_STATUS|
					JOB_REGISTRY_UPDATE_UDATE|
					JOB_REGISTRY_UPDATE_UPDATER_INFO|
					JOB_REGISTRY_UPDATE_EXITCODE|
					JOB_REGISTRY_UPDATE_EXITREASON)) < 0){
						if(ret != JOB_REGISTRY_NOT_FOUND){
							fprintf(stderr,"Update of record returns %d: ",ret);
							perror("");
						}
					} else {
						if(ret==JOB_REGISTRY_SUCCESS){
							if (en.status == REMOVED || en.status == COMPLETED) {
								do_log(debuglogfile, debug, 2, "%s: registry update in IntStateQuery for: jobid=%s creamjobid=%s wn=%s status=%d exitcode=%d\n",argv0,en.batch_id,en.user_prefix,en.wn_addr,en.status,en.exitcode);
								job_registry_unlink_proxy(rha, &en);
							}else{
								do_log(debuglogfile, debug, 2, "%s: registry update in IntStateQuery for: jobid=%s creamjobid=%s wn=%s status=%d\n",argv0,en.batch_id,en.user_prefix,en.wn_addr,en.status);
							}
							if (remupd_conf != NULL){
								if ((ret=job_registry_send_update(remupd_head_send,&en,NULL,NULL))<=0){
									do_log(debuglogfile, debug, 2, "%s: Error creating endpoint in IntStateQuery\n",argv0);
								}
							}
						}
					}
					en.status = UNDEFINED;
					JOB_REGISTRY_ASSIGN_ENTRY(en.exitreason,"\0");
					JOB_REGISTRY_ASSIGN_ENTRY(en.updater_info,"\0");
					JOB_REGISTRY_ASSIGN_ENTRY(en.wn_addr,"\0");
					en.exitcode=-1;
				}
				en.status = UNDEFINED;
				maxtok_l = strtoken(token[0], '=', &token_l);
				batch_str=strdup(token_l[1]);
				JOB_REGISTRY_ASSIGN_ENTRY(en.batch_id,batch_str);
				JOB_REGISTRY_ASSIGN_ENTRY(en.updater_info,string_now);
				en.exitcode=-1;
				bupdater_push_active_job(&bact, en.batch_id);
				do_log(debuglogfile, debug, 4, "%s: bupdater_push_active_job done for %s\n",argv0,en.batch_id);
				free(batch_str);
				freetoken(&token_l,maxtok_l);
				if(!first) free(ren);
				if ((ren=job_registry_get(rha, en.batch_id)) == NULL){
						fprintf(stderr,"Get of record returns error ");
						perror("");
				}
				if(ren){
					if(strlen(ren->updater_info)>0){
						en.udate=ren->udate;
					}else{
						en.udate=time(0);
					}
				}
				first=FALSE;
				
			}else if(line && strstr(line," JobState=")){
				if(token[0] && strstr(line,"JobState=")){
					maxtok_l = strtoken(token[0], '=', &token_l);
					if(token_l[1] && strstr(token_l[1],"PENDING")){
						en.status=IDLE;
						en.exitcode=-1;
						JOB_REGISTRY_ASSIGN_ENTRY(en.updater_info,string_now);
					}else if(token_l[1] && strstr(token_l[1],"RUNNING")){
						en.status=RUNNING;
						en.exitcode=-1;
						JOB_REGISTRY_ASSIGN_ENTRY(en.updater_info,string_now);
					}else if(token_l[1] && strstr(token_l[1],"COMPLETED")){
						en.status=COMPLETED;
						en.exitcode=0;
						JOB_REGISTRY_ASSIGN_ENTRY(en.updater_info,string_now);
					}else if(token_l[1] && strstr(token_l[1],"CANCELLED")){
						en.status=REMOVED;
						en.exitcode=-999;
						JOB_REGISTRY_ASSIGN_ENTRY(en.updater_info,string_now);
					}else if(token_l[1] && strstr(token_l[1],"FAILED")){
						en.status=COMPLETED;
						en.exitcode=0;
						JOB_REGISTRY_ASSIGN_ENTRY(en.updater_info,string_now);
					}else if(token_l[1] && strstr(token_l[1],"SUSPENDED")){
						en.status=HELD;
						en.exitcode=-1;
						JOB_REGISTRY_ASSIGN_ENTRY(en.updater_info,string_now);
					}else if(token_l[1] && strstr(token_l[1],"COMPLETING")){
						bupdater_remove_active_job(&bact, en.batch_id);
					}
					freetoken(&token_l,maxtok_l);
				}
			}else if(line && strstr(line," BatchHost=")){
				if(token[0] && strstr(line,"BatchHost=")){
					maxtok_l = strtoken(token[0], '=', &token_l);
					if(en.status!=IDLE){
						JOB_REGISTRY_ASSIGN_ENTRY(en.wn_addr,token_l[1]);
					}
					freetoken(&token_l,maxtok_l);
				}
			}else if(line && strstr(line," ExitCode=")){
				if(token[3] && strstr(line,"ExitCode=")){
					maxtok_l = strtoken(token[3], '=', &token_l);
					maxtok_e = strtoken(token_l[1], ':', &token_e);
					if(en.status==COMPLETED){
						en.exitcode=atoi(token_e[0]);
					}
					freetoken(&token_l,maxtok_l);
					freetoken(&token_e,maxtok_e);
				}
			}else if(line && strstr(line," SubmitTime=")){
				if(en.status==IDLE){
					if(token[0] && strstr(line,"SubmitTime=")){
						maxtok_l = strtoken(token[0], '=', &token_l);
						tmstampepoch=str2epoch(token_l[1],"N");
						en.udate=tmstampepoch;
						freetoken(&token_l,maxtok_l);
					}
				}
			}else if(line && strstr(line," StartTime=")){
				if(en.status==RUNNING){
					if(token[0] && strstr(line,"StartTime=")){
						maxtok_l = strtoken(token[0], '=', &token_l);
						tmstampepoch=str2epoch(token_l[1],"N");
						en.udate=tmstampepoch;
						freetoken(&token_l,maxtok_l);
					}
				}
				if(en.status==COMPLETED || en.status==REMOVED){
					if(token[1] && strstr(line,"EndTime=")){
						maxtok_l = strtoken(token[1], '=', &token_l);
						tmstampepoch=str2epoch(token_l[1],"N");
						en.udate=tmstampepoch;
						freetoken(&token_l,maxtok_l);
					}
				}
			}else if(line && strstr(line," SuspendTime=")){
				if(en.status==HELD){
					if(token[1] && strstr(line,"SuspendTime=")){
						maxtok_l = strtoken(token[1], '=', &token_l);
						tmstampepoch=str2epoch(token_l[1],"N");
						en.udate=tmstampepoch;
						freetoken(&token_l,maxtok_l);
					}
				}
			}
			
			free(line);
			free(string_now);
			freetoken(&token,maxtok_t);
		}
		pclose(fp);
	}
		
	if(en.status!=UNDEFINED && ren && ren->status!=REMOVED && ren->status!=COMPLETED){	
		if ((ret=job_registry_update_recn_select(rha, &en, ren->recnum,
		JOB_REGISTRY_UPDATE_WN_ADDR|
		JOB_REGISTRY_UPDATE_STATUS|
		JOB_REGISTRY_UPDATE_UDATE|
		JOB_REGISTRY_UPDATE_UPDATER_INFO|
		JOB_REGISTRY_UPDATE_EXITCODE|
		JOB_REGISTRY_UPDATE_EXITREASON)) < 0){
			if(ret != JOB_REGISTRY_NOT_FOUND){
				fprintf(stderr,"Update of record returns %d: ",ret);
				perror("");
			}
		} else {
			if(ret==JOB_REGISTRY_SUCCESS){
				if (en.status == REMOVED || en.status == COMPLETED) {
					do_log(debuglogfile, debug, 2, "%s: registry update in IntStateQuery for: jobid=%s creamjobid=%s wn=%s status=%d exitcode=%d\n",argv0,en.batch_id,en.user_prefix,en.wn_addr,en.status,en.exitcode);
					job_registry_unlink_proxy(rha, &en);
				}else{
					do_log(debuglogfile, debug, 2, "%s: registry update in IntStateQuery for: jobid=%s creamjobid=%s wn=%s status=%d\n",argv0,en.batch_id,en.user_prefix,en.wn_addr,en.status);
				}
				if (remupd_conf != NULL){
					if ((ret=job_registry_send_update(remupd_head_send,&en,NULL,NULL))<=0){
						do_log(debuglogfile, debug, 2, "%s: Error creating endpoint in IntStateQuery\n",argv0);
					}
				}
			}
		}
	}				

	free(ren);
	free(command_string);
	return 0;
}