static struct shmTime*
getShmTime(
	int unit,
	int/*BOOL*/ forall
	)
{
	struct shmTime *p = NULL;

#ifndef SYS_WINNT

	int shmid;

	/* 0x4e545030 is NTP0.
	 * Big units will give non-ascii but that's OK
	 * as long as everybody does it the same way.
	 */
	shmid=shmget(0x4e545030 + unit, sizeof (struct shmTime),
		      IPC_CREAT | (forall ? 0666 : 0600));
	if (shmid == -1) { /* error */
		msyslog(LOG_ERR, "SHM shmget (unit %d): %m", unit);
		return NULL;
	}
	p = (struct shmTime *)shmat (shmid, 0, 0);
	if (p == (struct shmTime *)-1) { /* error */
		msyslog(LOG_ERR, "SHM shmat (unit %d): %m", unit);
		return NULL;
	}

	return p;
#else

	static const char * nspref[2] = { "Local", "Global" };
	char buf[20];
	LPSECURITY_ATTRIBUTES psec = 0;
	HANDLE shmid = 0;
	SECURITY_DESCRIPTOR sd;
	SECURITY_ATTRIBUTES sa;
	unsigned int numch;

	numch = snprintf(buf, sizeof(buf), "%s\\NTP%d",
			 nspref[forall != 0], (unit & 0xFF));
	if (numch >= sizeof(buf)) {
		msyslog(LOG_ERR, "SHM name too long (unit %d)", unit);
		return NULL;
	}
	if (forall) { /* world access */
		if (!InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION)) {
			msyslog(LOG_ERR,"SHM InitializeSecurityDescriptor (unit %d): %m", unit);
			return NULL;
		}
		if (!SetSecurityDescriptorDacl(&sd, TRUE, NULL, FALSE)) {
			msyslog(LOG_ERR, "SHM SetSecurityDescriptorDacl (unit %d): %m", unit);
			return NULL;
		}
		sa.nLength = sizeof(SECURITY_ATTRIBUTES);
		sa.lpSecurityDescriptor = &sd;
		sa.bInheritHandle = FALSE;
		psec = &sa;
	}
	shmid = CreateFileMapping ((HANDLE)0xffffffff, psec, PAGE_READWRITE,
				   0, sizeof (struct shmTime), buf);
	if (shmid == NULL) { /*error*/
		char buf[1000];		
		FormatMessage (FORMAT_MESSAGE_FROM_SYSTEM,
			       0, GetLastError (), 0, buf, sizeof (buf), 0);
		msyslog(LOG_ERR, "SHM CreateFileMapping (unit %d): %s", unit, buf);
		return NULL;
	}
	p = (struct shmTime *)MapViewOfFile(shmid, FILE_MAP_WRITE, 0, 0,
					    sizeof (struct shmTime));
	if (p == NULL) { /*error*/
		char buf[1000];		
		FormatMessage (FORMAT_MESSAGE_FROM_SYSTEM,
			       0, GetLastError (), 0, buf, sizeof (buf), 0);
		msyslog(LOG_ERR,"SHM MapViewOfFile (unit %d): %s", unit, buf);
		return NULL;
	}

	return p;
#endif

	/* NOTREACHED */
	ENSURE(!"getShmTime(): Not reached.");
}