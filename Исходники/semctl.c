int CBD1
semctl(int semid, int semnum, int cmd, ...)
{
	BOOL	ret;
	int	iret;
	DWORD	dwret;
	int	i, j, diffsemval;
#ifndef TERMINAL_SERVICE
	char	semstr[16];
#else
	char	semstr[30];
#endif	/* TERMINAL_SERVICE */
	BOOL	lret;
	HANDLE	hsem;
	int	piid;
	DWORD	procid;
	va_list vlist;
	union	semun	semarg;
	LPTSTR	lpszPipeName = "\\\\.\\pipe\\ipcd";
	SCBUF	scIn, scOut;
	DWORD	bytesRead;
	HANDLE	hIpct = NULL;
	IPCT	*ipct = NULL;
#ifdef	TERMINAL_SERVICE
	OSVERSIONINFOEX osvi;

	ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

	if( !GetVersionEx ((OSVERSIONINFO *) &osvi) )
	{
	  // If OSVERSIONINFOEX doesn't work, try OSVERSIONINFO.
		osvi.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
		GetVersionEx( (OSVERSIONINFO *) &osvi );
	}
#endif	/* TERMINAL_SERVICE */

//	StartIPCD();
	if (semid<0 || semid>=MAXNOOFIPC)
	{
		errno=EINVAL;
		return -1;
	}

	if (GetIPCT(&hIpct, &ipct)<0)
	{
		errno=EFAULT;
		return -1;
	}

	if (ipct->semt[semid].key<0)
	{
		procid=GetCurrentProcessId();
		piid=FindPINFO(OPT_SEM, procid, ipct);
		if (piid>=0)
		{
			for (i=0; i<MAXNSEM; i++)
				ipct->pseminfo[piid].semadj[semid][i]=0;
			ipct->pseminfo[piid].semid[semid]=0;
			InitPINFO(OPT_SEM, piid, ipct);
		}
		errno=EINVAL;
		FreeIPCT(hIpct, ipct);
		return -1;
	}

	if (semnum<0 || semnum>ipct->semt[semid].semds.sem_nsems)
	{
		errno=EINVAL;
		FreeIPCT(hIpct, ipct);
		return -1;
	}

	va_start(vlist, cmd);
	semarg=va_arg(vlist, union semun);
	va_end(vlist);

	switch (cmd)
	{
	case	IPC_STAT:
		if (semarg.buf == NULL)
		{
			FreeIPCT(hIpct, ipct);
			return -1;
		}

		memcpy((PSTR)semarg.buf, (PSTR)&ipct->semt[semid].semds,
						sizeof(ipct->semt[semid].semds));
		FreeIPCT(hIpct, ipct);
		return 0;

	case	IPC_RMID:

		scIn.cmd=SNO_SEMCTL;
		scIn.data=semid;

		lret = CallNamedPipe(lpszPipeName,
			 (char *)&scIn, sizeof(scIn),
			 (char *)&scOut, sizeof(scOut),
			 &bytesRead, NMPWAIT_WAIT_FOREVER);

		if (lret==FALSE)
		{
			errno=GetLastError();
			FreeIPCT(hIpct, ipct);
			return -1;
		}
		if (scOut.cmd!=SNO_OK)
		{
			errno=scOut.data;
			FreeIPCT(hIpct, ipct);
			return -1;
		}

		if( InitSEMT(semid, ipct) < 0 )
			return -1;

		for (i=0; i<MAXNOOFIPC; i++)
		{
			for (j=0; j<MAXNSEM; j++)
				ipct->pseminfo[i].semadj[semid][j]=0;
			ipct->pseminfo[i].semid[semid]=0;
			InitPINFO(OPT_SEM, i, ipct);
		}


		FreeIPCT(hIpct, ipct);
		return 0;

	case	GETVAL:
		iret=ipct->semb[semid][semnum].semval;
		FreeIPCT(hIpct, ipct);
		return iret;

	case	SETVAL:
		if (semarg.val < 0)
		{
			errno = EINVAL;
			FreeIPCT(hIpct, ipct);
			return -1;
		}

		diffsemval=semarg.val-ipct->semb[semid][semnum].semval;

#ifndef TERMINAL_SERVICE
		MakeSemstr(semstr, semnum, semid, ipct->semt[semid].key);
#else
		if( osvi.dwMajorVersion >= 5 )	/* Windows 2000 */
			MakeGlobalSemstr(semstr, semnum, semid, ipct->semt[semid].key);
		else
			MakeSemstr(semstr, semnum, semid, ipct->semt[semid].key);
#endif	/* TERMINAL_SERVICE */
		hsem=OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, semstr);
		if (hsem==NULL)
		{
			errno=GetLastError();
			FreeIPCT(hIpct, ipct);
			return -1;
		}
		for (i=0; i<abs(diffsemval); i++)
		{
			if (diffsemval>0)
			{
				ret=ReleaseSemaphore(hsem, diffsemval, NULL);
				if (ret==FALSE)
				{
					errno=GetLastError();
					CloseHandle(hsem);
					FreeIPCT(hIpct, ipct);
					return -1;
				}
				break;	/*2000.4.19*/
			}
			else if (diffsemval<0)
			{
/********************
				do
				{
					dwret=MsgWaitForMultipleObjects(1, &hsem,
						FALSE, INFINITE,
						QS_SENDMESSAGE|QS_POSTMESSAGE|QS_TIMER);
********************/
				dwret=WaitForSingleObject(hsem, INFINITE);

				switch (dwret)
				{
/********************
				case	WAIT_OBJECT_0 + 1 :
					if (l_peekmessage()<0)
					{
						CloseHandle(hsem);
						FreeIPCT(hIpct, ipct);
						return -1;
					}
					break;
********************/

				case	WAIT_OBJECT_0	:
					break;

				case	WAIT_TIMEOUT	:
				case	WAIT_FAILED	:
					errno=GetLastError();
				default :
					CloseHandle(hsem);
					FreeIPCT(hIpct, ipct);
					return -1;
				}
/*************
				} while (dwret==(WAIT_OBJECT_0 + 1));
*************/
			}
		}
		CloseHandle(hsem);

		ipct->semb[semid][semnum].semval=semarg.val;
		for (i=0; i<MAXNOOFIPC; i++)
			ipct->pseminfo[i].semadj[semid][semnum]=0;

		FreeIPCT(hIpct, ipct);
		return 0;

	case	GETPID:
		iret=ipct->semb[semid][semnum].sempid;
		FreeIPCT(hIpct, ipct);
		return iret;

	case	GETNCNT:
		iret=ipct->semb[semid][semnum].semncnt;
		FreeIPCT(hIpct, ipct);
		return iret;

	case	GETZCNT:
		iret=ipct->semb[semid][semnum].semzcnt;
		FreeIPCT(hIpct, ipct);
		return iret;

	case	GETALL:
		if (semarg.array == NULL)
		{
			errno=EINVAL;
			FreeIPCT(hIpct, ipct);
			return -1;
		}

		for (i=0; i<ipct->semt[semid].semds.sem_nsems; i++)
			semarg.array[i]=(short)ipct->semb[semid][i].semval;

		FreeIPCT(hIpct, ipct);
		return 0;

	case	SETALL:
		/* #####PENDING */
		FreeIPCT(hIpct, ipct);
		return 0;

	default:
		FreeIPCT(hIpct, ipct);
		return -1;
	}

}