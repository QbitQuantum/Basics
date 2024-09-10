int main(int argc, char *argv[])
{

	int test_num, task_num, len, num_cpus;
	char mygroup[FILENAME_MAX], mytaskfile[FILENAME_MAX];
	char mysharesfile[FILENAME_MAX], ch;
	/* Following variables are to capture parameters from script*/
	char *group_num_p, *mygroup_p, *script_pid_p, *num_cpus_p;
	char *test_num_p, *task_num_p;
	int mygroup_num,	        /* A number attached with a group*/
		fd,          	        /* to open a fifo to synchronize*/
		counter = 0; 	 	/* To take n number of readings*/
	double total_cpu_time,  	/* Accumulated cpu time*/
		delta_cpu_time,  	/* Time the task could run on cpu(s)*/
		prev_cpu_time = 0;
	double exp_cpu_time;            /* Exp time in % by shares calculation*/

	struct rusage cpu_usage;
	time_t current_time, prev_time, delta_time;
	unsigned int fmyshares, num_tasks;
	unsigned int mygroup_shares;
	struct sigaction newaction, oldaction;
	/* Signal handling for alarm*/
	sigemptyset(&newaction.sa_mask);
	newaction.sa_handler = signal_handler_alarm;
	newaction.sa_flags = 0;
	sigaction(SIGALRM, &newaction, &oldaction);

	/* Collect the parameters passed by the script */
	group_num_p	= getenv("GROUP_NUM");
	mygroup_p	= getenv("MYGROUP");
	script_pid_p 	= getenv("SCRIPT_PID");
	num_cpus_p 	= getenv("NUM_CPUS");
	test_num_p 	= getenv("TEST_NUM");
	task_num_p 	= getenv("TASK_NUM");
	/* Check if all of them are valid */
	if ((test_num_p != NULL) && (((test_num = atoi(test_num_p)) <= 10) && \
					((test_num = atoi(test_num_p)) >= 9))) {
		if ((group_num_p != NULL) && (mygroup_p != NULL) && \
			(script_pid_p != NULL) && (num_cpus_p != NULL) && \
				 (task_num_p != NULL)) {
			mygroup_num	 = atoi(group_num_p);
			scriptpid	 = atoi(script_pid_p);
			num_cpus	 = atoi(num_cpus_p);
			task_num	 = atoi(task_num_p);
			sprintf(mygroup, "%s", mygroup_p);
		} else {
			tst_brkm(TBROK, cleanup,
					 "Invalid other input parameters\n");
		}
	} else {
		tst_brkm(TBROK, cleanup, "Invalid test number passed\n");
	}

	sprintf(mytaskfile, "%s", mygroup);
	sprintf(mysharesfile, "%s", mygroup);
	strcat(mytaskfile, "/tasks");
	strcat(mysharesfile, "/cpu.shares");

	write_to_file(mytaskfile, "a", getpid());

	/*
	 * Let us give the default group 100 shares, as other groups will have
	 * a multiple of 100 shares.
	 */
	mygroup_shares = 100;
	write_to_file(mysharesfile, "w", mygroup_shares);

	fd = open("./myfifo", 0);
	if (fd == -1)
		tst_brkm(TBROK, cleanup, "Could not open fifo synchronize");

	read(fd, &ch, 1);	/* Block task here to synchronize */

	/*
	 * We need not calculate the expected % cpu time of this task, as
	 * neither it is required nor it can be predicted as there are idle
	 * system tasks (and others too) in this group.
	 */
	FLAG = 0;
	total_shares = 0;
	shares_pointer = &total_shares;
	len = strlen(path);
	if (!strncpy(fullpath, path, len))
		tst_brkm(TBROK, cleanup,
			 "Could not copy directory path %s ", path);

	if (scan_shares_files(shares_pointer) != 0)
		tst_brkm(TBROK, cleanup,
		 "From function scan_shares_files in %s ", fullpath);

	/* return val -1 in case of function error, else 2 is min share value */
	if ((fmyshares = read_shares_file(mysharesfile)) < 2)
		tst_brkm(TBROK, cleanup,
			 "in reading shares files  %s ", mysharesfile);

	if ((read_file(mytaskfile, GET_TASKS, &num_tasks)) < 0)
		tst_brkm(TBROK, cleanup,
			 "in reading tasks files  %s ", mytaskfile);

	exp_cpu_time = (double)(fmyshares * 100) / (total_shares * num_tasks);

	prev_time = time(NULL);	 /* Note down the time*/

	while (1) {
		/*
		 * Need to run some cpu intensive task, which also
		 * frequently checks the timer value
		 */
		double f = 274.345, mytime;	/*just a float number for sqrt*/
		alarm(TIME_INTERVAL);
		timer_expired = 0;
		/*
		 * Let the task run on cpu for TIME_INTERVAL. Time of this
		 * operation should not be high otherwise we can exceed the
		 * TIME_INTERVAL to measure cpu usage
		 */
		while (!timer_expired)
			f = sqrt(f * f);

		current_time = time(NULL);
		/* Duration in case its not exact TIME_INTERVAL*/
		delta_time = current_time - prev_time;

		getrusage(0, &cpu_usage);
		/* total_cpu_time = total user time + total sys time */
		total_cpu_time = (cpu_usage.ru_utime.tv_sec +
				cpu_usage.ru_utime.tv_usec * 1e-6 +
				cpu_usage.ru_stime.tv_sec +
				cpu_usage.ru_stime.tv_usec * 1e-6) ;
		delta_cpu_time = total_cpu_time - prev_cpu_time;

		prev_cpu_time = total_cpu_time;
		prev_time = current_time;

		/* calculate % cpu time each task gets */
		if (delta_time > TIME_INTERVAL)
			mytime = (delta_cpu_time * 100) /
					 (delta_time * num_cpus);
		else
			mytime = (delta_cpu_time * 100) /
					 (TIME_INTERVAL * num_cpus);

		/* No neeed to print the results */
		fprintf(stdout, "Grp:-%3d task-%3d:CPU TIME{calc:-%6.2f(s) i.e."
			"  %6.2f(%%) exp:-%6.2f(%%)} with %3u shares in %lu (s)"
			" INTERVAL\n", mygroup_num, task_num, delta_cpu_time,
			 mytime, exp_cpu_time, fmyshares, delta_time);

		counter++;

		if (counter >= NUM_INTERVALS) {
			switch (test_num) {

			case 9:			/* Test 09 */
			case 10:		/* Test 10 */
				exit(0);	/* This task is done */
				break;
			default:
				tst_brkm(TBROK, cleanup,
					 "Invalid test number passed\n");
				break;

			}	/* end switch*/
		}	/* end if*/
	}	/* end while*/
}	/* end main*/