Bool LoadActions(char *file) {
	FILE	*fp;
	int	type, i;
	char	line[MAX_LINE_LEN],*token;
	Action	action,*new_action=NULL;
	
	DEBUG(D_LOAD) printf("LoadActions: %s\n",file);
	fp=fopen(file, "r");
	if (NULL==fp) {
		printf("Cannot open file: %s.\n",file);
		return FALSE;
		}
	while (fgets(line,MAX_LINE_LEN,fp)) {
		if (line[0]=='#') continue;
		if (strlen(line)<=1) continue;

		DEBUG(D_LOAD) printf("DEBUG: Read line: %s\n",line);
		{register int slen;
			slen=strlen(line);
			line[slen-1]=0; /* take out \n from fgets */
			line[slen]=0;   /* add extra \0 for last param check */
			}

		Zero(&action, sizeof(action));

		/* Event Type */
		token=StrTok(line, WHITE_SPACE);
		if (NULL==token) continue;
		type=StrToType(token);
		
		/* Flags */
		NextToken;
		action.flags=StrToFlags(token);

		/* delay */
		NextToken;
		action.delay.tv_sec=atoi(token);
		NextToken;
		action.delay.tv_usec=atoi(token);
		while (action.delay.tv_usec>1000000) {
			action.delay.tv_usec-=1000000;
			action.delay.tv_sec++;
			}
		DEBUG(D_LOAD) printf("DEBUG: delay is sec %d usec %d\n",action.delay.tv_sec,action.delay.tv_usec);
		
		/* Condition & test functions */
		NextToken;
		action.tests=atoi(token);
		new_action=NULL;
		for (i=0; i<action.tests; i++) {
			NextToken;
			if (!strcmp("DEFAULT",token)) {
				new_action=&set[type].default_action;
				}
			else {
				if (token[0]=='-' && token[1]==0) action.match[i]=NULL;
				else {
					if (token[0]=='!') {
						action.not[i]=TRUE;
						token++;
						}
					else action.not[i]=FALSE;
					action.match[i]=StrToCall(token,CALL_TEST);
					}	
				}
			
			NextToken;
			action.cond[i]=StrToCondition(token);
			}
		DEBUG(D_LOAD) printf("Read %d tests\n",i);
		
		/* Call */
		NextToken;
		action.call=StrToCall(token,CALL_ACTION);

		/* call's parameters (in string action.string) */
		token=&token[strlen(token)+1];
		if (strlen(token)>0) {
			action.string=(char *)malloc(strlen(token)+1);
			strcpy(action.string, token);
			DEBUG(D_LOAD) printf("Call Function Parameter: %s\n", token);
			}
		else action.string=NULL;
		
		
		/* add to list */
		set[type].is_set=TRUE;
		if (NULL==new_action) {
			new_action=(Action *)malloc(sizeof(Action));
			bcopy(&action, new_action, sizeof(Action));
			ListAddAfter(&set[type].tlist, ListLastElem(&set[type].tlist), new_action);
			}
		else	bcopy(&action, new_action, sizeof(Action));
		}
	return TRUE;
	}