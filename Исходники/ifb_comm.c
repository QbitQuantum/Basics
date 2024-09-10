//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void ifb_printProcStatus (void)
{
	int		i, alive=0, dead=0;
#if 0
	FILE *fp;
	int state;
	char buff[MAXLINE];
	char proc_usr[8], proc_stime[8], proc_tmptime[16];
	int  proc_pid;
	char cmd[] = "ps -ef|grep DAPP=|awk '{ print $1, $2, $5}'";
    char *pos = NULL;
	int  pos_idx=0;
#endif
	if (displayQkeyFlag) {
		fprintf(stderr,"===================================================================================================\n");
		fprintf(stderr," SYSTEM OPERATION MODE : %s\n", ifb_getSysOperMode(loc_sadb->loc_system_dup.myLocalDupStatus));
		fprintf(stderr,"===================================================================================================\n");
		fprintf(stderr," Process    PID      STATUS  MSG_Q_KEY    VERSION  Process    PID      STATUS  MSG_Q_KEY    VERSION  \n");
		fprintf(stderr,"---------------------------------------------------------------------------------------------------");
	} else {
		fprintf(stderr,"===================================================================================================\n");
		fprintf(stderr," SYSTEM OPERATION MODE : %s\n", ifb_getSysOperMode(loc_sadb->loc_system_dup.myLocalDupStatus));
		fprintf(stderr,"===================================================================================================\n");
		fprintf(stderr," Process    PID      STATUS  START-TIME   VERSION  Process    PID      STATUS  START-TIME   VERSION  \n");
		fprintf(stderr,"---------------------------------------------------------------------------------------------------");
	}

	for (i=0; i<SYSCONF_MAX_APPL_NUM; i++)
	{
		if (!strcasecmp (confProcTbl[i].procName, ""))
			break;
		if (i%2==0) fprintf(stderr,"\n");
		if (confProcTbl[i].runCnt) {
			if (displayQkeyFlag) {
				if (confProcTbl[i].runCnt == 1)
					fprintf(stderr," %-10s %-8d ALIVE   0x%-10x %-8s", confProcTbl[i].procName,
							(int)confProcTbl[i].pid, confProcTbl[i].msgQkey, confProcTbl[i].procVersion);
				else
					fprintf(stderr," %-10s %-8d ALIVE(%d)0x%-10x %-8s", confProcTbl[i].procName,
							(int)confProcTbl[i].pid, confProcTbl[i].runCnt, confProcTbl[i].msgQkey, confProcTbl[i].procVersion);
			} else {
				if (confProcTbl[i].runCnt == 1)
					fprintf(stderr," %-10s %-8d ALIVE   %-12s %-8s", confProcTbl[i].procName,
							(int)confProcTbl[i].pid, confProcTbl[i].startTime, confProcTbl[i].procVersion);
				else
					fprintf(stderr," %-10s %-8d ALIVE(%d)%-12s %-8s", confProcTbl[i].procName,
							(int)confProcTbl[i].pid, confProcTbl[i].runCnt, confProcTbl[i].startTime, confProcTbl[i].procVersion);
			}
			alive += confProcTbl[i].runCnt;
		} else {
			if (displayQkeyFlag) {
				fprintf(stderr," %-10s -        DEAD    0x%-10x %-8s", confProcTbl[i].procName,
						confProcTbl[i].msgQkey, confProcTbl[i].procVersion);
			} else {
				fprintf(stderr," %-10s -        DEAD    -     -      %-8s", confProcTbl[i].procName, "-");
			}
			dead++;
		}
	}
#if 1
	/* SM/CM Process Status Management, by sjjeon */
	{
		int sm_pid,cm_pid, rv;
		char startTM[32];
		char version[]="R1.0.0";

		// SM PID, TIME 을 구한다.
		sm_pid = getProcessID("SMSERVER");
 		rv = getPidInfo(sm_pid, startTM);
 		if(rv >= 0){
			fprintf(stderr,"\n %-10s %-8d ALIVE   %-12s %-8s","SM",sm_pid, startTM, version);
			alive += 1;
		}
		else{
			fprintf(stderr,"\n %-10s -        DEAD    -      %-8s","SM", version);
			dead +=1;
 		}

		// CM PID, TIME 을 구한다.
 		memset(startTM,0x00,sizeof(startTM));
 		cm_pid = getProcessID("CM");
 		rv = getPidInfo(cm_pid, startTM);
 		if(rv >= 0){
			fprintf(stderr," %-10s %-8d ALIVE   %-12s %-8s","CM",cm_pid, startTM, version);
     		alive += 1;
 		}
 		else{
			fprintf(stderr," %-10s -        DEAD    -      %-8s","CM", version);
			dead +=1;
		}
	}
	
#else
	/* SM/CM Process Status Management, by june */
	fp = popen(cmd, "r");
	if (fp == NULL) {
		perror("erro : "); exit(0);
	}
	fprintf(stderr,"\n");
	while(fgets(buff, MAXLINE, fp) != NULL)
	{
		if( sscanf( &buff[0], "%s %d %s", proc_usr, &proc_pid, proc_tmptime)==3) {
//////////////////////////////////////////////////////////////////////////////////////////////////
			pos = strrchr(proc_tmptime, ':');
			if (pos != NULL) {
				pos_idx = pos - proc_tmptime;
				proc_tmptime[pos_idx] = '\0';
			}
			sprintf(proc_stime, "%s", proc_tmptime);
//////////////////////////////////////////////////////////////////////////////////////////////////
			if (!strncmp(proc_usr, "pcube", 5)) {
				strncpy(proc_stime, proc_tmptime, 5);
				if (smLiveCheck()==0) {
					fprintf(stderr," %-10s %-8d ALIVE         %-5s  %-8s", "SMSERVER", proc_pid, proc_stime, "R1.0.0");
					alive++;
				} else {
					fprintf(stderr," %-10s %-8d DEAD          %-5s  %-8s", "SMSERVER", proc_pid, proc_stime, "R1.0.0");
					dead++;
				}
			}
			if (!strncmp(proc_usr, "scmscm", 6)) {
				if (cmLiveCheck()==0) {
					fprintf(stderr," %-10s %-8d ALIVE         %-5s  %-8s", "CM", proc_pid, proc_stime, "R1.0.0");
					alive++;
				} else {
					fprintf(stderr," %-10s %-8d DEAD          %-5s  %-8s", "CM", proc_pid, proc_stime, "R1.0.0");
					dead++;
				}
			}
		}
	}

	state = pclose(fp);
#endif
	fprintf(stderr,"\n===================================================================================================\n");
	fprintf(stderr,"TOTAL:%d (ALIVE:%d, DEAD:%d)\n\n", alive+dead, alive, dead);

	return;

} //----- End of ifb_printProcStatus -----//