void execute_cmd(void) {
	currcmd = currcmd % MAXCMDS;
	int curr = currcmd;
	FILE *f;

	if(comtab[curr].external == 0) {
		// Built-in Command
		aliasroot = NULL;
                aliasDepth = 0;

		switch(comtab[curr].code) {
			case CHD : {
	            if( chdir(getHOME) ) {
	                printf("ERROR at line %d\n", __LINE__);
	                break;
	            }
	            setenv("PWD", getHOME, 1);
				break;
			}
			case CDX : {
				char* dest = cleanInput(comtab[curr].atptr[0]);
				if( chdir(dest) == -1 ) {
	                printf("ERROR: \n%s is not a directory\n", dest);
            	}
            	char pwd[5000];
            	getcwd( pwd, sizeof(pwd) );
            	setenv("PWD", pwd, 1);
				break;
			}
			case SETENV : {
				char* name = cleanInput(comtab[curr].atptr[0]);
	            char* word = cleanInput(comtab[curr].atptr[1]);
	            if( setenv( name, word, 1 ) == -1 ) {
	                printf("setenv failed, could not set %s to %s\n", name, word );
	            }
				break;
			}
			case UNSETENV : {
				char* name = cleanInput(comtab[curr].atptr[0]);
	            if( getenv(name) ){
	                unsetenv(name);
	            } else {
	                printf("unsetenv failed, could not find %s\n", name);
	            }
				break;
			}
			case PRINTENV : {
				if(ofileredir) {
					if(comtab[curr].append) {
						f = fopen(comtab[curr].outfd, "a");
					}
					else {
						f = fopen(comtab[curr].outfd, "w");
					}

					if(f == NULL)
						return SYSERR;
				}
				else
					print_env();

				if(ofileredir)
					fclose(f);
				break;
			}
			case SETALIAS : {
				char* name = cleanInput(comtab[curr].atptr[0]);
	            char* word = cleanInput(comtab[curr].atptr[1]);
				setalias(name, word);
				break;
			}
			case UNALIAS : {
				char* name = cleanInput(comtab[curr].atptr[0]);
				removealias(name);
				break;
			}
			case PRINTALIAS : {
				if(ofileredir) {
					if(comtab[curr].append) {
						f = fopen(comtab[curr].outfd, "a");
					}
					else {
						f = fopen(comtab[curr].outfd, "w");
					}
				}
				else
					printalias();

				if(ofileredir)
					fclose(f);
				break;
			}
			case PWD : {
				printf("%s\n", getPWD);
				break;
			}
		}
	}
	else {
		// Handle aliasing
		int acurr = isalias(comtab[curr].comname);

		if(acurr != -1) {
			comtab[curr].external = 0;
			if(aliasroot == NULL) {
				aliasroot = aliastab[acurr].alname;
			}
			// Check for infinite aliasing
			if( aliasDepth > 30 ) {
				printf("ERR: Infinite aliasing detected. Exiting...\n");
				return;
			}
			else {
				ignoreEOF = 1;
				parse_string(aliastab[acurr].alstring);
				aliasDepth++;
				execute_cmd();
			}
		}
		else {
			// External Command
			aliasroot = NULL;
			aliasDepth = 0;
			pid_t child = fork();
			int stat;
			int success = -1;

			while(waitpid(child, &stat, 0) == -1) {
				if(errno != EINTR) {
					stat = -1;
					break;
				}
			}

			if(child < 0)
				exit(1);
			else if(child == 0) {
				// Prepare for execv call
				char tmp[256];
				char *paths = strcpy(tmp, getenv("PATH"));
				char *tok = strtok(paths, ":");
				char *cmp = "./";

				while(tok) {
					char place[255];
					if(comtab[curr].comname[0] == cmp[0] || comtab[curr].comname[0] == cmp[1]) {
						// If destination is specified 
						strcpy(place, comtab[curr].comname);
					}
					else {
						// If destination is not specified
						strcpy(place, tok);
						strcat(place, "/");
						// Append command name
						strcat(place, comtab[curr].comname);
					}

					char *cmds[comtab[curr].nargs + 2];
					cmds[0] = place;
					cmds[comtab[curr].nargs + 1] = (char *)NULL;

					int i = 0;
					for(i; i<comtab[curr].nargs; i++) {
						cmds[i+1] = comtab[curr].atptr[i];
					}

					if(execv(place, cmds) == -1) {
						tok = strtok(NULL, ":");
						continue;
					}
					else {
						_exit(0);
						success = 1;
						break;
					}
				}

				if(success == -1) {
					printf("ERR: Command not found: %s\n", comtab[curr].comname);
					_exit(1);
				}
			}
		}
	}

	currcmd += 1;
	comtab[currcmd].external = 0;
	ignoreEOF = 0;
}