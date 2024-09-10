/*******************************************************************************
 MAIN FUNCTION
*******************************************************************************/
int main(int ac, char **av)
{
	FILE *fp;
	int	fd;
	int  pid;

	int i, j, ln, err, kf, dRet;
	int init_only_one = 0;
	int verbose_flag = 0;

	char buf[BUF_SIZE];
	char fname[BUF_SIZE];
	char block_name[BUF_SIZE];
	char tmpbuf[128], errbuf[2048];

	signal(SIGHUP, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);
	signal(SIGQUIT, init_isr);

	dRet = dGetUserPermission();
    if( dRet == 0 )
    {
        sprintf(errbuf, "INAVLID USER PERMISSION\n" );
        PrintOut(TIFB_FAIL, errbuf);

        return 1;
    }

	dRet = dGetBlocks(FILE_MC_INIT,STR_TSW_COM);
	if( dRet < 0 ){
        sprintf(errbuf, "FAILED IN McInit\n" );
        PrintOut(TIFB_FAIL, errbuf);

        return 1;

	}
	else{
		dCurrBlockCnt = dRet;
	}

	if( init_proc() < 0 ){
		exit(0);
	}

	if (ac == 1)	/*** ALL START ********************************************/
	{
		strcpy(fname, FILE_MC_INIT); /*** "McInit" File ****************************/
	}
	else if (ac > 3)
	{
		UsageExit();
	}
	else
	{
		for(i = 1;i < ac;i++)
		{
			if (av[i][0] != '-')
			{
				UsageExit();
			}
			else if(av[i][1] == 'b')
			{
				if( ac < 3 )
				{
					UsageExit();
				}
				else	/*** ONLY ONE BLOCK START *****************************/
				{
					++i;
					init_only_one = 1;
 					for(j = 0;j < strlen(av[i]);j++)
						block_name[j] = toupper(av[i][j]);
					block_name[j] = 0;
				}
			}
			else if( av[i][1] == 'v' )	/*** ALL START ************************/
			{
				verbose_flag = 1;
			}
			else if(av[i][1] == 'd') {

                /* FOR SYSTEM AUTO RESTART : WAIT BOOTTING COMPLETE */
                sleep(300);
                verbose_flag = 1;
            }
			else
			{
				UsageExit();
			}
		}
	}

 	//freopen("/dev/null", "w", stdout);

	/*** 한개 블럭을 기동 시킴 ************************************************/
	if (init_only_one)
	{
		pid = InitOnlyOneBlock(block_name);
        if(pid > 0)
        {
            sprintf(errbuf, "NEW BLOCK : %s\n  PROCESS ID: %d\n", block_name, pid);
            PrintOut(TIFB_SUCCESS, errbuf);

            for(i=0; i< dCurrBlockCnt; i++)
            {
				if( STR_TSW_COM[i] == NULL )
					continue;

                if( !strcasecmp(block_name, STR_TSW_COM[i]) )
                {
                    send_pid_msg(i, pid);
                    break;
                }
            }
        }
		exit(0);
	}

	/***************************************************************************
	 READ FIDB_FILE, SET SHARED MEMORY VALUE
	***************************************************************************/
	if ((fd = open (FILE_FIDB, O_RDONLY, 0666)) < 0)
    {
    }
	else
	{
		remove( FILE_FIDB );
	}

	strcpy(fname, FILE_MC_INIT);

	if((fp = fopen(fname, "r")) == NULL)
	{
		sprintf(errbuf, "CAN'T OPEN FILE %s\n", fname);
		PrintOut(TIFB_FAIL, errbuf);
		exit(1);
	}

	ln = cntr = 0;

	/***************************************************************************
	 READ McInit File. SET blocks(bname, fname) VALUE
	***************************************************************************/
	while(fgets(buf, BUF_SIZE, fp) != NULL)
	{
		ln++;
		if (AnalyzeLine(buf) < 0)
		{
			fclose(fp);
			close(fd);
			sprintf(errbuf, "SYNTAX ERROR (FILE: %s, LINE: %d)\n", fname, ln);
			PrintOut(TIFB_FAIL, errbuf);
			exit(1);
		}
	}

	fclose(fp);

	/***************************************************************************
	 WHEN ALL BLOCK IS STARTED, CHECK 2 TIMES
	***************************************************************************/
	if( verbose_flag == 0 )
	{
		fprintf(stderr, "\n\tBlocks to initialize are follows.\n");
		PrintBlocks();

		fprintf(stderr, "\tDo you want initialize (y/n) ? ");
		err = GetYorN();
		if(err == _NO)
		{
			sprintf(errbuf, "STOPPED BY USER REQUEST\n");
			PrintOut(TIFB_SUCCESS, errbuf);
			exit(0);
		}
		fprintf(stderr, "\n\tDo you really want initialize (y/n) ? ");
		err = GetYorN();
		if(err == _NO)
		{
			sprintf(errbuf, "STOPPED BY USER REQUEST\n");
			PrintOut(TIFB_SUCCESS, errbuf);
			exit(0);
		}
	}

    sprintf(errbuf, "MAIN COMPUTER PROCESSS INITIALIZATION STARTED\n");
	PrintOut( TIFB_SUCCESS , errbuf );

	signal(SIGINT, init_isr);


	/*** 프로세스 기동을 개시함 ***********************************************/
	for(i=0; i<cntr; i++)
	{
		/*** 파일의 존재 및 수행가능성 조사 ***********************************/
		if( IsCorrectBlock(i) < 0 )
		{
			if( verbose_flag == 1 )
			{
				continue;
			}
			else
			{
				sprintf(errbuf, "FILE %s DOES NOT EXIST\n", blocks[i].fname);

				PrintOut(TIFB_FAIL, errbuf);

				fprintf(stderr, "\n\tDo you want to continue (y/n) ? ");

				err = GetYorN();

				if(err == _YES)
				{
					inits[i].isinit = _FALSE;
					continue;
				}
				else
				{
					final_isr();
				}
			}
		}

		/*** 이미 실행중인지 여부를 검사 **************************************/
		if ( (pid = GetProcessID(blocks[i].bname)) > 0 )
		{
			/* 이미 실행중인 경우 */

			if( verbose_flag == 1 )
			{
				err = _YES ;
			}
			else
			{
				fprintf(stderr, "\n\tBlock \"%s\" is already running.\n", blocks[i].bname);
				fprintf(stderr, "\tDo you want replace block \"%s\" (y/n) ? ", blocks[i].bname);
				err = GetYorN();
			}

			if(err == _NO)
			{
				inits[i].isinit = _FALSE;
				continue;
			}
			else
			{
				/* New Version of Killing */
				kf = kill(pid, SIGTERM);

				if (kf < 0)
				{
					//sleep(2);
					if (kill(pid, SIGTERM) < 0)
					{
			   			if (errno == ESRCH)
			       			kf = 0;
			  		}
					else
					{
			   			kf = 0;
					}
			   	}

				if ( kf && kill(pid, SIGKILL) < 0)
				{
					if( verbose_flag == 1 )
					{
						err = _YES ;
					}
					else
					{
						fprintf(stderr, "\tCan't kill process \"%d\"(%s)\n", pid, blocks[i].bname);
						fprintf(stderr, "\tDo you want to continue (y/n) ? ");
						err = GetYorN();
					}


					if(err == _YES)
					{
						inits[i].isinit = _FALSE;
						continue;
					}
					else
					{
						final_isr();
					}
				}
				else
				{
					sprintf(errbuf, "PROCESS %s(PID=%d) KILLED\n", blocks[i].fname, pid);
					PrintOut(TIFB_SUCCESS, errbuf);
				}
			}
		}

		signal(SIGTERM, init_isr);

		/***********************************************************************
		 PROCESS START
		***********************************************************************/
		err = ProcessStart(i);

		if(err == -1)
		{

			if( verbose_flag == 1 )
			{
				continue;
			}
			else
			{
				sprintf(errbuf, "CAN'T START PROCESS BLOCK: %s\n", blocks[i].bname);
				PrintOut(TIFB_FAIL, errbuf);

				fprintf(stderr, "\tDo you want to continue (y/n) ? ");
			}
		}
		else if(err == -2)
		{
			if( verbose_flag == 1 )
			{
				continue;
			}
			else
			{
				sprintf(errbuf, "PROGRAM NAME %s DOES NOT MEET NAME CONVENTION\n", blocks[i].fname);
				strcat(errbuf, "  ABANDON EXECUTING PROCESS\n");
				PrintOut(TIFB_FAIL, errbuf);

				fprintf(stderr, "\tDo you want to continue (y/n) ? ");
			}
		}

		if(err < 0)
		{
			if( verbose_flag == 1 )
			{
				err = _YES;
			}
			else
			{
				err = GetYorN();
			}


			if(err == _NO)
			{
				final_isr();
			}
			else
			{
				inits[i].isinit = _FALSE;
				continue;
			}
		}
		else
		{
			sprintf(errbuf, "A PROCESS INIAILIZATION SUCCESS\n");
			sprintf(tmpbuf, "  BLOCK NAME   : %s\n", blocks[i].bname);
			strcat(errbuf, tmpbuf);
			sprintf(tmpbuf, "  PROGRAM NAME : %s\n", blocks[i].fname);
			strcat(errbuf, tmpbuf);
			sprintf(tmpbuf, "  PROCESS ID   : %d\n", err);
			strcat(errbuf, tmpbuf);

			PrintOut(TIFB_SUCCESS, errbuf);
			sleep(1);


			for(j=0; j< dCurrBlockCnt; j++)
			{
				if( STR_TSW_COM[i] == NULL )
					continue;

				if( !strcasecmp(blocks[i].bname, STR_TSW_COM[j]) )
				{
					send_pid_msg(j, err );
					break;
				}
			}

			inits[i].isinit = _TRUE;
			inits[i].pid = err;
		}
	}

	PrintSuccessBlocks();
	printf("UPRESTO co. GTAM\n\n");
	exit(1);
}