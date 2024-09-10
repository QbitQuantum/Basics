int main(int argc, char **argv)
{
	get_shells();
	setflags(argc,argv);
	proc *ps[10000];
	proc_structs = ps;
	if (unique_uids)
	{
		int uidstr[10000];
		uuids = uidstr;
		int i = 10000;
		while(i--) uuids[i] = -1;
	}

	DIR *dp;
	struct dirent *ep;
	psinfo_t psinfo_buf;
	dp = opendir ("/proc");
	char buf[128];
	if (dp != NULL)
	{
		printf("%8s ","UID");
		if(unique_uids) printf("\n");
		else
		{
			if(pid) printf("%5s ","PID");
			if(descendants) printf("%4s ","N");
			printf("%16s %.24s\n","FNAME","STIME");
		}

		while ((ep = readdir(dp)))
		{
			if(ep->d_name[0] >= '0' && ep->d_name[0] <= '9')
			{
				sprintf(buf,"/proc/%s/psinfo",ep->d_name);
				save_procinfo(buf,&psinfo_buf);
				//print_procinfo(buf,&psinfo_buf);
			}
		}

		(void)closedir(dp);
	}
	else perror ("Couldn't open the directory");	
	compute_descendants();
	proc *p;int i = 0;
	while ((p = proc_structs[i++])) print_procinfo(p);

	return 0;
}