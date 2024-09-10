BOOL runImpCtrl(void)
{
    BOOL ok;
    USHORT curCmd = 0;
    char fileDir[256], *tmpNam;
#ifdef HAVE_CRYPT
    char locSalt[3];
#endif

    ok = FALSE;
    if (DoDebug)
    {
	sprintf(fileDir, "%s/server/%s", FIFO_DIR, IMP_TEST_PORT);
    }
    else if (PlayPort[0] != '\0')
    {
	sprintf(fileDir, "%s/server/%s", FIFO_DIR, &PlayPort[0]);
    }
    else
    {
	sprintf(fileDir, "%s/server/%s", FIFO_DIR, IMPERIUM_PORT);
    }
    ImperiumPort = open(fileDir, O_WRONLY | O_NDELAY, 0);
    if (ImperiumPort >= 0)
    {
        ISt = ImpAlloc();
        if (ISt != NULL)
        {
	    tmpNam = tempnam(FIFO_DIR, "ictl");
	    if (tmpNam == NULL)
	    {
		puts("Unable to allocate memory for temp name");
	    }
	    else if (mknod(tmpNam, S_IFIFO|0622, 0) == -1)
	    {
		printf("Unable to create named pipe %s\n", tmpNam);
	    }
#ifdef BROKEN_MKNOD
	    else if (chmod(tmpNam, 0622) != 0)
	    {
		printf("Unable to change mode for named pipe %s\n", tmpNam);
	    }
#endif
#ifdef BROKEN_PIPE
	    else if ((myPort = open(tmpNam, O_RDWR | O_NDELAY)) == -1)
#else
	    else if ((myPort = open(tmpNam, O_RDONLY | O_NDELAY)) == -1)
#endif
	    {
		(void)unlink(tmpNam);
		printf("Unable to open named pipe %s\n", tmpNam);
	    }
	    else
	    {
		    strcpy(UsePort, tmpNam);
                    IS = ISt;
                    ISt->is_serverRequest = serverRequest;
                    ISt->is_writeUser = writeUser;
                    ISt->is_readUser = readUser;
                    ISt->is_timedReadUser = timedReadUser;
                    ISt->is_echoOff = echoOff;
                    ISt->is_echoOn = echoOn;
                    ISt->is_gotControlC = gotControlC;
                    ISt->is_sleep = locSleep;
                    ISt->is_log = userLog;
                    ISt->is_extEdit = doExtEdit;
                    LogFd = NULL;

                    ISt->is_request.rq_type = rt_startClient;
                    strcpy(&ISt->is_request.rq_text[0], tmpNam);
		    /* Fill in the correct security code */
#ifdef HAVE_CRYPT
		    sprintf(&locSalt[0], "%2.2x", getpid() % 64);
		    sprintf(&ISt->is_request.rq_private[2], "%-.15s",
			crypt(IMP_CTRL_CODE, &locSalt[0]));
#else /* !HAVE_CRYPT */
		    strcpy(&ISt->is_request.rq_private[2], IMP_CTRL_CODE);
#endif
                    serverRequest();
		    /* Check to see if we were recognized */
		    if (ISt->is_request.rq_private[2] == '\0')
		    {
			/* Nope! */
			puts("*** outdated/invalid identity code");
		    }
		    else
		    {
			/* Yup! */
		        if (ServLog)
		        {
                	    strcpy(&ISt->is_request.rq_private[2],
			        "Imperium control utility started");
			    ISt->is_request.rq_type = rt_log;
			    serverRequest();
		        }

                        /* clear out buffer and set up no outside time limit */
                        memset(&ISt->is_textIn[0], '\0', INPUT_BUFFER_SIZE *
                            sizeof(char));

                        /* do the init call */
                        ISt->is_argShort = 0;
                        ImpCntrl(ISt);

                        while (curCmd < NumCmds)
                        {
                            switch(cmds[curCmd])
                            {
                                case 'p':
                                    ISt->is_argShort = IC_POWER;
                                    break;
                                case 'u':
                                    ISt->is_argShort = IC_UPDATE;
                                    break;
                                case 'm':
                                    ISt->is_argShort = IC_MINER;
                                    break;
                                case 'l':
                                    ISt->is_argShort = IC_INCUSR;
                                    break;
                                case 'L':
                                    ISt->is_argShort = IC_DECUSR;
                                    break;
                                case 'f':
                                    ISt->is_argShort = IC_DOFLUSH;
                                    break;
                                case 's':
                                    ISt->is_argShort = IC_PUBLISH;
                                    break;
                                case '\x50': /* Get around metaconfig problem */
                                default:
                                    ISt->is_argShort = IC_FPOWER;
                                    break;
                            }
                            ISt->is_argBool = ServLog;
                            ImpCntrl(ISt);
                            curCmd++;
                        }

                        if (LogFd != NULL)
                        {
                            logFlush();
                            fclose(LogFd);
                        }
		        if (ServLog)
		        {
			    strcpy(&ISt->is_request.rq_private[2],
			        "Imperium control utility terminated");
			    ISt->is_request.rq_type = rt_log;
			    serverRequest();
		        }
                        ISt->is_request.rq_type = rt_stopClient;
                        serverRequest();
		    }

                    ImpFree(ISt);
                    ok = TRUE;
		    close(myPort);
		    (void)unlink(tmpNam);
	    }
	    if (tmpNam != NULL)
	    {
		free(tmpNam);
	    }
        }