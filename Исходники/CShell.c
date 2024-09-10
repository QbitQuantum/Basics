int get_process(char *command,char *argm[],int num_args)
{
	int check = 1;
	if(num_args>2)
	{
		if(!strcmp(command,"pid"))
		{
			if(!strcmp(argm[1],"current"))
				pid_current();
			else if(!strcmp(argm[1],"all"))
				pid_all();
			check = 0;
			proc[num_proc].proc_run = 0;
			proc[num_proc].proc_pid = pid_out;
			num_proc++;
		}
		if(!strcmp(command,"cd"))
		{
			if(!strcmp(argm[1],getenv("HOME")))
				chdir(getenv("HOME"));
			else
				change_dir(argm[1]);

			check = 0;
			proc[num_proc].proc_pid = pid_out;
			proc[num_proc].proc_run = 0;
			num_proc++;
		}
	}
	else
	{
		if(!strcmp(command,"pid"))
		{
			printf("command name: ./a.out process id: %d\n",pid_out);
			check = 0;
			proc[num_proc].proc_pid = pid_out;
			proc[num_proc].proc_run = 0;
			num_proc++;
		}
		else if(!strcmp(command,"hist"))
		{
			hist_all();
			check = 0;
			proc[num_proc].proc_run = 0;
			proc[num_proc].proc_pid = pid_out;
			num_proc++;
		}
		else if(!strcmp(strndup(command,4),"hist") && strlen(command)>4)
		{
			hist_n(string_to_int(&command[4]));
			check = 0;
			proc[num_proc].proc_pid = pid_out;
			proc[num_proc].proc_run = 0;
			num_proc++;
		}
		else if(!strcmp(strndup(command,5),"!hist"))
		{
			proc[num_proc].proc_pid = pid_out;
			proc[num_proc].proc_run = 0;
			num_proc++;
			not_hist_n(string_to_int(&command[5]));
			check = 0;
		}
		else if(!strcmp(command,"quit"))
			exit(0);
		else if(!strcmp(command,"ls"))
		{
			ls_out();
			check = 0;
			proc[num_proc].proc_pid = pid_out;
			proc[num_proc].proc_run = 0;
			num_proc++;
		}
		else if(!strcmp(command,"cd"))
		{
			char *home = getenv("HOME");
			chdir(home);
			check = 0;
			proc[num_proc].proc_pid = pid_out;
			proc[num_proc].proc_run = 0;
			num_proc++;
		}
	}
	return check;
}