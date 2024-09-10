int setpriority(
		int which,
		int who,
		int prio
		)
{
	BOOL success;
	DWORD prio_class;

	if (PRIO_PROCESS != which || who || NTP_PRIO != prio) {
		DPRINTF(1,("windows setpriority() clone needs work.\n"));
	}

	prio_class = GetPriorityClass(GetCurrentProcess());
	
	if (HIGH_PRIORITY_CLASS == prio_class ||
	    REALTIME_PRIORITY_CLASS == prio_class)
		return 0;

	success = SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);

	if (!success) {
		msyslog(LOG_ERR, "Unable to raise priority: %m"); 
		errno = EPERM;
		return -1;
	}

	prio_class = GetPriorityClass(GetCurrentProcess());

	if (REALTIME_PRIORITY_CLASS == prio_class)
		msyslog(LOG_INFO, "Raised to realtime priority class");
	else if (HIGH_PRIORITY_CLASS == prio_class)
		msyslog(LOG_ERR,  "Raised to high priority class, realtime "
				  "requires Increase Scheduling Priority "
				  "privilege (enabled with secpol.msc).");
	else
		msyslog(LOG_ERR,  "Unexpected process priority class %d",
				 prio_class);

	return 0; 
}