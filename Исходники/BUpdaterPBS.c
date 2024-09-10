int
IntStateQuery()
{
/*
qstat -f

Job Id: 11.cream-12.pd.infn.it
    Job_Name = cream_579184706
    job_state = R
    ctime = Wed Apr 23 11:39:55 2008
    exec_host = cream-wn-029.pn.pd.infn.it/0
*/

/*
 Filled entries:
 batch_id
 wn_addr
 status
 udate
 
 Filled by submit script:
 blah_id 
 
 Unfilled entries:
 exitreason
*/


        FILE *fp;
	char *line=NULL;
	char **token;
	int maxtok_t=0;
	job_registry_entry en;
	int ret;
	char *timestamp;
	time_t tmstampepoch;
	char *batch_str=NULL;
	char *wn_str=NULL; 
        char *twn_str=NULL;
        char *status_str=NULL;
	char *ex_str=NULL;
	int  ex_code=0; 
	char *cp=NULL;
	char *command_string=NULL;
	job_registry_entry *ren=NULL;
	int first=TRUE;
	time_t now;
	char *string_now=NULL;

	command_string=make_message("%s%s/qstat -f",batch_command,pbs_binpath);
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
			if(line && strstr(line,"Job Id: ")){
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
								do_log(debuglogfile, debug, 2, "%s: registry update in IntStateQuery for: jobid=%s wn=%s status=%d exitcode=%d\n",argv0,en.batch_id,en.wn_addr,en.status,en.exitcode);
								job_registry_unlink_proxy(rha, &en);
							}else{
								do_log(debuglogfile, debug, 2, "%s: registry update in IntStateQuery for: jobid=%s wn=%s status=%d\n",argv0,en.batch_id,en.wn_addr,en.status);
							}
						}
						if (remupd_conf != NULL){
							if (ret=job_registry_send_update(remupd_head_send,&en,NULL,NULL)<=0){
								do_log(debuglogfile, debug, 2, "%s: Error creating endpoint in IntStateQuery\n",argv0);
							}
						}
					}
					en.status = UNDEFINED;
					JOB_REGISTRY_ASSIGN_ENTRY(en.wn_addr,"\0");
					JOB_REGISTRY_ASSIGN_ENTRY(en.exitreason,"\0");
					JOB_REGISTRY_ASSIGN_ENTRY(en.updater_info,"\0");
					en.exitcode=-1;
				}				
                        	maxtok_t = strtoken(line, ':', &token);
				batch_str=strdel(token[1]," ");
				JOB_REGISTRY_ASSIGN_ENTRY(en.batch_id,batch_str);
				JOB_REGISTRY_ASSIGN_ENTRY(en.updater_info,string_now);
				en.exitcode=-1;
				bupdater_push_active_job(&bact, en.batch_id);
				free(batch_str);
				freetoken(&token,maxtok_t);
				if(!first) free(ren);
				if ((ren=job_registry_get(rha, en.batch_id)) == NULL){
						fprintf(stderr,"Get of record returns error for %s ",en.batch_id);
						perror("");
				}
				first=FALSE;				
			}else if(line && strstr(line,"job_state = ")){	
				maxtok_t = strtoken(line, '=', &token);
				status_str=strdel(token[1]," ");
				if(status_str && strcmp(status_str,"Q")==0){ 
					en.status=IDLE;
					en.exitcode=-1;
					JOB_REGISTRY_ASSIGN_ENTRY(en.wn_addr,"\0");
				}else if(status_str && strcmp(status_str,"W")==0){ 
					en.status=IDLE;
					en.exitcode=-1;
				}else if(status_str && strcmp(status_str,"R")==0){ 
					en.status=RUNNING;
					en.exitcode=-1;
				}else if(status_str && strcmp(status_str,"C")==0){ 
					en.status=COMPLETED;
					JOB_REGISTRY_ASSIGN_ENTRY(en.exitreason,"\0");
				}else if(status_str && strcmp(status_str,"H")==0){ 
					en.status=HELD;
					en.exitcode=-1;
					JOB_REGISTRY_ASSIGN_ENTRY(en.wn_addr,"\0");
				}
				free(status_str);
				freetoken(&token,maxtok_t);
			}else if(line && strstr(line,"unable to run job")){
				en.status=IDLE;	
				en.exitcode=-1;
			}else if(line && strstr(line,"exit_status = ")){
				maxtok_t = strtoken(line, '=', &token);
				ex_str=strdel(token[1]," ");
				ex_code=atoi(ex_str);
				if(ex_code==0){
					en.exitcode=0;
				}else if(ex_code==271){
					en.status=REMOVED;
                        		en.exitcode=-999;
				}else{
					en.exitcode=ex_code;
				}
				free(ex_str);
				freetoken(&token,maxtok_t);
			}else if(line && strstr(line,"exec_host = ")){	
				maxtok_t = strtoken(line, '=', &token);
				twn_str=strdup(token[1]);
                		if(twn_str == NULL){
                        		sysfatal("strdup failed for twn_str in IntStateQuery: %r");
                		}
				freetoken(&token,maxtok_t);
				maxtok_t = strtoken(twn_str, '/', &token);
				wn_str=strdel(token[0]," ");
				JOB_REGISTRY_ASSIGN_ENTRY(en.wn_addr,wn_str);
				free(twn_str);
 				free(wn_str);
				freetoken(&token,maxtok_t);
			}else if(line && strstr(line,"mtime = ")){	
                        	maxtok_t = strtoken(line, ' ', &token);
				timestamp=make_message("%s %s %s %s %s",token[2],token[3],token[4],token[5],token[6]);
                        	tmstampepoch=str2epoch(timestamp,"L");
				free(timestamp);
				en.udate=tmstampepoch;
				freetoken(&token,maxtok_t);
			}
			free(line);
			free(string_now);

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
					do_log(debuglogfile, debug, 2, "%s: registry update in IntStateQuery for: jobid=%s wn=%s status=%d exitcode=%d\n",argv0,en.batch_id,en.wn_addr,en.status,en.exitcode);
					job_registry_unlink_proxy(rha, &en);
				}else{
					do_log(debuglogfile, debug, 2, "%s: registry update in IntStateQuery for: jobid=%s wn=%s status=%d\n",argv0,en.batch_id,en.wn_addr,en.status);
				}
			}
			if (remupd_conf != NULL){
				if (ret=job_registry_send_update(remupd_head_send,&en,NULL,NULL)<=0){
					do_log(debuglogfile, debug, 2, "%s: Error creating endpoint in IntStateQuery\n",argv0);
				}
			}
		}
	}				

	free(ren);
	free(command_string);
	return 0;
}