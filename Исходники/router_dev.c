 void router_init_script(char *arg)
{
	int pid=0;
	int i;
	char tmpBuf[MAX_MSG_BUFFER_SIZE]={0};

	snprintf(tmpBuf, MAX_MSG_BUFFER_SIZE, "%s/%s.pid", _DHCPD_PID_PATH, _DHCPD_PROG_NAME);
	pid = getPid(tmpBuf);
	if ( pid > 0) { 
		kill(pid, SIGUSR1);
	}

	usleep(1000);

	if (pid > 0) {
		system("killall -9 udhcpd 2> /dev/null");
		system("rm -f /var/run/udhcpd.pid 2> /dev/null");
	}
	killSomeDaemon();

	system("killsh.sh");	

	sprintf(tmpBuf, "%s gw %s", _CONFIG_SCRIPT_PROG, arg);
	for(i=3; i<sysconf(_SC_OPEN_MAX); i++)
	{
		close(i);
	}

	sleep(1);
	system(tmpBuf);
}