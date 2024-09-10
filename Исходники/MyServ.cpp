void ServiceStop()
{
	printf("call ServiceStop\n");

	printf("Search for %s\n",__progname);

	pid_t pidSelf;
	pidSelf = getpid();


	int pid = -1;
	pid = getProcessID(__progname);
	printf("self pid=%d\n",pidSelf);
	printf("pid=%d\n",pid);

	if(pid!=-1 && pid!=0)
	{
		printf("call kill\n");
		kill(pid,SIGTERM);

	}
	
	printf("call ServiceStop end\n");
}